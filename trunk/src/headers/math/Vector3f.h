#ifndef VECTOR3F_H
#define VECTOR3F_H

#include<iostream>

namespace siege{

	namespace math{
	
		class Vector3f{
			private:
				float x, y, z;
			public:
				Vector3f();
				Vector3f(float, float, float);
				Vector3f(float*);
				Vector3f(Vector3f&);
				float getX();
				float getY();
				float getZ();
				void setX(float);
				void setY(float);
				void setZ(float);
				float& operator[](const int);
				virtual float* get(float*);
				virtual void set(float*);
				friend  std::ostream& siege::math::operator<<(std::ostream&, Vector3f&);
		}; //Vector3f

	}; //math

}; //siege

#endif //VECTOR3F_H
