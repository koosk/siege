#include"gunit/MS3DStruct.h"
#include"BadIndexException.h"
#include"gunit/MS3DException.h"
#include<string.h>

namespace siege{
	namespace gunit{

		//////////////////////// MS3DVertex /////////////////////
		////////////////////////////////////////////////////////

		MS3DVertex::MS3DVertex(){
			flags = 0;
			vertex = Vector3f();
			boneId = -1;
			referenceCount = 0;
		}

		MS3DVertex::MS3DVertex(Vector3f& v){	
			flags = 0;
			vertex = v;
			boneId = -1;
			referenceCount = 0;
		}

		MS3DVertex::MS3DVertex(byte fl, Vector3f& v, char bid, byte refc){
			flags = fl;
			vertex = v;
			boneId = bid;
			referenceCount = refc;
		}

		byte MS3DVertex::getFlags(){
			return flags;
		}

		Vector3f MS3DVertex::operator()(){
			return vertex;
		}

		char MS3DVertex::getBoneId(){
			return boneId;
		}

		byte MS3DVertex::getReferenceCount(){
			return referenceCount;
		}

		bool MS3DVertex::hasBone(){
			return boneId > -1;
		}

		void MS3DVertex::setFlags(byte f){
			flags = f;		
		}

		void MS3DVertex::setVertex(Vector3f& v){
			vertex = v;	
		}

		void MS3DVertex::setBoneId(char id){
			boneId = id;	
		}

		void MS3DVertex::setReferenceCount(byte n){
			referenceCount = n;	
		}
		
		////////////// MS3DTriangle ///////////////////////////////////
		///////////////////////////////////////////////////////////////

		MS3DTriangle::MS3DTriangle(){
			flags = 0;	
			smoothingGroup = 0;
			groupIndex = 0;
		}

		MS3DTriangle::MS3DTriangle(word* ind, Vector3f* v){
			flags = 0;	
			smoothingGroup = 0;
			groupIndex = 0;
			for(int i=0; i<3; i++){
				setVertexIndex(ind[i], i);
				setVertexNormal(v[i], i);
			}
		}

		MS3DTriangle::MS3DTriangle(byte fl, word* ind, Vector3f* v, Vector3f& s, Vector3f& t, byte sg, byte g){
			flags = fl;
			for(int i=0; i<3; i++){
				setVertexIndex(ind[i], i);
				setVertexNormal(v[i], i);
			}
			this->s = s;
			this->t = t;
			setSmoothingGroup(sg);
			groupIndex = g;
		}

		byte MS3DTriangle::getFlags(){
			return flags;
		}

		word MS3DTriangle::getVertexIndex(byte i){
			if(i<0 || i>2)
				throw siege::BadIndexException("Bad vertex index at MS3DTriangle!");
			return vertexIndices[i];
		}

		Vector3f MS3DTriangle::getVertexNormal(byte i){
			if(i<0 || i>2)
				throw siege::BadIndexException("Bad vertex normal index at MS3DTriangle!");
			return vertexNormals[i];
		}

		Vector3f MS3DTriangle::getS(){
			return s;
		}

		Vector3f MS3DTriangle::getT(){
			return t;
		}

		byte MS3DTriangle::getSmoothingGroup(){
			return smoothingGroup;
		}

		byte MS3DTriangle::getGroupIndex(){
			return groupIndex;
		}

		void MS3DTriangle::setFlags(byte f){
			flags = f;
		}

		void MS3DTriangle::setVertexIndex(word a, byte i){
			if(i<0 || i>2)
				throw siege::BadIndexException("Bad vertex index at MS3DTriangle");
			vertexIndices[i] = a;
		}

		void MS3DTriangle::setVertexNormal(Vector3f& v, byte i){
			if(i<0 || i>2)
				throw siege::BadIndexException("Bad vertex normal index at MS3DTriangle!");
			vertexNormals[i] = v;
		}

		void MS3DTriangle::setS(Vector3f& v){
			s = v;
		}

		void MS3DTriangle::setT(Vector3f& v){
			t = v;
		}

		void MS3DTriangle::setSmoothingGroup(byte i){
			if(i<1 || i>32)
				throw siege::BadIndexException("Wrong smoothing group at MS3DTrinagle!");
			smoothingGroup = i;
		}

		void MS3DTriangle::setGroupIndex(byte i){
			groupIndex = i;
		}

//////////////////// MS3DGroup //////////////////////////////////////
/////////////////////////////////////////////////////////////////////

