#include"gunit/BSPStruct.h"
#include<iostream>

using namespace siege::gunit;
using namespace std;

int main(){
	BSPPolygon p(NULL, NULL, NULL, 0, NULL, 0, NULL, NULL, NULL, Vector3(1,2,3), Vector3(), Vector3(), Vector3());
	cout << p.getNormal() << endl;
	BSPPolygon p2;
	p2 = p;
	cout << p2.getNormal() << endl;
	BSPPolygon p3(p2);
	cout << p3.getNormal() << endl;

	BSPNode* n =  new BSPNode[4205];
	delete[] n;

	siege::scene::BoundingBox b(siege::math::Vector3(1,2,3), siege::math::Vector3(4,5,6));

	return 0;
}
