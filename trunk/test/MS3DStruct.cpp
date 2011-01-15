#include"gunit/MS3DStruct.h"
#include"math/Vector3f.h"
#include"utils.h"
#include<iostream>

using namespace std;
using namespace siege::gunit;

int main(){
	MS3DTriangle t;
	int a = t.getFlags();
	cout << "tri flag: "  << a << endl;
	a = t.getVertexIndex(1);
	cout << "tri 1 index: " << a << endl;
	siege::math::Vector3f v;
	v = t.getVertexNormal(1);
	cout << "tri 1 normal: "  << v << endl;

	MS3DGroup g;
	
	word tr[5] = {1,2,3,4,5};
	g.setTriangles(tr, 5);
	a = g.getNumberOfTriangles();
	cout << "Group numtri: " << a << endl;
	g.setTriangles(tr, 3);
	a = g.getNumberOfTriangles();
	cout << "Group numtri: " << a << endl;

	return 0;
}
