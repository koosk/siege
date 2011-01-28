// QUAKE3 BSP strucure

#ifndef BSP_STRUCT_H
#define  BSP_STRUCT_H

#include<vector>
#include<GL/gl.h>
#include"math/Vector3.h"
#include"utils.h"

namespace siege{
	namespace gunit{

		using namespace siege::math;

//mehsvert, leafbrush, leafface are not needed to be make as class

///////////// BSPVertex /////////////////////////////////////
/////////////////////////////////////////////////////////////
		class BSPVertex{
			private:
				Vector3 position;
				float texcoord[2][2]; //0=surface, 1=lightmap
				Vector3 normal;
				byte color[4];
			public:
				BSPVertex();
				BSPVertex(const Vector3, float const*, float const*, const Vector3, byte const*);
				void setPosition(const Vector3);
				void setSurfaceTextureCoordinate(float const*);
				void setLightmapTextureCoordinate(float const*);
				void setNormal(const Vector3);
				void setColor(byte const*);
				Vector3 getPosition() const;
				float const* getSurfaceTextureCoordinate() const;
				float const* getLightmapTextureCoordinate() const;
				Vector3 getNormal() const;
				byte const* getColor() const;
		}; //BSPVertex

///////////// BSPLightmap ///////////////////////////////////////
/////////////////////////////////////////////////////////////////
		class BSPLightmap{
			private:
				byte value[128][128][3];
			public:
				BSPLightmap();
				BSPLightmap(byte** const*);
				void setValue(byte** const*);
				//TODO
				//byte** const* getValue();
		}; //BSPLightmap

///////////// BSPPlane /////////////////////////////////////////
////////////////////////////////////////////////////////////////
		class BSPPlane{
			private:
				Vector3 normal;
				float distance;
			public:
				BSPPlane();
				BSPPlane(const Vector3, const float);
				void setNormal(const Vector3);
				void setDistance(const float);
				Vector3 getNormal() const;
				float getDistance() const;
		}; //BSPPlane

///////////// BSPTexture ///////////////////////////////////////
////////////////////////////////////////////////////////////////
		class BSPTexture{
			private:
				char path[64];
				int flags;
				int contents;
				GLuint texture;
				GLuint texquality;
				void loadTexture();
			public:
				BSPTexture();
				BSPTexture(char const*, const int, const int);
				void setPath(char const*);
				void setFlags(const int);
				void setContents(const int);
				void setTextureQuality(GLuint);
				char const* getPath() const;
				int getFlags() const;
				int getContents() const;
				GLuint getTexture() const;
		}; //BSPTexture

///////////// BSPBrushSide /////////////////////////////////////
////////////////////////////////////////////////////////////////
		class BSPBrushSide{
			private:
				BSPPlane* plane;
				BSPTexture* texture;
			public:
				BSPBrushSide();
				BSPBrushSide(BSPPlane*, BSPTexture*);
				void setPlane(BSPPlane*);
				void setTexture(BSPTexture*);
				BSPPlane* getPlane() const;
				BSPTexture* getTexture() const;
		}; //BSPBrushSide

///////////// BSPBrush ////////////////////////////////////////
///////////////////////////////////////////////////////////////
		class BSPBrush{
			private:
				int numbs;
				BSPBrushSide** brusSides;
				BSPTexture* texture;
			public:
				BSPBrush();
				BSPBrush(BSPBrushSide**, int, BSPTexture*);
				BSPBrush(const BSPBrush&);
				~BSPBrush();
				BSPBrush& operator=(const BSPBrush&);
				void setBrushSides(BSPBrushSide**, int);
				void setTexture(BSPTexture*);
				int getNumberOfBrushSides() const;
				BSPBrushSide* getBrushSide(int) const;
				BSPTexture* getTexture() const;
		}; //BSPBrush

///////////// BSPEffect /////////////////////////////////////////
/////////////////////////////////////////////////////////////////
		class BSPEffect{
			private:
				char name[64];
				BSPBrush* brush;
				//int unknown 	Always 5, except in q3dm8, which has one effect with -1
			private:
				BSPEffect();
				BSPEffect(char const*, BSPBrush*);
				void setName(char const*);
				void setBrush(BSPBrush*);
				char const* getName() const;
				BSPBrush* getBrush() const;
		}; //BSPEffect

///////////// BSPFace //////////////////////////////////////////
////////////////////////////////////////////////////////////////
		class BSPFace{
			protected:
				BSPTexture* texture;
				BSPEffect* effect;
				int numVertices;
				BSPVertex** vertices;
				int firstMeshvert;
				int numMeshVertices;
				BSPLightmap* lightmap;
				int lightmapStart[2];
				int lightmapSize[2];
				Vector3 Normal;
			public:
				BSPFace();
				BSPFace(BSPTexture const*, BSPEffect const*, BSPVertex* const*, int, int, int, BSPLightmap const*, int const*, int const*, Vector3);
				BSPFace(const BSPFace&);
				~BSPFace();
				BSPFace& operator=(const BSPFace&);
				void setTexture(BSPTexture const*);
				void setEffect(BSPEffect const*);
				void setVertices(BSPVertex* const*, int);
				void setMeshes(int, int);
				void setLighMap(BSPLightmap const*, int const*, int const*);
				void setNormal(const Vector3);
				//BSPTexture* getTexture() const;
				BSPEffect getEffect() const;
				/*int getNumberOfVertices() const;
				BSPVertex const* getVertex(int) const;
				hasonloan a meshekre sem valoszinu h fog kelleni*/
				//BSPLightmap* getLightmap() const;
				virtual void draw() const = 0;
		}; //BSPFace

