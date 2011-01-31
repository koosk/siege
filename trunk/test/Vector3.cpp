#include<iostream>
#include"math/Vector3.h"

using namespace std;
using namespace siege::math;

int main(){
	Vector3* v = new Vector3();
	delete v;
	float f[3] = {1, 2, 5};
	Vector3 v2(f);
	cout << v2 << endl;
	v2[1] = 10;
	cout << v2 << endl;
	
	//crossProduct teszt
	cout.precision(12);
	cout << "crossProduct teszt" << endl;
	Vector3 v1cp(1,0,0);
	Vector3 v2cp(0,1,0);
	Vector3 v3cp(0,0,1);
	cout << v1cp << " x " << v2cp << " = " << v1cp.crossProduct(v2cp) << endl;
	cout << v2cp << " x " << v1cp << " = " << v2cp.crossProduct(v1cp) << endl;
	cout << v2cp << " x " << v3cp << " = " << v2cp.crossProduct(v3cp) << endl;
	cout << v3cp << " x " << v2cp << " = " << v3cp.crossProduct(v2cp) << endl;
	cout << v3cp << " x " << v1cp << " = " << v3cp.crossProduct(v1cp) << endl;
	cout << v1cp << " x " << v3cp << " = " << v1cp.crossProduct(v3cp) << endl;
	cout << "---------------------------------" << endl;
	Vector3 v1cp2(1,0.001,0);
	cout << v1cp << " x " << v1cp2 << " = " << v1cp.crossProduct(v1cp2) << endl;

	return 0;
}
