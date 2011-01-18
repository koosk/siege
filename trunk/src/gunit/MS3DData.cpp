#include"gunit/MS3DData.h"
#include"BadIndexException.h"
#include"gunit/MS3DException.h"
#include<string.h>
#include<string>
#include<fstream>

namespace siege{
	namespace gunit{

		void MS3DData::init(word vernum=0, word trinum=0, word grunum=0, word matnum=0, word joinum=0){
			initVertices(vernum);
			initTriangles(trinum);
			initGroups(grunum);
			initMaterials(matnum);
			initJoints(joinum);
		}

		void MS3DData::initVertices(word n){
			numVertices = n;
			if(n == 0){
				if(vertices != NULL){
					delete[] vertices;
					vertices = NULL;
				}
				return;
			}
			if(vertices != NULL)
				delete[] vertices;
			vertices = new MS3DVertex[n];
		}

		void MS3DData::initTriangles(word n){
			numTriangles = n;
			if(n == 0){
				if(triangles != NULL){
					delete[] triangles;
					triangles = NULL;
				}
				return;
			}
			if(triangles != NULL)
				delete[] triangles;
			triangles = new MS3DTriangle[n];
		}

		void MS3DData::initGroups(word n){
			numGroups = n;
			if(n == 0){
				if(groups != NULL){
					delete[] groups;
					groups = NULL;
				}
				return;
			}
			if(groups != NULL)
				delete[] groups;
			groups = new MS3DGroup[n];
		}

		void MS3DData::initMaterials(word n){
			numMaterials = n;
			if(n == 0){
				if(materials != NULL){
					delete[] materials;
					materials = NULL;
				}
				return;
			}
			if(materials != NULL)
				delete[] materials;
			materials = new MS3DMaterial[n];
		}

		void MS3DData::initJoints(word n){
			numJoints = n;
			if(n == 0){
				if(joints != NULL){
					delete[] joints;
					joints = NULL;
				}
				return;
			}
			if(joints != NULL)
				delete[] joints;
			joints = new MS3DJoint[n];
		}

		void MS3DData::free(){
			init();
		}

		void MS3DData::setVersion(int v){
			version = v;
		}

		void MS3DData::setVertex(MS3DVertex& ms, word i){
			if(i<0 || i>=numVertices)
				throw BadIndexException();
			vertices[i] = ms;
		}

		void MS3DData::setTriangle(MS3DTriangle& ms, word i){
			if(i<0 || i>=numTriangles)
				throw BadIndexException();
			triangles[i] = ms;
		}

		void MS3DData::setGroup(MS3DGroup& ms, word i){
			if(i<0 || i>=numGroups)
				throw BadIndexException();
			groups[i] = ms;
		}

		void MS3DData::setMaterial(MS3DMaterial& ms, word i){
			if(i<0 || i>=numMaterials)
				throw BadIndexException();
			materials[i] = ms;
		}

		void MS3DData::setJoint(MS3DJoint& ms, word i){
			if(i<0 || i>=numJoints)
				throw BadIndexException();
			joints[i] = ms;
		}

		void MS3DData::setFPS(float f){
			fps = f;
		}

		void MS3DData::setTotalFrames(int n){
			totalFrames = n;
		}

		MS3DJoint* MS3DData::getJointParent(MS3DJoint& j){
			if(j.getParent() == NULL)
				return NULL;
			for(int i=0; i<numJoints; i++){
				if(strcmp(joints[i].getName(), j.getParent()->getName()) == 0)
					return &joints[i];
			}
			return NULL;
		}

		MS3DJoint* MS3DData::getJointParent(char* name){
			for(int i=0; i<numJoints; i++){
				if(strcmp(joints[i].getName(), name) == 0)
					return &joints[i];
			}
			return NULL;
		}

		MS3DData::MS3DData(){
			vertices = NULL;
			triangles = NULL;
			groups = NULL;
			materials = NULL;
			joints = NULL;
			init();
		}

		MS3DData::MS3DData(MS3DData& md){
			vertices = NULL;
			triangles = NULL;
			groups = NULL;
			materials = NULL;
			joints = NULL;
			init(md.numVertices, md.numTriangles, md.numGroups, md.numMaterials, md.numJoints);
			//memcpy(vertices, md.vertices, numVertices);
			//memcpy(triangles, md.triangles, numTriangles);
			//memcpy(groups, md.groups, numGroups);
			//memcpy(materials, md.materials, numMaterials);
			for(int i=0; i<numVertices; i++)
				vertices[i] = md.vertices[i];
			for(int i=0; i<numTriangles; i++)
				triangles[i] = md.triangles[i];
			for(int i=0; i<numGroups; i++)
				groups[i] = md.groups[i];
			for(int i=0; i<numMaterials; i++)
				materials[i] = md.materials[i];
			for(int i=0; i<numJoints; i++){
				joints[i] = md.joints[i];
				joints[i].setParent(getJointParent(joints[i]));
			}
		}

		MS3DData::~MS3DData(){
			free();
		}

		int MS3DData::getVersion(){
			return version;
		}

		word MS3DData::getNumberOfVertices(){
			return numVertices;
		}