		MS3DGroup::MS3DGroup(){
			flags = 0;
			strcpy(name, "Unnamed");
			numTriangles = 0;
			triangleIndices = NULL;
			materialIndex = -1;
		}

		MS3DGroup::MS3DGroup(MS3DGroup& g){
			flags = g.flags;
			strcpy(name, g.name);
			triangleIndices = NULL;
			setTriangles(g.triangleIndices, g.numTriangles);
			materialIndex = g.materialIndex;
		}

		MS3DGroup::MS3DGroup(byte fl, char* nm, word ct, word* ind, char mi){
			flags = fl;
			strcpy(name, nm);
			triangleIndices = NULL;
			setTriangles(ind, ct);
			materialIndex = mi;
		}

		MS3DGroup::~MS3DGroup(){
			if(triangleIndices != NULL) 
				delete[] triangleIndices;
		}

		MS3DGroup& MS3DGroup::operator=(MS3DGroup& g){
			flags = g.flags;
			strcpy(name, g.name);
			triangleIndices = NULL;
			setTriangles(g.triangleIndices, g.numTriangles);
			materialIndex = g.materialIndex;
			return *this;
		}

		byte MS3DGroup::getFlags(){
			return flags;
		}

		char* MS3DGroup::getName(){
			return name;
		}

		word MS3DGroup::getNumberOfTriangles(){
			return numTriangles;
		}

		word MS3DGroup::operator[](int i){
			if(i<0 || i>=numTriangles)
				throw BadIndexException("Bad triangle index at MS3DGroup!");
			return triangleIndices[i];
		}

		char MS3DGroup::getMaterialIndex(){
			return materialIndex;
		}

		bool MS3DGroup::hasTriangles(){
			return numTriangles > 0;
		}

		bool MS3DGroup::hasMaterial(){
			return materialIndex > -1;
		}

		void MS3DGroup::setFlags(byte f){
			flags = f;
		}

		void MS3DGroup::setName(char* nm){
			strcpy(name, nm);
		}

		void MS3DGroup::setTriangles(word* ind, word ct){
			if(triangleIndices != NULL){
				delete[] triangleIndices;
				triangleIndices = NULL;
			}
			if(ind == NULL || ct == 0){
				triangleIndices = NULL;
				numTriangles = 0;
				return;
			}
			numTriangles = ct;
			triangleIndices = new word[numTriangles];
			for(int i=0; i<ct; i++)
				triangleIndices[i] = ind[i];
			//memcpy(triangleIndices, ind, ct);
		}

		void MS3DGroup::setMaterialIndex(char i){
			materialIndex = i;
		}

///////////////////////// MS3DMaterial ////////////////////////////
///////////////////////////////////////////////////////////////////
		MS3DMaterial::MS3DMaterial(){
			textureQuality = GL_LINEAR_MIPMAP_NEAREST; 
			strcpy(name, "Unnamed");
			shininess = 0;
			transparency = 1;
			mode = 0;
		}

		MS3DMaterial::MS3DMaterial(char* nm, Vector4f& am, Vector4f& dif, Vector4f& em, Vector4f& spe, float shi, float tra, char md, char* text, char* alpha){
			textureQuality = GL_LINEAR_MIPMAP_NEAREST; 
			strcpy(name, nm);
			ambient = am;
			diffuse = dif;
			emissive = em;
			specular = spe;
			shininess = shi;
			transparency = tra;
			mode = md;
			setTexture(text);
			setAlphamap(alpha);
		}

		char* MS3DMaterial::getName(){
			return name;
		}

		Vector4f MS3DMaterial::getAmbient(){
			return ambient;
		}

		Vector4f MS3DMaterial::getDiffuse(){
			return diffuse;
		}

		Vector4f MS3DMaterial::getEmissive(){
			return emissive;
		}

		Vector4f MS3DMaterial::getSpecular(){
			return specular;
		}

		float MS3DMaterial::getShininess(){
			return shininess;
		}

		float MS3DMaterial::getTransparency(){
			return transparency;
		}

		char MS3DMaterial::getMode(){
			return mode;
		}

		char* MS3DMaterial::getTexureName(){
			return textureName;
		}

		char* MS3DMaterial::getAlphamapName(){
			return alphamapName;
		}

		GLuint MS3DMaterial::getTexure(){
			return texture;
		}

		GLuint MS3DMaterial::getAlphamap(){
			return alphamap;
		}

