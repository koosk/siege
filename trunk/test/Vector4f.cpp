#include"math/Vector4f.h"
#include<iostream>
#include<exception>

using namespace std;
using namespace siege::math;

int main(){
	Vector4f* v = new Vector4f;
	delete v;
	Vector4f v2(1,2,3,4);
	Vector4f v3(2,5,7,8);
	float f[4];
	v2.get(f);
	cout << v2 << endl;
	v2[3] = 10;
	v2[0] = 45.5;
	cout << v2 << endl;
	v2 = v3;
	cout << v2 << endl;
	v2.set(f);
	cout << v2 << endl;
	try{
		v2[4];
	}catch(exception &e){cout << e.what()<<endl;}
	return 0;
}
