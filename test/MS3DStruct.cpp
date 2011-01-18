#include"gunit/MS3DStruct.h"
#include"math/Vector3f.h"
#include"utils.h"
#include<iostream>

using namespace std;
using namespace siege::gunit;

int main(){
	MS3DVertex ver;
	Vector3f vec(1,2,3);
	MS3DVertex ver2;
	ver2 = MS3DVertex(ver);
	ver.setVertex(vec);

	MS3DTriangle t;
	int a = t.getFlags();
	cout << "tri flag: "  << a << endl;
	a = t.getVertexIndex(1);
	cout << "tri 1 index: " << a << endl;
	siege::math::Vector3f v;
	v = t.getVertexNormal(1);
	cout << "tri 1 normal: "  << v << endl;

	MS3DMaterial mat;
	mat.setTexture((char*)"data/beast1.png");
	MS3DMaterial mat2 = mat;

	MS3DGroup g;

	try{
		g[0];
	}catch(exception &e){cout << e.what() << endl;}
	
	word tr[5] = {1,2,3,4,5};
	g.setTriangles(tr, 5);
	a = g.getNumberOfTriangles();
	cout << "Group numtri: " << a << endl;
	g.setTriangles(tr, 3);
	a = g.getNumberOfTriangles();
	cout << "Group numtri: " << a << endl;
	g.setTriangles(NULL, 0);

	MS3DGroup g1;
	MS3DGroup g2;
	word asd[3] = {1,2,3};
	g2.setTriangles(asd, 3);
	g1 = MS3DGroup(g2);

	MS3DJoint j;
	MS3DJoint j1;

	j= MS3DJoint(j1);

	return 0;
}
