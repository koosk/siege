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
				inline float getA() const;
				inline void setA(const float);
				inline float& operator[](const int);
				float* get(float*);
				void set(float*);
				friend std::ostream& siege::math::operator<<(std::ostream&, const Vector4&);
		}; //Vector4
		
		float Vector4::getA() const{
			return a;
		}

		void Vector4::setA(const  float f){
			a = f;
		}

		float& Vector4::operator[](const int i){
			if(i == 3)
				return a;
			return Vector3::operator[](i);
		}

	};//math
};//siege

#endif //VECTOR4F_H
