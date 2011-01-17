#ifndef MS3D_DATA_H
#define MS3D_DATA_H

#include"MS3DStruct.h"
#include<fstream>

namespace siege{
	namespace gunit{

		class MS3DData{
			private:
				int version;
				word numVertices;
				word numTriangles;
				word numGroups;
				word numMaterials;
				word numJoints;
				MS3DVertex* vertices;
				MS3DTriangle* triangles;
				MS3DGroup* groups;
				MS3DMaterial* materials;
				MS3DJoint* joints;
				float fps;
				int totalFrames;
			protected:
				void init(word, word, word, word, word);
				void initVertices(word);
				void initTriangles(word);
				void initGroups(word);
				void initMaterials(word);
				void initJoints(word);
				inline void free();
				void setVersion(int);
				void setVertex(MS3DVertex&, word);
				void setTriangle(MS3DTriangle&, word);
				void setGroup(MS3DGroup&, word);
				void setMaterial(MS3DMaterial&, word);
				void setJoint(MS3DJoint&, word);
				void setFPS(float);
				void setTotalFrames(int);
				MS3DJoint* getJointParent(MS3DJoint&);
				MS3DJoint* getJointParent(char*);
			public:
				MS3DData();
				MS3DData(MS3DData&);
				~MS3DData();
				int getVersion();
				word getNumberOfVertices();
				word getNumberOfTriangles();
				word getNumberOfGroups();
				word getNumberOfMaterials();
				word getNumberOfJoints();
				MS3DVertex* getVertex(word);
				MS3DTriangle* getTriangle(word);
				MS3DGroup* getGroup(word);
				MS3DMaterial* getMaterial(word);
				MS3DJoint* getJoint(word);
				float getFPS();
				int getTotalFrames();
				friend  std::ifstream& operator>>(std::ifstream&, MS3DData&);
		}; //MS3DData

	}; //gunit
}; //siege

#endif //MS3D_DATA_H