		class BSPPolygon : public BSPFace{
			private:
				Vector3 lightmapOrigin;
				Vector3 lightmapS;
				Vector3 lightmapT;
			public:
				BSPPolygon(BSPTexture const*, BSPEffect const*, BSPVertex* const*, int, int, int, BSPLightmap const*, 
							int const*, int const*, Vector3, Vector3, Vector3, Vector3);
				BSPPolygon(const BSPPolygon&);
				BSPPolygon& operator=(const BSPPolygon&);
				void setLightmapOrigin(Vector3);
				void setLightmapS(Vector3);
				void setLightmapT(Vector3);
				Vector3 getLightmapS() const;
				Vector3 getLightmapT() const;
				Vector3 getLightmapOrigin() const;
		}; //BSPPolygon

		class BSPPatch : public BSPFace{
			private:
				int dimension[2];
			public:
				BSPPatch(BSPTexture const*, BSPEffect const*, BSPVertex* const*, int, int, int, BSPLightmap const*, int const*, int const*, Vector3, int const*);
				BSPPatch(const BSPPatch&);
				BSPPatch& operator=(const BSPPatch&);
				void setDimension(int const*);
				int const* getDimension() const;
				void draw() const;
		}; //BSPPatch

		class BSPMesh : public BSPFace{
			public:
				BSPMesh(BSPTexture const*, BSPEffect const*, BSPVertex* const*, int, int, int, BSPLightmap const*, int const*, int const*, Vector3);
				BSPMesh(const BSPMesh&);
				BSPMesh& operator=(const BSPMesh&);
				void draw() const;
		}; //BSPMesh

		class BSPBillboard : public BSPFace{
			public:
				BSPBillboard(BSPTexture const*, BSPEffect const*, BSPVertex* const*, int, int, int, BSPLightmap const*, int const*, int const*, Vector3);
				BSPBillboard(const BSPBillboard&);
				BSPBillboard& operator=(const BSPBillboard&);
				void draw() const;
		}; //BSPBillboard

///////////// BSPVisdata ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		class BSPLeaf;

		class BSPVisdata{
			private:
				int numVisdata;
				BSPVisdata** visdata;
				std::vector<BSPLeaf*> leaves;
			public:
				BSPVisdata();
				BSPVisdata(int);
				BSPVisdata(BSPVisdata* const*, int);
				BSPVisdata(const BSPVisdata&);
				~BSPVisdata();
				BSPVisdata& operator=(const BSPVisdata&);
				void resetVisData(int);
				void addVisdata(BSPVisdata const*);
				void setNumberofVisdata(BSPVisdata* const*, int);
				void addLeaf(BSPLeaf const*);
				int getNumberOfVisdata() const;
				BSPVisdata* getVisData(int) const;
				int getNumberOfLeaves() const;
				BSPLeaf* getLeaf(int) const;
		}; //BSPVisdata

		class BSPTreePoint{
			protected:
				bool node;
				BSPTreePoint();
			public:
				bool isNode();
		}; //BSPTreePoint

///////////// BSPLeaf //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		class BSPLeaf : public BSPTreePoint{
			private:
				BSPVisdata* cluster;
				int area;
				int mins[3];
				int maxs[3];
				int numFaces;
				BSPFace** face;
				int numBrushes;
				BSPBrush** brushes;
			public:
				BSPLeaf();
				BSPLeaf(BSPVisdata const*, int, int const*, int const*, BSPFace* const*, int, BSPBrush* const*, int);
				BSPLeaf(const BSPLeaf&);
				~BSPLeaf();
				BSPLeaf& operator=(const BSPLeaf&);
				void setCluster(BSPVisdata const*);
				void setArea(int);
				void setBoxMin(int const*);
				void setBoxMax(int const*);
				void setFaces(BSPFace* const*, int);
				void setBrush(BSPBrush* const*, int);
				BSPVisdata* getCluster() const;
				int getArea() const;
				int const* getBoxMin() const;
				int const* getBoxMax() const;
				int getNumberOfFaces() const;
				BSPFace* getFace(int) const;
				int getNumberOfBrushes() const;
				BSPBrush* getBrush(int) const;
		}; //BSPLeaf

///////////// BSPNode ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
		class BSPNode : public BSPTreePoint{
			private:
				BSPPlane* plane;
				BSPTreePoint* left;
				BSPTreePoint* right;
				int mins[3];
				int maxs[3];
			public:
				BSPNode();
				BSPNode(BSPPlane const*, BSPTreePoint const*, BSPTreePoint const*, int const*, int const*);
				void setPlane(BSPPlane const*);
				void setLeftChild(BSPTreePoint const*);
				void setRightChild(BSPTreePoint const*);
				void setBoxMin(int const*);
				void setBoxMax(int const*);
				BSPPlane* getPlane() const;
				BSPTreePoint* getLeftChild() const; 
				BSPTreePoint* getRightChild() const; 
				int const* getBoxMin() const;
				int const* getBoxMax() const;
		}; //BSPNode

		//TODO entity, model, lightval, etc

	}; //gunit
}; //siege

#endif //BSP_STRUCT_H