		GLuint MS3DMaterial::getTextureQuality(){
			return textureQuality;
		}

		bool MS3DMaterial::hasTexture(){
			return texture != 0;
		}

		bool MS3DMaterial::hasAlphamap(){
			return alphamap != 0;
		}

		void MS3DMaterial::setName(char* nm){
			strcpy(name, nm);
		}

		void MS3DMaterial::setAmbient(Vector4f& v){
			ambient = v;
		}

		void MS3DMaterial::setDiffuse(Vector4f& v){
			diffuse = v;
		}

		void MS3DMaterial::setEmissive(Vector4f& v){
			emissive = v;
		}

		void MS3DMaterial::setSpecular(Vector4f& v){
			specular = v;
		}

		void MS3DMaterial::setShininess(float shi){
			shininess = shi;
		}

		void MS3DMaterial::setTransparency(float tra){
			transparency = tra;
		}

		void MS3DMaterial::setMode(char m){
			mode = m;
		}

		void MS3DMaterial::setTexture(char* t){
			if(t == NULL || strcmp(t, "") == 0){
				texture = 0;
				strcpy(textureName, "");
				return;
			}
			try{
				texture = loadImage(t, textureQuality);
				strcpy(textureName, t);
			}catch(std::exception &e){
				texture = 0;
				strcpy(textureName, "");
				std::cout << e.what() << std::endl;
			}
		}

		void MS3DMaterial::setAlphamap(char* a){
			if(a == NULL || strcmp(a, "") == 0){
				alphamap = 0;
				strcpy(alphamapName, "");
				return;
			}
			try{
				alphamap = loadImage(a, textureQuality);
				strcpy(alphamapName, a);
			}catch(std::exception &e){
				alphamap = 0;
				strcpy(alphamapName, "");
				std::cout << e.what() << std::endl;
			}
		}

		void MS3DMaterial::setTextureQuality(GLuint q){
			textureQuality = q;
			setTexture(textureName);
			setAlphamap(alphamapName);
		}

///////////////////// MS3DKeyFrame //////////////////////////////////
/////////////////////////////////////////////////////////////////////

		MS3DKeyFrame::MS3DKeyFrame():time(0.0){}

		MS3DKeyFrame::MS3DKeyFrame(float t, Vector3f& v){
			time = t;
			vector = v;
		}

		MS3DKeyFrame::MS3DKeyFrame(MS3DKeyFrame& kf){
			time = kf.time;
			vector = kf.vector;
		}

		float MS3DKeyFrame::getTime(){
			return time;
		}

		Vector3f MS3DKeyFrame::operator()(){
			return vector;
		}

		void MS3DKeyFrame::setTime(float t){
			time = t;
		}

		void MS3DKeyFrame::setVector(Vector3f& v){
			vector = v;
		}

		Vector3f& MS3DKeyFrame::interpolate(MS3DKeyFrame& kf, float t){
			if(time > kf.time)
				throw MS3DException("The given keyframe's time must be bigger!");
			if(t < time || t > kf.time)
				throw MS3DException("The given time is not in the appropriet time interval!");
			if(time == kf.time)
				return vector;
			float td = kf.time - time;
			float intpol = (t - time) / td;
			float x = vector[0] + (kf.vector[0] - vector[0]) * intpol;
			float y = vector[1] + (kf.vector[1] - vector[1]) * intpol;
			float z = vector[2] + (kf.vector[2] - vector[2]) * intpol;
			Vector3f v(x, y, z);
			return v;
		}

/////////////////////// MS3DJoint ///////////////////////////////////
/////////////////////////////////////////////////////////////////////

		MS3DJoint::MS3DJoint(){
			index = -1;
			flags = 0;
			strcpy(name, "Unnamed");
			parent = NULL;
			numRotKeyFrames = 0;
			rotKeyFrames = NULL;
			numTransKeyFrames = 0;
			transKeyFrames = NULL;
		}
	
		MS3DJoint::MS3DJoint(MS3DJoint& j){
			index = j.index;
			flags = j.flags;
			strcpy(name, j.name);
			parent = j.parent;
			rotation = j.rotation;
			position = j.position;
			rotKeyFrames = NULL;
			setRotationKeyFrames(j.rotKeyFrames, j.numRotKeyFrames);
			transKeyFrames = NULL;
			setTranslationKeyFrames(j.transKeyFrames, j.numTransKeyFrames);
		}

