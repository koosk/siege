#include "scene/Camera.h"
#include <GL/glu.h> 
#include "math/Matrix4.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace siege{
  namespace scene{
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

	void Camera::render() const{
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

	float Camera::getMovementIntensity() const{
		return movementIntensity;
	}

	float Camera::getRotationIntensity() const{
		return rotationIntensity;
	}
	
	void Camera::rotate(const int direction){
#define sqr(x) (x*x)
		//http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/ArbitraryAxisRotation.html#fig:axisrot
		//r46 meg tartalmaz egy kozvetlen kepletet, matrixok nelkul, de mivel nem mukodott, lecsereltem. Gyorsitasi lehetoseg.
		const float eps = 0.1f;
		Matrix4 T;
		Matrix4 Rxz;
		Matrix4 Rxz2z;
		Matrix4 Rz;
		float d1;
		float d;
		Vector3 rotv;
		if(direction==ROTATE_LEFT || direction==ROTATE_RIGHT){
			T = T.translate(-pos);
			d1 = (sqrt(sqr(up.getX()) + sqr(up.getY()) ));
			d = sqrt(sqr(up.getX())+sqr(up.getY())+sqr(up.getZ()));
			if(d1>=eps){
				Rxz.set(0,up.getX()/d1);
				Rxz.set(1,up.getY()/d1);
				Rxz.set(4,-up.getY()/d1);
				Rxz.set(5,up.getX()/d1);
			}
			Rxz2z.set(0,up.getZ()/d);
			Rxz2z.set(2,-d1/d);
			Rxz2z.set(8,d1/d);
			Rxz2z.set(10,up.getZ()/d);
			if(direction==ROTATE_LEFT){
				rotv.setZ(rotationIntensity);
			}else{//ROTATE_RIGHT
				rotv.setZ(-rotationIntensity);
			}
			Rz = Rz.rotate(rotv);
			lookAt = lookAt*T*Rxz*Rxz2z*Rz*Rxz2z.invert()*Rxz.invert()*T.invert();
		}else if(direction==LEAN_LEFT || direction==LEAN_RIGHT){
			T = T.translate(-pos);
			Vector3 dir(pos.getX()-lookAt.getX(), pos.getY()-lookAt.getY(), pos.getZ()-lookAt.getZ());
			dir.normalize();
			d1 = sqrt(sqr(dir.getX()) + sqr(dir.getY()) );
			d  = sqrt(sqr(dir.getX())+sqr(dir.getY())+sqr(dir.getZ()));
			if(d1>=eps){
				Rxz.set(0,dir.getX()/d1);
				Rxz.set(1,dir.getY()/d1);
				Rxz.set(4,-dir.getY()/d1);
				Rxz.set(5,dir.getX()/d1);
			}
			Rxz2z.set(0,dir.getZ()/d);
			Rxz2z.set(2,-d1/d);
			Rxz2z.set(8,d1/d);
			Rxz2z.set(10,dir.getZ()/d);
			if(direction==LEAN_LEFT){
				rotv.setZ(rotationIntensity);
			}else{//LEAN_RIGHT
				rotv.setZ(-rotationIntensity);
			}
			Rz = Rz.rotate(rotv);
			up = up*T*Rxz*Rxz2z*Rz*Rxz2z.invert()*Rxz.invert()*T.invert();
		}else if(ROTATE_UP || ROTATE_DOWN){
			Vector3 dir = lookAt-pos;
			dir.normalize();
			Vector3 right = dir.crossProduct(up);
			T = T.translate(-pos);
			d1 = (sqrt(sqr(right.getX()) + sqr(right.getY()) ));
			d = sqrt(sqr(right.getX())+sqr(right.getY())+sqr(right.getZ()));
			if(d1>=eps){
				Rxz.set(0,right.getX()/d1);
				Rxz.set(1,right.getY()/d1);
				Rxz.set(4,-right.getY()/d1);
				Rxz.set(5,right.getX()/d1);
			}
			Rxz2z.set(0,right.getZ()/d);
			Rxz2z.set(2,-d1/d);
			Rxz2z.set(8,d1/d);
			Rxz2z.set(10,right.getZ()/d);
			if(direction==ROTATE_UP){
				rotv.setZ(rotationIntensity);
			}else{//ROTATE_DOWN
				rotv.setZ(-rotationIntensity);
			}
			Rz = Rz.rotate(rotv);
			Vector3 newLookAt = lookAt*T*Rxz*Rxz2z*Rz*Rxz2z.invert()*Rxz.invert()*T.invert();
			dir = newLookAt-pos;
			dir.normalize();
			if(dir.crossProduct(up).length()>=0.2f){
				lookAt = newLookAt;
			}
			//up     =     up  *Rxz*Rxz2z*Rz*Rxz2z.invert()*Rxz.invert();
		}
#undef sqr
	}

	void Camera::move(const int direction){
		if(direction==MOVE_FORWARD || direction==MOVE_BACKWARD){
			Vector3 dir = lookAt - pos;
			dir.normalize();
			if(direction==MOVE_FORWARD){
				pos    += movementIntensity*dir;
				lookAt += movementIntensity*dir;
			}else{//MOVE_BACKWARD
				pos    -= movementIntensity*dir;
				lookAt -= movementIntensity*dir;
			}
		}else if(direction==MOVE_RIGHT || direction==MOVE_LEFT){
			Vector3 viewDir = lookAt - pos;
			viewDir.normalize();
			Vector3 right   = viewDir.crossProduct(up);
			right.normalize();
			if(direction==MOVE_RIGHT){
				pos    += movementIntensity*right;
				lookAt += movementIntensity*right;
			}else{//MOVE_LEFT
				pos    -= movementIntensity*right;
				lookAt -= movementIntensity*right;
			}
		}else if(direction==MOVE_UP || direction==MOVE_DOWN){
			up.normalize();
			if(direction==MOVE_UP){
				pos    += movementIntensity*up;
				lookAt += movementIntensity*up;
			}else{//MOVE_DOWN
				pos    -= movementIntensity*up;
				lookAt -= movementIntensity*up;
			}
		}
	}

	const Vector3& Camera::getPosition() const{
		return pos;
	}

	const Vector3& Camera::getUp() const{
		return up;
	}

	const Vector3& Camera::getLookAt() const{
		return lookAt;
	}
	
	void Camera::setPosition(const Vector3 &pos){
		this->pos = pos;
	}

	void Camera::setUp(const Vector3 &up){
		this->up = up;
	}

	void Camera::setLookAt(const Vector3 &lookAt){
		this->lookAt = lookAt;
	}
  };//namespace scene
};//namespace siege
