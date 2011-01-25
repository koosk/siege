#include "math/Vector3.h"
#include "BadIndexException.h"
#include "math/Vector4.h"
#include "math/Matrix4.h"

namespace siege{
	namespace math{

		Vector3::Vector3():x(0.0),y(0.0),z(0.0){
		}

		Vector3::Vector3(const float a, const float b, const float c):x(a),y(b),z(c){
		}

		Vector3::Vector3(const float* a){
			x = a[0];	
			y = a[1];	
			z = a[2];	
		}

		Vector3::Vector3(const Vector3 &v){
			x = v.x;
			y = v.y;
			z = v.z;
		}

		float Vector3::getX() const{
			return x;
		}

		float Vector3::getY() const{
			return y;
		}

		float Vector3::getZ() const{
			return z;
		}

		void Vector3::setX(float a){
			x = a;
		}

		void Vector3::setY(float a){
			y = a;
		}

		void Vector3::setZ(float a){
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

		float* Vector3::get(float* f){
			f[0] = x;
			f[1] = y;
			f[2] = z;
			return f;
		}

		void Vector3::set(const float* f){
			x = f[0];	
			y = f[1];	
			z = f[2];	
		}

		std::ostream& operator<<(std::ostream& out, const Vector3& v){
			//out << "Vector3(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
			out << "Vector3(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
			return out;
		}
		
		Vector4 Vector3::operator*(const Matrix4 &m) const{
			float r[4];
			r[0] = x*m.data[0]  + y*m.data[1]  + z*m.data[2]  + m.data[3];
			r[1] = x*m.data[4]  + y*m.data[5]  + z*m.data[6]  + m.data[7];
			r[2] = x*m.data[8]  + y*m.data[9]  + z*m.data[10] + m.data[11];
			r[3] = x*m.data[12] + y*m.data[13] + z*m.data[14] + m.data[15];
			Vector4 v(r);
			return v;
		}
		
		Vector3& Vector3::operator=(const Vector4 &v){
			x = v.getX();
			y = v.getY();
			z = v.getZ();
			return *this;
		}
	};//math
};//siege
