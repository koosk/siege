#include<iostream>
#include"math/Vector3f.h"

using namespace std;
using namespace siege::math;

int main(){
	Vector3f* v = new Vector3f();
	delete v;
	float f[3] = {1, 2, 5};
	Vector3f v2(f);
	cout << v2 << endl;
	v2[1] = 10;
	cout << v2 << endl;
	return 0;
}
