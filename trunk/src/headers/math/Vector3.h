#ifndef VECTOR3_H
#define VECTOR3_H

#include<iostream>

namespace siege{

	namespace math{
	
		class Vector4;
		class Matrix4;
		
		class Vector3{
			private:
				float x, y, z;
			public:
				Vector3();
				Vector3(const float, const float, const float);
				Vector3(const float*);
				Vector3(const Vector3&);
				float getX() const;
				float getY() const;
				float getZ() const;
				void setX(float);
				void setY(float);
				void setZ(float);
				virtual float& operator[](const int);
				virtual float* get(float*);
				virtual void set(const float*);
				friend  std::ostream& operator<<(std::ostream&, const Vector3&);
				Vector4 operator*(const Matrix4 &) const;
				Vector3& operator=(const Vector4 &);
		};//Vector3

	};//math

};//siege

#endif //VECTOR3F_H