#ifndef VECTOR4_H
#define VECTOR4_H

#include"Vector3.h"

namespace siege{
	namespace math{

		class Vector4: public Vector3{
			private:
				float a;
			public:
				Vector4();
				Vector4(float, float, float, float);
				Vector4(const float*);
				Vector4(const Vector4&);
				Vector4(const Vector3&);
				float getA() const;
				void setA(float);
				float& operator[](const int);
				float* get(float*);
				void set(float*);
				friend std::ostream& siege::math::operator<<(std::ostream&, const Vector4&);
				virtual void normalize();
		}; //Vector4

	};//math
};//siege

#endif //VECTOR4F_H
