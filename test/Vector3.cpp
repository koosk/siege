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
	return 0;
}
