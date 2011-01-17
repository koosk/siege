#ifndef MATRIX16F_H
#define MATRIX16F_H

#include "Vector3f.h"
#include "Vector4f.h"

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
				void set(const float*);
				void set(int, float);
				float operator[](int) const;
				Matrix16f& operator*(const Matrix16f &) const;
				friend Vector4f& Vector3f::operator*(const Matrix16f &) const;
				void transpose();
		};
	};
};

#endif //MATRIX16F_H