		word MS3DData::getNumberOfTriangles(){
			return numTriangles;
		}

		word MS3DData::getNumberOfGroups(){
			return numGroups;
		}

		word MS3DData::getNumberOfMaterials(){
			return numMaterials;
		}

		word MS3DData::getNumberOfJoints(){
			return numVertices;
		}

		MS3DVertex* MS3DData::getVertex(word i){
			if(i<0 || i>=numVertices)
				throw BadIndexException("Wrong index in MS3DData while getting vertex!");
			return &vertices[i];
		}

		MS3DTriangle* MS3DData::getTriangle(word i){
			if(i<0 || i>=numTriangles)
				throw BadIndexException("Wrong index in MS3DData while getting triangle!");
			return &triangles[i];
		}

		MS3DGroup* MS3DData::getGroup(word i){
			if(i<0 || i>=numGroups)
				throw BadIndexException("Wrong index in MS3DData while getting group!");
			return &groups[i];
		}

		MS3DMaterial* MS3DData::getMaterial(word i){
			if(i<0 || i>=numMaterials)
				throw BadIndexException("Wrong index in MS3DData while getting material!");
			return &materials[i];
		}

		MS3DJoint* MS3DData::getJoint(word i){
			if(i<0 || i>=numJoints)
				throw BadIndexException("Wrong index in MS3DData while getting joint!");
			return &joints[i];
		}

		float MS3DData::getFPS(){
			return fps;
		}

		int MS3DData::getTotalFrames(){
			return totalFrames;
		}

