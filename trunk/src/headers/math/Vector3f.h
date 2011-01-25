#ifndef VECTOR3F_H
#define VECTOR3F_H

#include<iostream>

namespace siege{

	namespace math{
	
		class Vector4f;
		class Matrix16f;
		
		class Vector3f{
			private:
				float x, y, z;
			public:
				Vector3f();
				Vector3f(const float, const float, const float);
				Vector3f(const float*);
				Vector3f(const Vector3f&);
				float getX() const;
				float getY() const;
				float getZ() const;
				void setX(float);
				void setY(float);
				void setZ(float);
				virtual float& operator[](const int);
				virtual float* get(float*);
				virtual void set(const float*);
				friend  std::ostream& operator<<(std::ostream&, const Vector3f&);
				Vector4f operator*(const Matrix16f &) const;
				Vector3f& operator=(const Vector4f &);
		};//Vector3f

	};//math

};//siege

#endif //VECTOR3F_H
