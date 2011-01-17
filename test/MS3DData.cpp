#include"gunit/MS3DData.h"
#include<exception>
#include<fstream>

using namespace std;
using namespace siege::gunit;

int main(){
	MS3DData m;
	ifstream in("data/beast.ms3d", ios::in | ios::binary);
	if(!in.is_open()){
		cout << "nem sikerult megnyitni" << endl;
		return 1;
	}
	try{
		in >> m;
	}catch(exception &e){cout << e.what() << endl;}
	in.close();
	return 0;
}