		void MS3DData::load(char* file ){
			std::ifstream in(file, std::ios::in | std::ios::binary);
			if(!in.is_open()){
				std::string ms("The file cannot be opened or the path is not valid: ");
				ms.append(file);
				throw MS3DException(ms);
			}

			in.seekg(0, std::ios::end);
			long size = in.tellg();
			in.seekg(0, std::ios::beg);

			char* buffer = new char[size];
			in.read(buffer, size);
			char* ptr = buffer;
			in.close();

			/////////////HEADER/////////////////////////
			char mid[10];
			memcpy(mid, ptr, sizeof(mid));
			ptr += sizeof(mid);
			if(strncmp(mid, "MS3D000000", 10) != 0)
				throw MS3DException("Not a valid Milkshape model data!");
			memcpy(&version, ptr, sizeof(version));
			ptr += sizeof(version);
			if(version < 3 || version > 4){
				throw MS3DException("Unhandled version!");
			}
			
			////////////VERTICES//////////////////////
			memcpy(&numVertices, ptr, sizeof(numVertices));
			ptr += sizeof(numVertices);
			initVertices(numVertices);
			for(int i=0; i<numVertices; i++){
				byte btmp;
				memcpy(&btmp, ptr, sizeof(byte));
				ptr += sizeof(byte);
				float ftmp[3];
				memcpy(ftmp, ptr, sizeof(ftmp));
				ptr += sizeof(ftmp);
				char ctmp;
				memcpy(&ctmp, ptr, sizeof(ctmp));
				ptr += sizeof(ctmp);
				byte refc;
				memcpy(&refc, ptr, sizeof(refc));
				ptr += sizeof(refc);
				Vector3f v(ftmp);
				vertices[i] = MS3DVertex(btmp, v, ctmp, refc);
			}
			//////////////TRIANGLES////////////////////
			memcpy(&numTriangles, ptr, sizeof(numTriangles));
			ptr += sizeof(numTriangles);
			initTriangles(numTriangles);
			for(int i=0; i<numTriangles; i++){
				word flag;
				memcpy(&flag, ptr, sizeof(flag));
				ptr += sizeof(flag);
				word vi[3];
				memcpy(vi, ptr, sizeof(vi));
				ptr += sizeof(vi);
				Vector3f vec[3];
				for(int k=0; k<3; k++){
					float f[3];
					memcpy(f, ptr, sizeof(f));
					ptr += sizeof(f);
					vec[k] = Vector3f(f);
				}
				float f[3];
				memcpy(f, ptr, sizeof(f));
				ptr += sizeof(f);
				Vector3f s(f);
				memcpy(f, ptr, sizeof(f));
				ptr += sizeof(f);
				Vector3f t(f);
				byte sg;
				memcpy(&sg, ptr, sizeof(sg));
				ptr += sizeof(sg);
				byte gr;
				memcpy(&gr, ptr, sizeof(gr));
				ptr += sizeof(gr);
				MS3DTriangle tri(flag, vi, vec, s, t, sg, gr);
				triangles[i] = tri;
			}
			///////////////////GROUPS/////////////////
			memcpy(&numGroups, ptr, sizeof(numGroups));
			ptr += sizeof(numGroups);
			initGroups(numGroups);
			for(int i=0; i<numGroups; i++){
				byte flag;
				memcpy(&flag, ptr, sizeof(flag));
				ptr += sizeof(flag);
				char name[32];
				memcpy(name, ptr, sizeof(name));
				ptr += sizeof(name);
				word nt;
				memcpy(&nt, ptr, sizeof(nt));
				ptr += sizeof(nt);
				word ti[nt];
				for(int k=0; k<nt; k++){
					memcpy(&ti[k], ptr, sizeof(word));
					ptr += sizeof(word);
				}
				char mi;
				memcpy(&mi, ptr, sizeof(mi));
				ptr += sizeof(mi);
				groups[i] =  MS3DGroup(flag, name, nt, ti ,mi);
			}
			///////////////////////MATERIAL////////////
			memcpy(&numMaterials, ptr, sizeof(numMaterials));
			ptr += sizeof(numMaterials);
			initMaterials(numMaterials);
			std::string dpath(file);
			dpath = dpath.substr(0, dpath.find_last_of("/\\")+1);
			for(int i=0; i<numMaterials; i++){
				char name[32];
				memcpy(name, ptr, sizeof(name));
				ptr += sizeof(name);
				float f[4];
				memcpy(f, ptr, sizeof(f));
				ptr += sizeof(f);
				Vector4f amb(f);
				memcpy(f, ptr, sizeof(f));
				ptr += sizeof(f);
				Vector4f dif(f);
				memcpy(f, ptr, sizeof(f));
				ptr += sizeof(f);
				Vector4f spe(f);
				memcpy(f, ptr, sizeof(f));
				ptr += sizeof(f);
				Vector4f emi(f);
				float sh;
				memcpy(&sh, ptr, sizeof(sh));
				ptr += sizeof(sh);
				float tr;
				memcpy(&tr, ptr, sizeof(tr));
				ptr += sizeof(tr);
				char mod;
				memcpy(&mod, ptr, sizeof(mod));
				ptr += sizeof(mod);
				char tx[128];
				memcpy(tx, ptr, sizeof(tx));
				ptr += sizeof(tx);
				char al[128];
				memcpy(al, ptr, sizeof(al));
				ptr += sizeof(al);
				std::string s(tx);
				std::string fname = s.substr(s.find_last_of("/\\")+1);
				char *tph = new char[1];
				strcpy(tph, "");
				if(!s.empty()){
					s = dpath;
					s+= fname;
					delete[] tph;
					tph = new char[s.size()+1];
					s.copy(tph, s.size());
					tph[s.size()] = 0;
				}
				s = std::string(al);
				char *aph = new char[1];
				strcpy(aph, "");
				if(!s.empty()){
					fname = s.substr(s.find_last_of("/\\")+1);
					s = dpath;
					s+= fname;
					delete[] aph;
					aph = new char[s.size()+1];
					s.copy(aph, s.size());
					aph[s.size()] = 0;
				}
				MS3DMaterial mt(name, amb, dif, spe, emi, sh, tr, mod, tph, aph);
				delete[] tph;
				delete[] aph;
				materials[i] = mt;
			}
			////////////////INFOS/////////////////////
			memcpy(&fps, ptr, sizeof(fps));
			ptr += sizeof(fps);
			ptr += sizeof(float); //currentTime not needed
			memcpy(&totalFrames, ptr, sizeof(totalFrames));
			ptr += sizeof(totalFrames);
			///////////////JOINTS/////////////////////////
			memcpy(&numJoints, ptr, sizeof(numJoints));
			ptr += sizeof(numJoints);
			initJoints(numJoints);
			for(int i=0; i<numJoints; i++){
				byte fl;
				memcpy(&fl, ptr, sizeof(fl));
				ptr += sizeof(fl);
				char nm[32];
				memcpy(nm, ptr, sizeof(nm));
				ptr += sizeof(nm);
				char pn[32];
				memcpy(pn, ptr, sizeof(pn));
				ptr += sizeof(pn);
				MS3DJoint* par = getJointParent(pn);
				float f[3];
				memcpy(f, ptr, sizeof(f));
				ptr += sizeof(f);
				Vector3f rot(f);
				memcpy(f, ptr, sizeof(f));
				ptr += sizeof(f);
				Vector3f pos(f);
				word rkf;
				memcpy(&rkf, ptr, sizeof(rkf));
				ptr += sizeof(rkf);
				MS3DKeyFrame rotkf[rkf];
				word tkf;
				memcpy(&tkf, ptr, sizeof(tkf));
				ptr += sizeof(tkf);
				MS3DKeyFrame trakf[tkf];
				for(int k=0; k<rkf; k++){
					float ti;
					memcpy(&ti, ptr, sizeof(ti));
					ptr += sizeof(ti);
					float f[3];
					memcpy(f, ptr, sizeof(f));
					ptr += sizeof(f);
					Vector3f v(f);
					MS3DKeyFrame kf(ti, v);
					rotkf[k] = kf;
				}
				for(int k=0; k<tkf; k++){
					float ti;
					memcpy(&ti, ptr, sizeof(ti));
					ptr += sizeof(ti);
					float f[3];
					memcpy(f, ptr, sizeof(f));
					ptr += sizeof(f);
					Vector3f v(f);
					MS3DKeyFrame kf(ti, v);
					trakf[k] = kf;
				}
				MS3DJoint jo(fl, nm, par, rot, pos, rkf, tkf, rotkf, trakf);
				joints[i] = jo;
			}

			delete[] buffer;
		}

	}; //gunit
}; //siege
