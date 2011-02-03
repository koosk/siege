#ifndef VECTOR3_H
#define VECTOR3_H

#include<iostream>
#include "BadIndexException.h"

namespace siege{

	namespace math{
	
		class Vector4;
		class Matrix4;
		
		class Vector3{
			private:
				float x, y, z;
			public:
				friend std::ostream& operator<<(std::ostream&, const Vector3&);
				friend Vector3 operator*(const float, const Vector3&);

				Vector3();
				Vector3(const float, const float, const float);
				Vector3(const float*);
				Vector3(const Vector3&);
				inline float getX() const;
				inline float getY() const;
				inline float getZ() const;
				inline void setX(const float);
				inline void setY(const float);
				inline void setZ(const float);
				inline virtual float& operator[](const int);
				virtual float* get(float*) const;
				virtual void set(const float*);
				Vector4 operator*(const Matrix4 &) const;
				Vector3& operator=(const Vector4 &);
				bool operator==(Vector3) const;
				bool operator<(Vector3) const;
				bool operator>(Vector3) const;
				bool operator<=(Vector3) const;
				bool operator>=(Vector3) const;
				void normalize();
				void swapYZ();
				Vector3 operator-() const;
				Vector3 crossProduct(const Vector3 &) const;
				Vector3 operator-(const Vector3 &) const;
				Vector3 operator+(const Vector3 &) const;
				Vector3& operator+=(const Vector3 &);
				Vector3& operator-=(const Vector3 &);
				Vector3 operator*(const float) const;
				virtual float length() const;
		};//Vector3
		
		float Vector3::getX() const{
			return x;
		}

		float Vector3::getY() const{
			return y;
		}

		float Vector3::getZ() const{
			return z;
		}

		void Vector3::setX(const float a){
			x = a;
		}

		void Vector3::setY(const float a){
			y = a;
		}

		void Vector3::setZ(const float a){
			z = a;
		}
		
		float& Vector3::operator[](const int i){
			if(i == 0)
				return x;
			if(i == 1)
				return y;
			if(i == 2)
				return z;
			
			throw siege::BadIndexException();
		}

	};//math

};//siege

#endif //VECTOR3F_H
