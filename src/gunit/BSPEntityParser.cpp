#include"gunit/BSPEntityParser.h"
#include<string.h>
#include"stdlib.h"

#include<iostream>

namespace siege{
	namespace gunit{

		using namespace std;

		BSPEntityParser::BSPEntityParser(){}

		BSPEntityParser::BSPEntityParser(char const* d){
			parse(d);
		}

		void BSPEntityParser::parse(char const* d){
			data.resize(0);
			size_t pos;
			for(unsigned int i=0; i<=strlen(d); i++){
				if(d[i] == '{'){
					i += 2;
					pos = i;
				}
				else if(d[i] == '}'){
					char c[i-pos];
					memcpy(c, &d[pos], i-pos-1);
					c[i-pos-1] = 0;
					data.push_back(string(c));
				}
			}
			/*list<string>::iterator it = data.begin();
			while(it != data.end()){
				cout << *it << endl;
				it++;
			}*/
		}

		string BSPEntityParser::getValue(string ent, string attr) const{
			size_t pos = ent.find(attr);
			if(pos == string::npos)
				return string();
			pos = ent.find('"', pos+attr.size()+2) + 1;
			size_t pos2 = ent.find('"', pos);
			return ent.substr(pos, pos2-1);
		}
		
		list<string> BSPEntityParser::getEntities(string attr, string val) const{
			list<string> li;
			list<string>::const_iterator it = data.begin();
			while(it != data.end()){
				if(getValue(*it, attr).find(val) != string::npos){
					li.push_back(*it);
					//cout << *it << endl;
				}
				it++;
			}
			return li;
		}

		vector<math::Vector4> BSPEntityParser::getAllSpawnPoints() const{
			list<string> li =  getEntities("classname" ,"info_player");
			list<string>::iterator it = li.begin();
			vector<math::Vector4> vec;
			while(it != li.end()){
				string s = getValue(*it, "origin");
				size_t pos = s.find(' ');
				float f[4];
				f[0] = atof(s.substr(0, pos).data());
				int i = 1;
				do{
					size_t tm = s.find(' ', pos+1);
					f[i] = atof(s.substr(pos+1, tm-1).data());
					pos = tm;
					i++;
				}while(pos != string::npos);
				f[3] = atof(getValue(*it, "angle").data());
				math::Vector4 v(f);
				v.swapYZ();
				vec.push_back(v);
				it++;
			}
			return vec;
		}

	}; //gunit
}; //siege
