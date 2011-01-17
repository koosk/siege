#include"gunit/MS3DData.h"
#include"BadIndexException.h"
#include"gunit/MS3DException.h"
#include<string.h>

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
			memcpy(vertices, md.vertices, numVertices);
			memcpy(triangles, md.triangles, numTriangles);
			memcpy(groups, md.groups, numGroups);
			memcpy(materials, md.materials, numMaterials);
			for(int i=0; i<numJoints; i++){
				joints[i] = md.joints[i];
				joints[i].setParent(getJointParent(md.joints[i]));
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
				throw BadIndexException();
			return &vertices[i];
		}

		MS3DTriangle* MS3DData::getTriangle(word i){
			if(i<0 || i>=numTriangles)
				throw BadIndexException();
			return &triangles[i];
		}

		MS3DGroup* MS3DData::getGroup(word i){
			if(i<0 || i>=numGroups)
				throw BadIndexException();
			return &groups[i];
		}

		MS3DMaterial* MS3DData::getMaterial(word i){
			if(i<0 || i>=numMaterials)
				throw BadIndexException();
			return &materials[i];
		}

		MS3DJoint* MS3DData::getJoint(word i){
			if(i<0 || i>=numJoints)
				throw BadIndexException();
			return &joints[i];
		}

		float MS3DData::getFPS(){
			return fps;
		}

		int MS3DData::getTotalFrames(){
			return totalFrames;
		}

		std::ifstream& operator>>(std::ifstream& in, MS3DData& md){
			//TODO ellenorizni hogy a stream binaris e
			//if((in.flags() & std::ios::binary) != std::ios::binary)
			//	throw MS3DException("The given stream is not binary!");

			in.seekg(0, std::ios::end);
			long size = in.tellg();
			in.seekg(0, std::ios::beg);

			char* buffer = new char[size];
			in.read(buffer, size);
			char* ptr = buffer;

			/////////////HEADER/////////////////////////
			char mid[10];
			memcpy(mid, ptr, sizeof(mid));
			ptr += sizeof(mid);
			if(strncmp(mid, "MS3D000000", 10) != 0)
				throw MS3DException("Not a valid Milkshape model data!");
			memcpy(&md.version, ptr, sizeof(md.version));
			ptr += sizeof(md.version);
			if(md.version < 3 || md.version > 4){
				throw MS3DException("Unhandled version!");
			}
			
			////////////VERTICES//////////////////////
			memcpy(&md.numVertices, ptr, sizeof(md.numVertices));
			ptr += sizeof(md.numVertices);
			md.initVertices(md.numVertices);
			for(int i=0; i<md.numVertices; i++){
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
				md.vertices[i] = MS3DVertex(btmp, v, ctmp, refc);
			}
			//////////////TRIANGLES////////////////////
			memcpy(&md.numTriangles, ptr, sizeof(md.numTriangles));
			ptr += sizeof(md.numTriangles);
			md.initTriangles(md.numTriangles);
			for(int i=0; i<md.numTriangles; i++){
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
				f[0] = 1.0 - f[0];
				f[1] = 1.0 - f[1];
				f[2] = 1.0 - f[2];
				Vector3f t(f);
				byte sg;
				memcpy(&sg, ptr, sizeof(sg));
				ptr += sizeof(sg);
				byte gr;
				memcpy(&gr, ptr, sizeof(gr));
				ptr += sizeof(gr);
				MS3DTriangle tri(flag, vi, vec, s, t, sg, gr);
				md.triangles[i] = tri;
			}
			///////////////////GROUPS/////////////////
			memcpy(&md.numGroups, ptr, sizeof(md.numGroups));
			ptr += sizeof(md.numGroups);
			md.initGroups(md.numGroups);
			for(int i=0; i<md.numGroups; i++){
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
				md.groups[i] =  MS3DGroup(flag, name, nt, ti ,mi);
			}
			///////////////////////MATERIAL////////////
			memcpy(&md.numMaterials, ptr, sizeof(md.numMaterials));
			ptr += sizeof(md.numMaterials);
			md.initMaterials(md.numMaterials);
			for(int i=0; i<md.numMaterials; i++){
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
				MS3DMaterial mt(name, amb, dif, spe, emi, sh, tr, mod, tx, al);
				md.materials[i] = mt;
			}
			////////////////INFOS/////////////////////
			memcpy(&md.fps, ptr, sizeof(md.fps));
			ptr += sizeof(md.fps);
			ptr += sizeof(float); //currentTime not needed
			memcpy(&md.totalFrames, ptr, sizeof(md.totalFrames));
			ptr += sizeof(md.totalFrames);
			///////////////JOINTS/////////////////////////
			memcpy(&md.numJoints, ptr, sizeof(md.numJoints));
			ptr += sizeof(md.numJoints);
			md.initJoints(md.numJoints);
			for(int i=0; i<md.numJoints; i++){
				byte fl;
				memcpy(&fl, ptr, sizeof(fl));
				ptr += sizeof(fl);
				char nm[32];
				memcpy(nm, ptr, sizeof(nm));
				ptr += sizeof(nm);
				char pn[32];
				memcpy(pn, ptr, sizeof(pn));
				ptr += sizeof(pn);
				MS3DJoint* par = md.getJointParent(pn);
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
				md.joints[i] = jo;
			}

			delete[] buffer;
			return in;
		}

	}; //gunit
}; //siege
