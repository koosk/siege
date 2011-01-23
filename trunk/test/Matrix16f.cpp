#include <iostream>
#include "math/Matrix16f.h"
#include "math/Vector3f.h"
using namespace std;
using namespace siege::math;

int main(){
	cout.precision(8);
	float mdata[16] = {1, 0  , 0   , 0,
		               0, 1  , -0.9, 0,
					   0, 0.9, 1   , 0,
					   0, 0  , 0   , 1};
	Matrix16f m(mdata);
	cout << m << endl;
	cout << m.invert() << endl;
	float md2[16] = {1,0,0,3,
	                 0,1,0,0,
	                 0,0,1,0,
	                 0,0,0,1
	};
	Matrix16f m2(md2);
	float v1d[3] = {0,3,0};
	float v2d[3] = {-3,0,0};
	float v3d[3] = {3,0,0};
	Vector3f v1(v1d);
	Vector3f v2(v2d);
	Vector3f v3(v3d);
	/*Vector4f vres = v1*m2;
	cout << vres << endl;
	vres = v2*m2;
	cout << vres << endl;
	vres = v3*m2;
	cout << vres << endl;*/
	cout << m2*m << endl;
	cout << endl << "m determinansa: " << m.determinant() << endl;
	cout << "m2 determinansa: " << m2.determinant() << endl;
	cout << "m1 es m2 inverze: " << endl;
	cout << m.invert()  << endl;
	cout << m2.invert() << endl;
	cout << m2.transpose().invert() << endl;

	float detprb1[9] = {0,0,3,1,0,0,0,1,0};
	float detprb2[9] = {0,1,0,0,0,1,3,0,0};
	cout << Matrix16f::determinant3(detprb1) << endl;
	cout << Matrix16f::determinant3(detprb2) << endl;
		

	return 0;
}
