#ifndef MATRIX16_H
#define MATRIX16_H

#include <iostream>
#include "Vector3.h"
#include "Vector4.h"
#include "BadIndexException.h"
#include "MathException.h"

namespace siege{
	namespace math{
		class Matrix4{
			private:
				float data[16];
			public:
				Matrix4();
				Matrix4(const Matrix4 &);
				Matrix4(const float*);
				~Matrix4();
				Matrix4& operator=(const Matrix4 &);
				void load(const float*);
				void loadTranspose(const float*);
				inline void set(int, float);
				inline float operator[](int) const;
				Matrix4 operator*(const Matrix4 &) const;
				Matrix4 operator*=(const Matrix4 &);
				friend Vector4 Vector3::operator*(const Matrix4 &) const;
				Matrix4 transpose() const;
				friend std::ostream& operator<<(std::ostream&,const Matrix4 &);
				Matrix4 translate(const Vector3 &) const;
				Matrix4 rotate(const Vector3 &) const;
				Matrix4 scale(const Vector3 &) const;
				static float determinant3(const float*);
				float determinant() const;
				Matrix4 invert() const throw(MathException);
				friend Matrix4 operator*(float,const Matrix4 &);
				Matrix4 operator+(const Matrix4 &) const;
				Matrix4 operator-(const Matrix4 &) const;
				Matrix4 operator+=(const Matrix4 &);
				Matrix4 operator-=(const Matrix4 &);
				float getNormaF();
				Matrix4 normalize();
				static Matrix4 identity();
				Matrix4& loadIdentity();
				static Matrix4 translation(const Vector3 &);
				static Matrix4 rotation(const Vector3 &);
				static Matrix4 scaling(const Vector3 &);
		};//class Matrix4

		void Matrix4::set(int pos, float value){
			if(pos>15){
				throw siege::BadIndexException();
			}
			data[pos] = value;
		}

		float Matrix4::operator[](int index) const{//index from 0
			if(index>15 || index<0){
				throw siege::BadIndexException();
			}
			return data[index];
		}
		

	};//namespace math
};//namespace siege

#endif //MATRIX16F_H
