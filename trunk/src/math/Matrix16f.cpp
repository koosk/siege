#include "math/Matrix16f.h"
#include "BadIndexException.h"
#include <string.h>

namespace siege{
	namespace math{
		Matrix16f::Matrix16f(){
			for(int i=0; i<16; i++){
				data[i] = 0.0f;
			}
			this->data[0] = this->data[5] = 1;
			this->data[10] = this->data[15] = 1;
		}
		
		Matrix16f::Matrix16f(const Matrix16f &m){
			memcpy(data,m.data,sizeof(float[16]));
		}

		Matrix16f::Matrix16f(const float *data){
			memcpy(this->data,data,sizeof(float[16]));
		}

		Matrix16f::~Matrix16f(){
		};
		
		Matrix16f& Matrix16f::operator=(const Matrix16f &m){
			memcpy(data,m.data,sizeof(float[16]));
			return (*this);
		}

		void Matrix16f::set(const float *data){
			memcpy(this->data,data,sizeof(float[16]));
		}

		void Matrix16f::set(int pos, float value){
			if(pos>15){
				throw siege::BadIndexException();
			}
			data[pos] = value;
		}

		float Matrix16f::operator[](int index) const{//index from 0
			if(index>15){
				throw siege::BadIndexException();
			}
			return data[index];
		}
		
		Matrix16f& Matrix16f::operator*(const Matrix16f &m) const{
			float r[16];
			r[0]  = data[0]*m.data[0]  + data[1]*m.data[4]  + data[2]*m.data[8]   + data[3]*m.data[12];
			r[1]  = data[0]*m.data[1]  + data[1]*m.data[5]  + data[2]*m.data[9]   + data[3]*m.data[13];
			r[2]  = data[0]*m.data[2]  + data[1]*m.data[6]  + data[2]*m.data[10]  + data[3]*m.data[14];
			r[3]  = data[0]*m.data[3]  + data[1]*m.data[7]  + data[2]*m.data[11]  + data[3]*m.data[15];

			r[4]  = data[4]*m.data[0]  + data[5]*m.data[4]  + data[6]*m.data[8]   + data[7]*m.data[12];
			r[5]  = data[4]*m.data[1]  + data[5]*m.data[5]  + data[6]*m.data[9]   + data[7]*m.data[13];
			r[6]  = data[4]*m.data[2]  + data[5]*m.data[6]  + data[6]*m.data[10]  + data[7]*m.data[14];
			r[7]  = data[4]*m.data[3]  + data[5]*m.data[7]  + data[6]*m.data[11]  + data[7]*m.data[15];

			r[8]  = data[8]*m.data[0]  + data[9]*m.data[4]  + data[10]*m.data[8]  + data[11]*m.data[12];
			r[9]  = data[8]*m.data[1]  + data[9]*m.data[5]  + data[10]*m.data[9]  + data[11]*m.data[13];
			r[10] = data[8]*m.data[2]  + data[9]*m.data[6]  + data[10]*m.data[10] + data[11]*m.data[14];
			r[11] = data[8]*m.data[3]  + data[9]*m.data[7]  + data[10]*m.data[11] + data[11]*m.data[15];

			r[12] = data[12]*m.data[0] + data[13]*m.data[4] + data[14]*m.data[8]  + data[15]*m.data[12];
			r[13] = data[12]*m.data[1] + data[13]*m.data[5] + data[14]*m.data[9]  + data[15]*m.data[13];
			r[14] = data[12]*m.data[2] + data[13]*m.data[6] + data[14]*m.data[10] + data[15]*m.data[14];
			r[15] = data[12]*m.data[3] + data[13]*m.data[7] + data[14]*m.data[11] + data[15]*m.data[15];
			Matrix16f* res = new Matrix16f(r);
			return *res;
		}

		void Matrix16f::transpose(){
			/*float res[16];
			for(int i=0; i<4; i++){
				for(int j=0; j<4; j++){
					res[4*j+i] = data[4*i+j];
				}
			}
			return *(new Matrix16f(res));*/
			int tmp;
			for(int i=0; i<3; i++){
				for(int j=i+1; j<4; j++){
					tmp = data[i*4+j];
					data[i*4+j] = data[j*4+i];
					data[j*4+i] = tmp;
				}
			}
		}
	};
};
