#ifndef VECTOR4F_H
#define VECTOR4F_H

#include"Vector3f.h"

namespace siege{
	namespace math{

		class Vector4f: public Vector3f{
			private:
				float a;
			public:
				Vector4f();
				Vector4f(float, float, float, float);
				Vector4f(const float*);
				Vector4f(const Vector4f&);
				Vector4f(const Vector3f&);
				float getA() const;
				void setA(float);
				float& operator[](const int);
				float* get(float*);
				void set(float*);
				friend  std::ostream& siege::math::operator<<(std::ostream&, Vector4f&);
		}; //Vector4f

	};//math
};//siege

#endif //VECTOR4F_H
