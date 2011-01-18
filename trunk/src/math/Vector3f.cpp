#include "math/Vector3f.h"
#include "BadIndexException.h"
#include "math/Vector4f.h"
#include "math/Matrix16f.h"

namespace siege{
	namespace math{

		Vector3f::Vector3f():x(0.0),y(0.0),z(0.0){
		}

		Vector3f::Vector3f(float a, float b, float c):x(a),y(b),z(c){
		}

		Vector3f::Vector3f(float* a){
			x = a[0];	
			y = a[1];	
			z = a[2];	
		}

		Vector3f::Vector3f(Vector3f &v){
			x = v.x;
			y = v.y;
			z = v.z;
		}

		float Vector3f::getX() const{
			return x;
		}

		float Vector3f::getY() const{
			return y;
		}

		float Vector3f::getZ() const{
			return z;
		}

		void Vector3f::setX(float a){
			x = a;
		}

		void Vector3f::setY(float a){
			y = a;
		}

		void Vector3f::setZ(float a){
			z = a;
		}

		float& Vector3f::operator[](const int i){
			if(i == 0)
				return x;
			if(i == 1)
				return y;
			if(i == 2)
				return z;
			
			throw siege::BadIndexException();
		}

		float* Vector3f::get(float* f){
			f[0] = x;
			f[1] = y;
			f[2] = z;
			return f;
		}

		void Vector3f::set(float* f){
			x = f[0];	
			y = f[1];	
			z = f[2];	
		}
		std::ostream& operator<<(std::ostream& out, Vector3f& v){
			out << "Vector3f(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
			return out;
		}
		
		Vector4f& Vector3f::operator*(const Matrix16f &m) const{
			float r[4];
			r[0] = x*m.data[0]  + y*m.data[1]  + z*m.data[2]  + m.data[3];
			r[1] = x*m.data[4]  + y*m.data[5]  + z*m.data[6]  + m.data[7];
			r[2] = x*m.data[8]  + y*m.data[9]  + z*m.data[10] + m.data[11];
			r[3] = x*m.data[12] + y*m.data[13] + z*m.data[14] + m.data[15];
			return *(new Vector4f(r));
		}
	};//math
};//siege