		MS3DJoint::MS3DJoint(word i, byte f, char* nm, MS3DJoint* pa, Vector3f& r, Vector3f& p, word nr, word nt, MS3DKeyFrame* rot, MS3DKeyFrame* trans){
			index = i;
			flags = f;
			strcpy(name, nm);
			parent = pa;
			rotation = r;
			position = p;
			rotKeyFrames = NULL;
			setRotationKeyFrames(rot, nr);
			transKeyFrames = NULL;
			setTranslationKeyFrames(trans, nt);
		}

		MS3DJoint::~MS3DJoint(){
			if(rotKeyFrames != NULL)
				delete[] rotKeyFrames;
			if(transKeyFrames != NULL)
				delete[] transKeyFrames;
		}

		MS3DJoint& MS3DJoint::operator=(MS3DJoint& j){
			index = j.index;
			flags = j.flags;
			strcpy(name, j.name);
			parent = j.parent;
			rotation = j.rotation;
			position = j.position;
			rotKeyFrames = NULL;
			setRotationKeyFrames(j.rotKeyFrames, j.numRotKeyFrames);
			transKeyFrames = NULL;
			setTranslationKeyFrames(j.transKeyFrames, j.numTransKeyFrames);
			return *this;
		}

		byte MS3DJoint::getFlags(){
			return flags;
		}

		char* MS3DJoint::getName(){
			return name;
		}

		int MS3DJoint::getIndex(){
			return index;
		}

		MS3DJoint* MS3DJoint::getParent(){
			return parent;
		}

		Vector3f MS3DJoint::getRotationVector(){
			return rotation;
		}

		Vector3f MS3DJoint::getPositionVector(){
			return position;
		}

		word MS3DJoint::getNumberOfRotationKeyFrames(){
			return numRotKeyFrames;
		}

		word MS3DJoint::getNumberOfTranslationKeyFrames(){
			return numTransKeyFrames;
		}
		
		MS3DKeyFrame* MS3DJoint::getRotationKeyFrames(){
			return rotKeyFrames;
		}
		
		MS3DKeyFrame* MS3DJoint::getTranslationKeyFrames(){
			return transKeyFrames;
		}

		MS3DKeyFrame MS3DJoint::getRotationKeyFrame(word i){
			if(i<0 || i>=numRotKeyFrames)
				throw siege::BadIndexException("Bad rotation key frame index at MS3DJoint!");
			return rotKeyFrames[i];
		}
		
		MS3DKeyFrame MS3DJoint::getTranslationKeyFrame(word i){
			if(i<0 || i>=numTransKeyFrames)
				throw siege::BadIndexException("Bad translation key frame index at MS3DJoint!");
			return transKeyFrames[i];
		}

		bool MS3DJoint::hasRotationKeyFrames(){
			return rotKeyFrames > 0;
		}

		bool MS3DJoint::hasTranslationKeyFrames(){
			return transKeyFrames > 0;
		}

		bool MS3DJoint::hasParent(){
			return parent != NULL;
		}

		void MS3DJoint::setIndex(word i){
			index = i;
		}

		void MS3DJoint::setFlags(byte f){
			flags = f;
		}

		void MS3DJoint::setName(char* nm){
			strcpy(name, nm);
		}

		void MS3DJoint::setParent(MS3DJoint* p){
			parent = p;
		}

		void MS3DJoint::setRotationVector(Vector3f& v){
			rotation = v;
		}

		void MS3DJoint::setPositionVector(Vector3f& v){
			position = v;
		}

		void MS3DJoint::setRotationKeyFrames(MS3DKeyFrame* f, word num){
			if(rotKeyFrames != NULL)
				delete[] rotKeyFrames;
			if(f == NULL){
				rotKeyFrames = NULL;
				numRotKeyFrames = 0;
				return;
			}
			numRotKeyFrames = num;
			rotKeyFrames = new MS3DKeyFrame[num];
			for(int i=0; i<num; i++)
				rotKeyFrames[i] = f[i];
		}

		void MS3DJoint::setTranslationKeyFrames(MS3DKeyFrame* f, word num){
			if(transKeyFrames != NULL)
				delete[] transKeyFrames;
			if(f == NULL){
				transKeyFrames = NULL;
				numTransKeyFrames = 0;
				return;
			}
			numTransKeyFrames = num;
			transKeyFrames = new MS3DKeyFrame[num];
			for(int i=0; i<num; i++)
				transKeyFrames[i] = f[i];
		}

	}; //gunit
}; //siege

