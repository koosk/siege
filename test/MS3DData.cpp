#include"gunit/MS3DData.h"
#include<exception>

using namespace std;
using namespace siege::gunit;

int main(){
	MS3DData m;
	try{
		m.load((char*)"data/beast.ms3d");
	}catch(exception &e){cout << e.what() << endl;}
	MS3DData* dat = new MS3DData();
	dat->load((char*)"data/beast.ms3d");
	//delete[] dat;
	return 0;
}
