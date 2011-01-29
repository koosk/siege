#include"math/Vector4.h"

namespace siege{
	namespace math{

		Vector4::Vector4():Vector3(),a(0.0){};

		Vector4::Vector4(float b, float c, float d, float e):Vector3(b, c, d){
			a = e;
		}

		Vector4::Vector4(const float* f):Vector3(f){
			a = f[3];
		}

		Vector4::Vector4(const Vector4& v){
			setX(v.getX());
			setY(v.getY());
			setZ(v.getZ());
			a = v.a;
		}

		Vector4::Vector4(const Vector3& v){
			setX(v.getX());
			setY(v.getY());
			setZ(v.getZ());
			a = 0.0;
		}

		float Vector4::getA() const{
			return a;
		}

		void Vector4::setA(float f){
			a = f;
		}

		float& Vector4::operator[](int i){
			if(i == 3)
				return a;
			return Vector3::operator[](i);
		}

		float* Vector4::get(float* f){
			f[0] = (*this)[0];
			f[1] = (*this)[1];
			f[2] = (*this)[2];
			f[3] = a;
			return f;
		}

		void Vector4::set(float* f){
			(*this)[0] = f[0];
			(*this)[1] = f[1];
			(*this)[2] = f[2];
			a = f[3];
		}
		
		std::ostream& operator<<(std::ostream& out, const Vector4& v){
			//out << "Vector4(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
			out << "Vector4(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ", " << v.getA() << ")";
			return out;
		}

		void Vector4::normalize(){
			float d = getX()*getX() + getY()*getY() + getZ()*getZ() + a*a;
			setX(getX()/d);
			setY(getY()/d);
			setZ(getZ()/d);
			a = a/d;
		}
	}; //math
}; //siege
