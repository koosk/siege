#ifndef MATRIX16F_H
#define MATRIX16F_H

#include <iostream>
#include "Vector3f.h"
#include "Vector4f.h"
#include "MathException.h"

namespace siege{
	namespace math{
		class Matrix16f{
			private:
				float data[16];
			public:
				Matrix16f();
				Matrix16f(const Matrix16f &);
				Matrix16f(const float*);
				~Matrix16f();
				Matrix16f& operator=(const Matrix16f &);
				void load(const float*);
				void loadTranspose(const float*);
				void set(int, float);
				float operator[](int) const;
				Matrix16f operator*(const Matrix16f &) const;
				Matrix16f operator*=(const Matrix16f &);
				friend Vector4f Vector3f::operator*(const Matrix16f &) const;
				Matrix16f transpose() const;
				friend std::ostream& operator<<(std::ostream&,const Matrix16f &);
				Matrix16f translate(const Vector3f &) const;
				Matrix16f rotate(const Vector3f &) const;
				Matrix16f scale(const Vector3f &) const;
				static float determinant3(const float*);
				float determinant() const;
				Matrix16f invert() const throw(MathException);
				friend Matrix16f operator*(float,const Matrix16f &);
				Matrix16f operator+(const Matrix16f &) const;
				Matrix16f operator-(const Matrix16f &) const;
				Matrix16f operator+=(const Matrix16f &);
				Matrix16f operator-=(const Matrix16f &);
				float getNormaF();
				Matrix16f normalize();
		};
	};
};

#endif //MATRIX16F_H
