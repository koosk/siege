#include <iostream>
#include "math/Matrix16f.h"
#include "math/Vector3f.h"
using namespace std;
using namespace siege::math;

int main(){
	Matrix16f mtx;
	cout << mtx << endl;
	float vd[3] = {1.f,2.f,3.f};
	Vector3f v(vd);
	mtx = mtx.translate(v);
	cout << mtx << endl;
	cout << "transzponalt:" << endl;
	cout << mtx.transpose() << endl;
	//float md[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	float md[16] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
	/*float md[16] = {1,0,0,4,
		            0,1,0,5,
	                0,0,1,6,
	                0,0,0,1};*/
	mtx.loadTranspose(md);
	cout << "transzponalt betoltes:" << endl;
	cout << mtx << endl;
	mtx.load(md);
	//mtx.set(4,19);
	cout << mtx << endl;
	Matrix16f mtx2;
	cout << mtx2*mtx << endl;
	Matrix16f onemtx = mtx2*mtx;

	float mtransl[16] = {1,0,0,1,
		                 0,1,0,1,
	                     0,0,1,1,
	                     0,0,0,1};
	mtx2.load(mtransl);
	cout << mtx2 << endl;
	cout << mtx*mtx2 << endl;
	Matrix16f m3;
	cout << m3*mtx2 << endl;
	//cout << "vektor*matrix:" << endl;
	//Vector4f v2 = v*mtx2;
	

	return 0;
}
