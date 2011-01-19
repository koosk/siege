#include "math/Matrix16f.h"
#include "BadIndexException.h"
#include <string.h>
#include <cmath>
#include <iostream>

namespace siege{
	namespace math{
		Matrix16f::Matrix16f(){
			for(int i=0; i<16; i++){
				data[i] = 0.f;
			}
			this->data[0] = this->data[5] = 1.f;
			this->data[10] = this->data[15] = 1.f;
		}
		
		Matrix16f::Matrix16f(const Matrix16f &m){
			memcpy(data,m.data,sizeof(float[16]));
		}

		Matrix16f::Matrix16f(const float *data){
			memcpy(this->data,data,sizeof(float[16]));
		}

		Matrix16f::~Matrix16f(){
			//std::cout << "Matrix16f destruktor" << std::endl;
		};
		
		Matrix16f& Matrix16f::operator=(const Matrix16f &m){
			memcpy(data,m.data,sizeof(float[16]));
			return (*this);
		}

		void Matrix16f::load(const float *data){
			memcpy(this->data,data,sizeof(float[16]));
		}

		void Matrix16f::loadTranspose(const float *data){
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					this->data[i*4+j] = data[4*j+i];
				}
			}
		}

		void Matrix16f::set(int pos, float value){
			if(pos>15){
				throw siege::BadIndexException();
			}
			data[pos] = value;
		}

		float Matrix16f::operator[](int index) const{//index from 0
			if(index>15 || index<0){
				throw siege::BadIndexException();
			}
			return data[index];
		}
		
		Matrix16f Matrix16f::operator*(const Matrix16f &m) const{
			float r[16];
			r[0]  = data[0]*m.data[0]  + data[4]*m.data[1]  + data[8]*m.data[2]   + data[12]*m.data[3];
			r[1]  = data[1]*m.data[0]  + data[5]*m.data[1]  + data[9]*m.data[2]   + data[13]*m.data[3];
			r[2]  = data[2]*m.data[0]  + data[6]*m.data[1]  + data[10]*m.data[2]  + data[14]*m.data[3];
			r[3]  = data[3]*m.data[0]  + data[7]*m.data[1]  + data[11]*m.data[2]  + data[15]*m.data[3];

			r[4]  = data[0]*m.data[4]  + data[4]*m.data[5]  + data[8]*m.data[6]   + data[12]*m.data[7];
			r[5]  = data[1]*m.data[4]  + data[5]*m.data[5]  + data[9]*m.data[6]   + data[13]*m.data[7];
			r[6]  = data[2]*m.data[4]  + data[6]*m.data[5]  + data[10]*m.data[6]  + data[14]*m.data[7];
			r[7]  = data[3]*m.data[4]  + data[7]*m.data[5]  + data[11]*m.data[6]  + data[15]*m.data[7];

			r[8]  = data[0]*m.data[8]  + data[4]*m.data[9]  + data[8]*m.data[10]  + data[12]*m.data[11];
			r[9]  = data[1]*m.data[8]  + data[5]*m.data[9]  + data[9]*m.data[10]  + data[13]*m.data[11];
			r[10] = data[2]*m.data[8]  + data[6]*m.data[9]  + data[10]*m.data[10] + data[14]*m.data[11];
			r[11] = data[3]*m.data[8]  + data[7]*m.data[9]  + data[11]*m.data[10] + data[15]*m.data[11];

			r[12] = data[0]*m.data[12] + data[4]*m.data[13] + data[8]*m.data[14]  + data[12]*m.data[15];
			r[13] = data[1]*m.data[12] + data[4]*m.data[13] + data[9]*m.data[14]  + data[13]*m.data[15];
			r[14] = data[2]*m.data[12] + data[5]*m.data[13] + data[10]*m.data[14] + data[14]*m.data[15];
			r[15] = data[3]*m.data[12] + data[6]*m.data[13] + data[11]*m.data[14] + data[15]*m.data[15];
			return Matrix16f(r);
		}
		
		Matrix16f Matrix16f::operator*=(const Matrix16f &m){
			*this = (*this) * m;
			return *this;
		}

		Matrix16f Matrix16f::transpose() const{
			float res[16];
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					res[4*j+i] = data[4*i+j];
				}
			}
			return Matrix16f(res);
		}

		std::ostream& operator<<(std::ostream &out,const Matrix16f &m){
			for(int i=0; i<4; i++){
				int j;
				for(j=0; j<3; j++){
					out << m.data[i*4+j] << " ";
				}
				out << m.data[i*4+j] << std::endl;
			}
			return out;
		}
		
		Matrix16f Matrix16f::translate(const Vector3f &v) const{
			float r[16];
			float x = v.getX();
			float y = v.getY();
			float z = v.getZ();
			r[0]  = data[0]+data[3]*x;
			r[4]  = data[1]+data[3]*y;
			r[8]  = data[2]+data[3]*z;
			r[12]  = data[3];
			r[1]  = data[4]+data[7]*x;
			r[5]  = data[5]+data[7]*y;
			r[9]  = data[6]+data[7]*z;
			r[13]  = data[7];
			r[2]  = data[8]+data[11]*x;
			r[6]  = data[9]+data[11]*y;
			r[10] = data[10]+data[11]*z;
			r[14] = data[11];
			r[3] = data[12]+data[15]*x;
			r[7] = data[13]+data[15]*y;
			r[11] = data[14]+data[15]*z;
			r[15] = data[15];
			return Matrix16f(r);
		}

		Matrix16f Matrix16f::rotate(const Vector3f &v) const{
			/*float phi = v.getX();
			float theta = v.getY();
			float psi = v.getZ();*/
			/*float phi = v.getZ();
			float theta = v.getX();
			float psi = v.getY();

			float cphi = cos(phi);
			float sphi = sin(phi);
			float ctheta = cos(theta);
			float stheta = sin(theta);
			float cpsi = cos(psi);
			float spsi = sin(psi);*/
			/* http://www.ibrtses.com/opengl/matrices.html   
            |cos(phi)cos(psi)-sin(phi)cos(theta)sin(psi)      cos(phi)*sin(psi)+sin(phi)*cos(theta)*cos(psi)   sin(phi)*sin(theta)|
			|-sin(phi)*cos(psi)-cos(phi)*cos(theta)*sin(psi)  -sin(phi)*sin(psi)+cos(phi)*cos(theta)*cos(psi)  cos(phi)*sin(theta)|
			|sin(theta)*sin(psi)                              -sin(theta)*cos(psi)                             cos(theta)         |
			*/
			/*float r[16] = {cphi*cpsi-sphi*ctheta*spsi, -sphi*cpsi-cphi*ctheta*spsi, stheta*spsi , 0.f,
			               cphi*spsi+sphi*ctheta*cpsi, -sphi*spsi+cphi*ctheta*cpsi, -stheta*cpsi, 0.f,
			               sphi*stheta               , cphi*stheta                , ctheta      , 0.f,
			               0.f                       , 0.f                       , 0.f         , 1.f
			};*/
			float xRot = v.getX();
			float yRot = v.getY();
			float zRot = v.getZ();
			float cx = cos(xRot);
			float sx = sin(xRot);
			float cy = cos(yRot);
			float sy = sin(yRot);
			float cz = cos(zRot);
			float sz = sin(zRot);
			/*float r[16] = {cy*cz-sz*sy*sx, -sz*cx, sy*cz+sx*cy   , 0.,
			               cy*sz+sy*sx*cz, cx*cz , sy*sz-sx*cy*cz, 0.,
			               -sy*cx        , sx    , cy*cx         , 0.,
			               0.            , 0.    , 0.            , 1.};*/
			/*float r[16] = {cz*cy          , -sz*cy         , sy    , 0.,
			               cz*sy*sx+sz*cx , -sz*sy*sx+cz*cx, -sy*cy, 0.,
			               -cz*sy*cx+sz*sx, sz*sy*cx+cz*sx , cy*cx , 0.,
			               0.             , 0.             , 0.    , 1.
			};*/
			float r[16] = {cz*cy+sz*sx*sy , -sz*cy+cz*sx*sy, cx*sy , 0.,
			               sz*cx          , cz*cx          , -sx   , 0.,
			               -cz*sy+sz*sx*cy, sz*sy+cz*sx*cy , cx*cy , 0.,
			               0.             , 0.             , 0.    , 1.
			};
			//return ((*this)*Matrix16f(r));
			return (Matrix16f(r)*(*this));
		}
		
		Matrix16f Matrix16f::scale(const Vector3f &v) const{
			float *r = new float[16];
			memcpy(r,data,sizeof(float[16]));
			r[0]  *= v.getX();
			r[5]  *= v.getY();
			r[10] *= v.getZ();
			return Matrix16f(r);
		}

		//A matrix and its transpose have the same determinant.
		//Using rule of Sarrus.
		float Matrix16f::determinant3(const float *f){
			return (f[0]*f[4]*f[8] + f[1]*f[5]*f[6] + f[2]*f[3]*f[7]
				  - f[2]*f[4]*f[6] - f[1]*f[3]*f[8] - f[0]*f[5]*f[7]);
		}
		
		float Matrix16f::determinant() const{
			float tmp1[9] = {data[1],data[2],data[3],
			                 data[5],data[6],data[7],
			                 data[9],data[10],data[11]};

			float tmp2[9] = {data[0],data[2],data[3],
			                 data[4],data[6],data[7],
			                 data[8],data[10],data[11]};

			float tmp3[9] = {data[0],data[1],data[3],
			                 data[4],data[5],data[7],
			                 data[8],data[9],data[11]};

			float tmp4[9] = {data[0],data[1],data[2],
			                 data[4],data[5],data[6],
			                 data[8],data[9],data[10]};
			return (data[12]*determinant3(tmp1) - data[13]*determinant3(tmp2)
				  + data[14]*determinant3(tmp3) - data[15]*determinant3(tmp4));
		}
		
		Matrix16f Matrix16f::invert() const throw(MathException){
			float det = determinant();
			if(0==det){
				throw MathException("Singular matrix does not have determinant and inverse.");
			}
			float r[16];
			//1. sor
			{
				float c[9] = {data[5],data[6],data[7],
				              data[9],data[10],data[11],
				              data[13],data[14],data[15]};
				r[0] = determinant3(c);
			}
			{
				float c[9] = {data[4],data[6],data[7],
				              data[8],data[10],data[11],
				              data[12],data[14],data[15]};
				r[1] = determinant3(c);
			}
			{
				float c[9] = {data[4],data[5],data[7],
				              data[8],data[9],data[11],
				              data[12],data[13],data[15]};
				r[2] = determinant3(c);
			}
			{
				float c[9] = {data[4],data[5],data[6],
				              data[8],data[9],data[10],
				              data[12],data[13],data[14]};
				r[3] = determinant3(c);
			}
			//2. sor
			{
				float c[9] = {data[1],data[2],data[3],
				              data[9],data[10],data[11],
				              data[13],data[14],data[15]};
				r[4] = determinant3(c);
			}
			{
				float c[9] = {data[0],data[2],data[3],
				              data[8],data[10],data[11],
				              data[12],data[14],data[15]};
				r[5] = determinant3(c);
			}
			{
				float c[9] = {data[0],data[1],data[3],
				              data[8],data[9],data[11],
				              data[12],data[13],data[15]};
				r[6] = determinant3(c);
			}
			{
				float c[9] = {data[0],data[1],data[2],
				              data[8],data[9],data[10],
				              data[12],data[13],data[14]};
				r[7] = determinant3(c);
			}
			//3. sor
			{
				float c[9] = {data[1],data[2],data[3],
				              data[5],data[6],data[7],
				              data[13],data[14],data[15]};
				r[8] = determinant3(c);
			}
			{
				float c[9] = {data[0],data[2],data[3],
				              data[4],data[6],data[7],
				              data[12],data[14],data[15]};
				r[9] = determinant3(c);
			}
			{
				float c[9] = {data[0],data[1],data[3],
				              data[4],data[5],data[7],
				              data[12],data[13],data[15]};
				r[10] = determinant3(c);
			}
			{
				float c[9] = {data[0],data[1],data[2],
				              data[4],data[5],data[6],
				              data[12],data[13],data[14]};
				r[11] = determinant3(c);
			}
			//4. sor
			{
				float c[9] = {data[1],data[2],data[3],
				              data[5],data[6],data[7],
				              data[9],data[10],data[11]};
				r[12] = determinant3(c);
			}
			{
				float c[9] = {data[0],data[2],data[3],
				              data[4],data[6],data[7],
				              data[8],data[10],data[11]};
				r[13] = determinant3(c);
			}
			{
				float c[9] = {data[0],data[1],data[3],
				              data[4],data[5],data[7],
				              data[8],data[9],data[11]};
				r[14] = determinant3(c);
			}
			{
				float c[9] = {data[0],data[1],data[2],
				              data[4],data[5],data[6],
				              data[8],data[9],data[10]};
				r[15] = determinant3(c);
			}

			return (1./det)*Matrix16f(r);
		}
		
		Matrix16f operator*(float c,const Matrix16f &m){
			float r[16];
			for(int i=0; i<16; i++){
				r[i] = c*m.data[i];
			}
			return Matrix16f(r);
		}

		Matrix16f Matrix16f::operator+(const Matrix16f &m) const{
			float r[16];
			for(int i=0; i<16; i++){
				r[i] = data[i] + m.data[i];
			}
			return Matrix16f(r);
		}
		
		Matrix16f Matrix16f::operator-(const Matrix16f &m) const{
			float r[16];
			for(int i=0; i<16; i++){
				r[i] = data[i] - m.data[i];
			}
			return Matrix16f(r);
		}

		Matrix16f Matrix16f::operator+=(const Matrix16f &m){
			*this = (*this) + m;
			return *this;
		}
		
		Matrix16f Matrix16f::operator-=(const Matrix16f &m){
			*this = (*this) - m;
			return *this;
		}

	};//math
};//siege
