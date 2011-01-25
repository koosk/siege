#include"gunit/MS3DStruct.h"
#include"math/Vector3.h"
#include"utils.h"
#include<iostream>

using namespace std;
using namespace siege::gunit;

int main(){
	{
	MS3DVertex ver;
	Vector3 vec(1,2,3);
	MS3DVertex ver2;
	ver2 = MS3DVertex(ver);
	ver.setVertex(vec);

	MS3DTriangle t;
	int a = t.getFlags();
	cout << "tri flag: "  << a << endl;
	a = t.getVertexIndex(1);
	cout << "tri 1 index: " << a << endl;
	siege::math::Vector3 v;
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
	g1 = g2;

	MS3DJoint j;
	MS3DJoint j1;

	j= j1;
	}
	//////////////////////
	cout << "==============================================================" << endl;
	Vector3* vector = new Vector3(1,1,1);
	MS3DVertex *v = new MS3DVertex(1, *vector, 1, 1);
	delete[] vector;
	delete[] v;

	Vector3 v1;
	Vector3 v2;
	Vector3 v3;
	Vector3 vv[3] = {v1,v2,v3}; 
	word w[3] = {1,2,3};
	MS3DTriangle* t = new MS3DTriangle(1, w, vv, v1, v2, 1, 2);
	delete t;

	MS3DGroup* gr = new MS3DGroup();
	delete gr;

	char* name = "adsasdas";	
	MS3DGroup* g = new MS3DGroup(1, name, 3, w, 1);
	delete g;

	Vector4 v4(1,1,1,1);
	MS3DMaterial* m = new MS3DMaterial(name, v4,v4,v4,v4, 1,1,1, (char*)"data/beas1.png", (char*)"asd");
	delete[] m;

	MS3DKeyFrame* kf = new MS3DKeyFrame(1, v1);
	delete[] kf;

	MS3DKeyFrame kf1(1, v2);
	MS3DKeyFrame kf2(2, v3);
	MS3DKeyFrame k[2] = {kf1, kf2};
	MS3DJoint* j = new MS3DJoint(1,1,name, NULL, v1, v2, 2, 2, k, k);
	delete j;

	return 0;
}
