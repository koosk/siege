#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix4.h"
#include <cmath>
#define sqr(x) (x*x)
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

		bool Vector3::operator==(Vector3 v) const{
			return x == v.x && y == v.y && z == v.z;
		}

		bool Vector3::operator<(Vector3 v) const{
			return x < v.x && y < v.y && z < v.z;
		}

		bool Vector3::operator>(Vector3 v) const{
			return x > v.x && y > v.y && z > v.z;
		}

		bool Vector3::operator<=(Vector3 v) const{
			return *this < v || *this == v;
		}

		bool Vector3::operator>=(Vector3 v) const{
			return *this > v || *this == v;
		}
		
		void Vector3::normalize(){
			float d = sqrt(x*x+y*y+z*z);
			x = x/d;
			y = y/d;
			z = z/d;
		}

		void Vector3::swapYZ(){
			float f = y;
			y = z;
			z = f;
		}
		
		Vector3 Vector3::operator-() const{
			return Vector3(-x,-y,-z);
		};

		Vector3 Vector3::crossProduct(const Vector3 &v) const{
			return Vector3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
		}
		
		Vector3 Vector3::operator-(const Vector3 &v) const{
			return Vector3(x-v.x, y-v.y, z-v.z);
		}
		
		Vector3 Vector3::operator+(const Vector3 &v) const{
			return Vector3(x+v.x, y+v.y, z+v.z);
		}
		
		Vector3& Vector3::operator+=(const Vector3 &v){
			*this = *this + v;
			return *this;
		}
		
		Vector3& Vector3::operator-=(const Vector3 &v){
			*this = *this - v;
			return *this;
		}
		
		Vector3 Vector3::operator*(const float a) const{
			return Vector3(x*a, y*a, z*a);
		}
		
		Vector3 operator*(const float a, const Vector3 &v){
			return Vector3(v.x*a, v.y*a, v.z*a);
		}

		float Vector3::length() const{
			return sqrt(sqr(x)+sqr(y)+sqr(z));
		}
	};//math
};//siege
#undef sqr
