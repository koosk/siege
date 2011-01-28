#ifndef MS3D_STRUCT_H
#define MS3D_STRUCT_H

#include"utils.h"
#include"math/Vector3.h"
#include"math/Vector4.h"

namespace siege{
	namespace gunit{

		using namespace siege::math;

		const byte SELECTED = 1;
		const byte SELECTED2 = 2;
		const byte HIDDEN = 4;
		const byte DIRTY = 8;


///////////// MS3DVertex //////////////////////////////
///////////////////////////////////////////////////////

		class MS3DVertex{
			private:
				byte flags; //SELECTED | SELECTED2 | HIDDEN
				Vector3 vertex;
				char boneId;
				byte referenceCount;
			public:
				MS3DVertex();
				MS3DVertex(Vector3&);
				MS3DVertex(byte, Vector3&, char, byte);
				byte getFlags();
				Vector3 operator()();	//getVertex
				char getBoneId();
				byte getReferenceCount();
				bool hasBone();
				void setFlags(byte);
				void setVertex(Vector3&);
				void setBoneId(char);
				void setReferenceCount(byte);
		}; //MS3DVertex

///////////// MS3DTriangle /////////////////////////////
////////////////////////////////////////////////////////

		class MS3DTriangle{
			private:
				byte flags; // SELECTED | SELECTED2 | HIDDEN
				word vertexIndices[3];
				Vector3 vertexNormals[3];
				Vector3 s; // texture coordinate
				Vector3 t;	// texture coordinate
				byte smoothingGroup;
				byte groupIndex;
			public:
				MS3DTriangle();
				MS3DTriangle(word*, Vector3*);
				MS3DTriangle(byte, word*, Vector3*, Vector3&, Vector3&, byte, byte);
				byte getFlags();
				word getVertexIndex(byte);
				Vector3 getVertexNormal(byte);
				Vector3 getS();
				Vector3 getT();
				byte getSmoothingGroup();
				byte getGroupIndex();
				void setFlags(byte);
				void setVertexIndex(word, byte);
				void setVertexNormal(Vector3&, byte);
				void setS(Vector3&);
				void setT(Vector3&);
				void setSmoothingGroup(byte);
				void setGroupIndex(byte);
		}; //MS3DTriangle

///////////// MS3DGroup //////////////////////////////////
//////////////////////////////////////////////////////////

		class MS3DGroup{
			private:
				byte flags; // SELECTED | HIDDEN
				char name[32];
				word numTriangles;
				word* triangleIndices;
				char materialIndex; //-1 = no material
			public:
				MS3DGroup();
				MS3DGroup(MS3DGroup&);
				MS3DGroup(byte, char*, word, word*, char);
				~MS3DGroup();
				MS3DGroup& operator=(MS3DGroup&);
				byte getFlags();
				char* getName();
				word getNumberOfTriangles();
				word operator[](int); //getTriangleindex
				char getMaterialIndex();
				bool hasTriangles();
				bool hasMaterial();
				void setFlags(byte);
				void setName(char*);
				void setTriangles(word*, word);
				void setMaterialIndex(char);
		}; //MS3DGroup

///////////// MS3DMaterial /////////////////////////////////
////////////////////////////////////////////////////////////

		class MS3DMaterial{
			private:
				GLuint textureQuality; // GL_LINEAR || GL_NEAREST || GL_LINEAR_MIPMAP_NEAREST
				char name[32];
				Vector4 ambient;
				Vector4 diffuse;
				Vector4 specular;
				Vector4 emissive;
				float shininess; //0.0 - 128.0
				float transparency; //0.0 - 1.0
				char mode;
				char textureName[128];
				char alphamapName[128];
				GLuint texture;
				GLuint alphamap;
			public:
				MS3DMaterial();
				MS3DMaterial(char*, Vector4&, Vector4&, Vector4&, Vector4&, float, float, char ,char*, char*);
				char* getName();
				Vector4 getAmbient();
				Vector4 getDiffuse();
				Vector4 getSpecular();
				Vector4 getEmissive();
				float getShininess();
				float getTransparency();
				char getMode();
				char* getTexureName();
				char* getAlphamapName();
				GLuint getTexure();
				GLuint getAlphamap();
				GLuint getTextureQuality();
				bool hasTexture();
				bool hasAlphamap();
				void setName(char*);
				void setAmbient(Vector4&);
				void setDiffuse(Vector4&);
				void setSpecular(Vector4&);
				void setEmissive(Vector4&);
				void setShininess(float);
				void setTransparency(float);
				void setMode(char);
				void setTexture(char*);
				void setAlphamap(char*);
				void setTextureQuality(GLuint);
		}; //MS3DMaterial

///////////// MS3DKeyFrame ///////////////////////////////////
//////////////////////////////////////////////////////////////

		class MS3DKeyFrame{
			private:
				float time;
				Vector3 vector;
			public:
				MS3DKeyFrame();
				MS3DKeyFrame(float, Vector3&);
				MS3DKeyFrame(MS3DKeyFrame&);
				float getTime();
				Vector3 operator()(); //getVector
				void setTime(float);
				void setVector(Vector3&);
				Vector3 interpolate(MS3DKeyFrame&, float);
		}; //MS3DKeyFrame

///////////// MS3DJoint //////////////////////////////////////
//////////////////////////////////////////////////////////////

		class MS3DJoint{
			private:
				int index;
				byte flags; // SELECTED | DIRTY
				char name[32];
				MS3DJoint* parent; //char parentName[32]
				Vector3 rotation;
				Vector3 position;
				word numRotKeyFrames;
				word numTransKeyFrames;
				MS3DKeyFrame* rotKeyFrames;
				MS3DKeyFrame* transKeyFrames;
			public:
				MS3DJoint();
				MS3DJoint(MS3DJoint&);
				MS3DJoint(word, byte, char*, MS3DJoint*, Vector3&, Vector3&, word, word, MS3DKeyFrame*, MS3DKeyFrame*);
				~MS3DJoint();
				MS3DJoint& operator=(MS3DJoint&);
				byte getFlags();
				char* getName();
				int getIndex();
				MS3DJoint* getParent();
				Vector3 getRotationVector();
				Vector3 getPositionVector();
				word getNumberOfRotationKeyFrames();
				word getNumberOfTranslationKeyFrames();
				MS3DKeyFrame* getRotationKeyFrames();
				MS3DKeyFrame* getTranslationKeyFrames();
				MS3DKeyFrame getRotationKeyFrame(word);
				MS3DKeyFrame getTranslationKeyFrame(word);
				bool hasRotationKeyFrames();
				bool hasTranslationKeyFrames();
				bool hasParent();
				void setIndex(word);
				void setFlags(byte);
				void setName(char*);
				void setParent(MS3DJoint*);
				void setRotationVector(Vector3&);
				void setPositionVector(Vector3&);
				void setRotationKeyFrames(MS3DKeyFrame*, word);
				void setTranslationKeyFrames(MS3DKeyFrame*, word);
		}; //MS3dJoint

	}; //gunit
}; //siege

#endif //MS3D_STRUCT_H


// Mesh Transformation:
// 
// 0. Build the transformation matrices from the rotation and position
// 1. Multiply the vertices by the inverse of local reference matrix (lmatrix0)
// 2. then translate the result by (lmatrix0 * keyFramesTrans)
// 3. then multiply the result by (lmatrix0 * keyFramesRot)
//
// For normals skip step 2.
