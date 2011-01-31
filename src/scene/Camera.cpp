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
		/*float x,y,z,a,b,c,u,v,w;
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
			Vector3 tmpv( lookAt.getX() - pos.getX(), lookAt.getY() - pos.getY(), lookAt.getZ() - pos.getZ());
			tmpv.normalize();
			//cout << "irany: " << tmpv << endl;
			u = tmpv.getX();
			v = tmpv.getY();
			w = tmpv.getZ();
			Matrix4 transm;
			Vector3 negpos(-pos.getX(),-pos.getY(),-pos.getZ());
			transm = transm.translate(negpos);
			cout << transm << endl;
			Vector3 directionV = lookAt*transm;
			directionV.normalize();
			cout << "dirV = " << directionV << endl;
			//directionV.normalize();
			u = directionV.getX();
			v = directionV.getY();
			w = directionV.getZ();*/
			//a = pos.getX();
			//b = pos.getY();
			//c = pos.getZ();
			/*a = 0;
			b = 0;
			c = 0;
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
		if(u*u+v*v<0.1){
			cout << "warning: u and v too small: u=" << u << ", v=" << v << ", w=" << w << ", u^2*v^2=" << u*u+v*v << endl;
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
			cout << lookAt << endl;
		}else if(direction==LEAN_LEFT || direction==LEAN_RIGHT){
			//cout << up;
			up.setX(resX);
			up.setY(resY);
			up.setZ(resZ);
			//up.normalize();
			//cout << " " << up << endl;
			cout << up << endl;
		}*/
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
			if(d1!=0){//TODO eps-re cserelni?
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
			if(d1!=0){
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
			//cout << right;
			
			T = T.translate(-pos);
			d1 = (sqrt(sqr(right.getX()) + sqr(right.getY()) ));
			d = sqrt(sqr(right.getX())+sqr(right.getY())+sqr(right.getZ()));
			if(d1!=0){
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
			lookAt = lookAt*T*Rxz*Rxz2z*Rz*Rxz2z.invert()*Rxz.invert()*T.invert();
			up     =     up  *Rxz*Rxz2z*Rz*Rxz2z.invert()*Rxz.invert();
			//cout << " " << lookAt << " " << up << endl;
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
};//namespace scene
};//namespace siege
