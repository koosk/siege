#include <iostream>
#include "math/Matrix4.h"
#include "math/Vector3.h"
using namespace std;
using namespace siege::math;

double PI = 3.141592;

int main(){
	cout.precision(8);
	float mdata[16] = {1, 0  , 0   , 0,
		               0, 1  , -0.9, 0,
					   0, 0.9, 1   , 0,
					   0, 0  , 0   , 1};
	Matrix4 m(mdata);
	cout << m << endl;
	cout << m.invert() << endl;
	float md2[16] = {1,0,0,3,
	                 0,1,0,0,
	                 0,0,1,0,
	                 0,0,0,1
	};
	Matrix4 m2(md2);
	cout << m2*m << endl;
	cout << endl << "m determinansa: " << m.determinant() << endl;
	cout << "m2 determinansa: " << m2.determinant() << endl;
	cout << "m1 es m2 inverze: " << endl;
	cout << m.invert()  << endl;
	cout << m2.invert() << endl;
	cout << m2.transpose().invert() << endl;

	float detprb1[9] = {0,0,3,1,0,0,0,1,0};
	float detprb2[9] = {0,1,0,0,0,1,3,0,0};
	cout << Matrix4::determinant3(detprb1) << endl;
	cout << Matrix4::determinant3(detprb2) << endl;

	cout << "translate teszt:" << endl;
	float v1d[3] = {0,3,0};
	float v2d[3] = {-3,3,0};
	float v3d[3] = {3,2,4};
	Vector3 v1(v1d);
	Vector3 v2(v2d);
	Vector3 v3(v3d);
	Vector4 vres = v1*m2;
	cout << vres << endl;
	vres = v2*m2;
	cout << vres << endl;
	vres = v3*m2;
	cout << vres << endl;

	cout << endl << "rotate test" << endl;
	Matrix4 rotm1;
	Matrix4 rotm2;
	float rotd1[3] = {0,0,PI/2.};
	float rotd2[3] = {0,0,-PI/2.};
	Vector3 rotv1(rotd1);
	Vector3 rotv2(rotd2);
	rotm1 = rotm1.rotate(rotv1);
	rotm2 = rotm2.rotate(rotv2);
	float v1rd[3] = {1,0,0};
	float v2rd[3] = {0,1,0};
	float v3rd[3] = {0,0,1};
	Vector3 v1r(v1rd);
	Vector3 v2r(v2rd);
	Vector3 v3r(v3rd);

	vres = v1r*rotm1;
	cout << v1r << endl;
	cout << vres << endl;
	vres = v1r*rotm2;
	cout << vres << endl;

	vres = v2r*rotm1;
	cout << v2r << endl;
	cout << vres << endl;
	vres = v2r*rotm2;
	cout << vres << endl;

	vres = v3r*rotm1;
	cout << v3r << endl;
	cout << vres << endl;
	vres = v3r*rotm2;
	cout << vres << endl;

	cout << endl << "scale test" << endl;
	Matrix4 scalem1;
	float scaled1[3] = {1,1,1};
	Vector3 scalev1(scaled1);
	scalem1 = scalem1.scale(scalev1);
	vres = v1r*scalem1;
	cout << vres << endl;

	float v2sd1[3] = {1,1,1};
	Vector3 v2s1(v2sd1);
	float scaled2[3] = {2,2,2};
	Vector3 scalev2(scaled2);
	scalem1 = scalem1.scale(scalev2);
	vres = v2s1*scalem1;
	cout << vres << endl;

	float v2sd2[3] = {0.9,-2,3};
	Vector3 v2s2(v2sd2);
	float scaled3[3] = {-2,2,-1};
	Vector3 scalev3(scaled3);

	Matrix4 scalem2;
	scalem2 = scalem2.scale(scalev3);
	cout << endl << scalem2 << endl;
	//vres = v2s2*scalem2;
	//cout << vres << endl;
	cout << v2s2*scalem2 << endl;

	return 0;
}
