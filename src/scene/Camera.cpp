#include "scene/Camera.h"
#include <GL/glu.h> 
#include "math/Matrix4.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace siege{
	Camera::Camera():lookAt(Vector3(0.f,0.f,-1.f)),up(Vector3(0.f,1.f,0.f)),
		movementIntensity(defaultMovementIntensity),rotationIntensity(defaultRotationIntensity){
	}

	Camera::Camera(const Vector3 p, const Vector3 la, const Vector3 u)
		:pos(p),lookAt(la),up(u),movementIntensity(defaultMovementIntensity),
		rotationIntensity(defaultRotationIntensity){
	}


	Camera::Camera(const float px, const float py, const float pz,
			       const float lx, const float ly, const float lz,
			       const float ux, const float uy, const float uz)
		:pos(Vector3(px,py,pz)),lookAt(Vector3(lx,ly,lz)),up(Vector3(ux,uy,uz)),
		 movementIntensity(defaultMovementIntensity),rotationIntensity(defaultRotationIntensity){
	}

	Camera::~Camera(){
	}

	void Camera::refresh() const{
		gluLookAt(pos.getX(),pos.getY(),pos.getZ(),
		          lookAt.getX(),lookAt.getY(),lookAt.getZ(),
		          up.getX(),up.getY(),up.getZ());
	}

	void Camera::setMovementIntensity(const float movementIntensity){
		this->movementIntensity = movementIntensity;
	}

	void Camera::setRotationIntensity(const float rotationIntensity){
		this->rotationIntensity = rotationIntensity;
	}
	
	void Camera::setDefaultMovementIntensity(){
		movementIntensity = defaultMovementIntensity;
	}

	void Camera::setDefaultRotationIntensity(){
		rotationIntensity = defaultRotationIntensity;
	}

	 float Camera::getMovementIntensity() const{
		return movementIntensity;
	}

	float Camera::getRotationIntensity() const{
		return rotationIntensity;
	}
	
	void Camera::rotate(const int direction){
#define sqr(x) x*x
		//http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/ArbitraryAxisRotation.html#fig:axisrot
		float x,y,z,a,b,c,u,v,w;
		float stheta;
		float ctheta;
		//TODO valtozhat, hogy mi korul forgatunk
		if(direction==ROTATE_LEFT || direction==ROTATE_RIGHT){
			x = lookAt.getX();
			y = lookAt.getY();
			z = lookAt.getZ();
			a = pos.getX();
			b = pos.getY();
			c = pos.getZ();
			u = up.getX();
			v = up.getY();
			w = up.getZ();

			if(direction==ROTATE_RIGHT){
				stheta = sin(-rotationIntensity);
				ctheta = cos(-rotationIntensity);
			}else{//ROTATE_LEFT
				stheta = sin(rotationIntensity);
				ctheta = cos(rotationIntensity);
			}
		}else if(direction==LEAN_LEFT || direction==LEAN_RIGHT){
	//!!!!!!!!!!!!!!! itt valami nem jo
			u = lookAt.getX() - pos.getX();
			v = lookAt.getY() - pos.getY();
			w = lookAt.getZ() - pos.getZ();
			a = pos.getX();
			b = pos.getY();
			c = pos.getZ();
			x = up.getX();
			y = up.getY();
			z = up.getZ();
			if(direction==LEAN_RIGHT){
				stheta = sin(-rotationIntensity);
				ctheta = cos(-rotationIntensity);
			}else{//LEAN_LEFT
				stheta = sin(rotationIntensity);
				ctheta = cos(rotationIntensity);
			}
		}

		const float sqrd = sqr(u)+sqr(v)+sqr(w);
		const float d = sqrt(sqrd);
		const float resX = (a*(sqr(v)+sqr(w)) + u*(-b*v-c*w+u*x+w*y+w*z) + 
		             ((x-a)*(sqr(v)+sqr(w)) + u*(b*v+c*w-v*z-w*z))*ctheta +
		             d*(b*w-c*v-w*y+v*z)*stheta) / sqrd;
		const float resY = (b*(sqr(u)+sqr(w)) + v*(-a*u-c*w+u*x+v*y+w*z) + 
		             ((y-b)*(sqr(u)+sqr(w)) + v*(a*u+c*w-u*x-w*z))*ctheta +
		             d*(-a*w+c*u+w*x-u*z)*stheta) / sqrd;
		const float resZ = (c*(sqr(u)+sqr(v)) + w*(-a*u-b*v+u*x+v*y+w*z) + 
		             ((z-c)*(sqr(u)+sqr(v)) + w*(a*u+b*v-u*x-v*y))*ctheta +
		             d*(a*v-b*u-v*x+u*y)*stheta) / sqrd;

		if(direction==ROTATE_LEFT || direction==ROTATE_RIGHT){
			lookAt.setX(resX);
			lookAt.setY(resY);
			lookAt.setZ(resZ);
		}else if(direction==LEAN_LEFT || direction==LEAN_RIGHT){
			cout << up << endl;
			up.setX(resX);
			up.setY(resY);
			up.setZ(resZ);
			up.normalize();
		}
		
#undef sqr
	}
};
