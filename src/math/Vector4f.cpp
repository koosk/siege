#include"math/Vector4f.h"

namespace siege{
	namespace math{

		Vector4f::Vector4f():Vector3f(),a(0.0){};

		Vector4f::Vector4f(float b, float c, float d, float e):Vector3f(b, c, d){
			a = e;
		}

		Vector4f::Vector4f(float* f):Vector3f(f){
			a = f[3];
		}

		Vector4f::Vector4f(Vector4f& v){
			(*this)[0] = v[0];
			(*this)[1] = v[1];
			(*this)[2] = v[2];
			a = v.a;
		}

		Vector4f::Vector4f(Vector3f& v){
			(*this)[0] = v[0];
			(*this)[1] = v[1];
			(*this)[2] = v[2];
			a = 0.0;
		}

		float Vector4f::getA() const{
			return a;
		}

		void Vector4f::setA(float f){
			a = f;
		}

		float& Vector4f::operator[](int i){
			if(i == 3)
				return a;
			return Vector3f::operator[](i);
		}

		float* Vector4f::get(float* f){
			f[0] = (*this)[0];
			f[1] = (*this)[1];
			f[2] = (*this)[2];
			f[3] = a;
			return f;
		}

		void Vector4f::set(float* f){
			(*this)[0] = f[0];
			(*this)[1] = f[1];
			(*this)[2] = f[2];
			a = f[3];
		}
		std::ostream& operator<<(std::ostream& out, Vector4f& v){
			out << "Vector4f(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
			return out;
		}
	}; //math
}; //siege
