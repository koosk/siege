/*
Versions:
	Quake1, Hexen2												29
	Half-Life, Opposing Force, Counter-Strike, Blue-Shift		30
	Quake2, Heretic2											38
	Quake3		(IMPLEMENTED)									46
	RTCW														47
*/

#ifndef BSP_MAP_H
#define BSP_MAP_H

#include"gunit/BSPStruct.h"
#include"math/Vector4.h"
#include"gunit/Model.h"
#include"scene/Camera.h"
#include<vector>
#include<GL/gl.h>

namespace siege{
	namespace gunit{

		class BSPMap{
			private:
				char* path;
				GLuint texQuality;
				unsigned int numVertices;
				unsigned int numLightmaps;
				unsigned int numPlanes;
				unsigned int numTextures;
				unsigned int numBrushsides;
				unsigned int numBrushes;
				unsigned int numEffects;
				unsigned int numFaces;
				unsigned int numClusters;
				unsigned int numLeaves;
				unsigned int numNodes;
				BSPVertex* vertices;
				BSPLightmap* lightmaps;
				BSPPlane* planes;
				BSPTexture* textures;
				BSPBrushSide* brushsides;
				BSPBrush* brushes;
				BSPEffect* effects;
				BSPFace** faces;
				int* meshverts;
				int* leaffaces;
				int* leafbrushes;
				BSPVisdata* clusters;
				BSPLeaf* leaves;
				BSPNode* nodes;
				std::vector<math::Vector4> spawnPoints;
			protected:
				virtual void init();
				void initVertices(int);
				void initLightmaps(int);
				void initPlanes(int);
				void initTextures(int);
				void initBrushsides(int);
				void initBrushes(int);
				void initEffects(int);
				void initFaces(int);
				void initClusters(int);
				void initLeaves(int);
				void initNodes(int);
				void read(std::ifstream&, byte, BSPDir*, void (BSPMap::*f)(char*, unsigned int));
				void loadEntities(char*, unsigned int);
				void loadVertices(char*, unsigned int);
				void loadLighmaps(char*, unsigned int);
				void loadPlanes(char*, unsigned int);
				void loadTextures(char*, unsigned int);
				void loadBrushsides(char*, unsigned int);
				void loadBrushes(char*, unsigned int);
				void loadEffects(char*, unsigned int);
				void loadFaces(char*, unsigned int);
				void loadMeshverts(char*, unsigned int);
				void loadLeafFaces(char*, unsigned int);
				void loadLeafBrushes(char*, unsigned int);
				void loadClusters(char*, unsigned int);
				void loadLeaves(char*, unsigned int);
				void loadNodes(char*, unsigned int);
			public:
				static const GLuint DEFAULT_TEXTURE_QUALITY = GL_LINEAR_MIPMAP_NEAREST;
				BSPMap();
				BSPMap(char const*);
				BSPMap(const BSPMap&);
				~BSPMap();
				BSPMap& operator=(const BSPMap&);
				void load();
				void load(char const*);
				void setPath(char const*);
				void draw() const;
				void draw(math::Vector3) const;
				void setTextureQuality(GLuint);
				void spawn(math::Vector3&, int = -1) const;
				void spawn(Model*, int = -1) const;
				void spawn(scene::Camera&, int = -1) const;
				unsigned int getNumSpawnPoints() const;
		}; //BSPMap

	}; //gunit
}; //gunit

#endif //BSP_MAP_H
