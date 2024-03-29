// QUAKE3 BSP strucure

#ifndef BSP_STRUCT_H
#define  BSP_STRUCT_H

#include<vector>
#include<GL/gl.h>
#include"math/Vector3.h"
#include"utils.h"
#include"scene/BoundingBox.h"

namespace siege{
	namespace gunit{

		using namespace siege::math;

////////////// SIZE //////////////////////////////////////////
//////////////////////////////////////////////////////////////

		static const int BSP_VERTEX_SIZE = 44;
		static const int BSP_LIGHTMAP_SIZE = 128*128*3;
		static const int BSP_PLANE_SIZE = 16;
		static const int BSP_TEXTURE_SIZE = 72;
		static const int BSP_BRUSHSIDE_SIZE = 8;
		static const int BSP_BRUSH_SIZE = 12;
		static const int BSP_EFFECT_SIZE = 72;
		static const int BSP_FACE_SIZE = 104;
		static const int BSP_LEAF_SIZE = 48;
		static const int BSP_NODE_SIZE = 36;
		static const int BSP_MODEL_SIZE = 40;
		static const int BSP_LIGHVAL_SIZE = 8;

//mehsvert, leafbrush, leafface are not needed to be make as class

///////////// BSPDir ///////////////////////////////////////
////////////////////////////////////////////////////////////
		class BSPDir{
			private:
				unsigned int offset;
				unsigned int length;
			public:
				static const byte NUMDIR = 17;
				static const byte ENTITY = 0;
				static const byte TEXTURE = 1;
				static const byte PLANE = 2;
				static const byte NODE = 3;
				static const byte LEAF = 4;
				static const byte LEAFFACE = 5;
				static const byte LEAFBRUSH = 6;
				static const byte MODEL = 7;
				static const byte BRUSH = 8;
				static const byte BRUSHSIDE = 9;
				static const byte VERTEX = 10;
				static const byte MESHVERT = 11;
				static const byte EFFECT = 12;
				static const byte FACE = 13;
				static const byte LIGHTMAP = 14;
				static const byte LIGHTVOLS = 15;
				static const byte VISDATA = 16;
				BSPDir();
				BSPDir(unsigned int, unsigned int);
				void setOffset(unsigned int);
				void setLength(unsigned int);
				unsigned int getOffset() const;
				unsigned int getLength() const;
		}; //BSPDir

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
				static const GLuint DEFAULT_TEXTURE_QUALITY = GL_LINEAR_MIPMAP_NEAREST;
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
			public:
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
				int numMeshes;
				int* meshes;
				BSPLightmap* lightmap;
				int lightmapStart[2];
				int lightmapSize[2];
				Vector3 normal;
			public:
				BSPFace();
				BSPFace(BSPTexture*, BSPEffect*, BSPVertex**, int, int const*, int, BSPLightmap*, int const*, int const*, const Vector3);
				BSPFace(const BSPFace&);
				virtual ~BSPFace();
				BSPFace& operator=(const BSPFace&);
				void setTexture(BSPTexture*);
				void setEffect(BSPEffect*);
				void setVertices(BSPVertex**, int);
				void setMeshes(int const*, int);
				void setLighMap(BSPLightmap*, int const*, int const*);
				void setNormal(const Vector3);
				BSPTexture* getTexture() const;
				BSPEffect* getEffect() const;
				/*int getNumberOfVertices() const;
				BSPVertex const* getVertex(int) const;
				hasonloan a meshekre sem valoszinu h fog kelleni*/
				BSPLightmap* getLightmap() const;
				Vector3 getNormal() const;
				virtual void draw() const = 0;
		}; //BSPFace

///////////// BSPPolygon ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
		class BSPPolygon : public BSPFace{
			private:
				Vector3 lightmapOrigin;
				Vector3 lightmapS;
				Vector3 lightmapT;
			public:
				BSPPolygon();
				BSPPolygon(BSPTexture*, BSPEffect*, BSPVertex**, int, int const*, int, BSPLightmap*, 
							int const*, int const*, Vector3, Vector3, Vector3, Vector3);
				BSPPolygon(const BSPPolygon&);
				BSPPolygon& operator=(const BSPPolygon&);
				void setLightmapOrigin(Vector3);
				void setLightmapS(Vector3);
				void setLightmapT(Vector3);
				Vector3 getLightmapS() const;
				Vector3 getLightmapT() const;
				Vector3 getLightmapOrigin() const;
				void draw() const;
		}; //BSPPolygon

///////////// BSPPatch //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
		class BSPPatch : public BSPFace{
			private:
				int dimension[2];
			public:
				BSPPatch();
				BSPPatch(BSPTexture*, BSPEffect*, BSPVertex**,int, BSPLightmap*, int const*, int const*, Vector3, int const*);
				BSPPatch(const BSPPatch&);
				BSPPatch& operator=(const BSPPatch&);
				void setDimension(int const*);
				int const* getDimension() const;
				void draw() const;
		}; //BSPPatch

///////////// BSPMesh ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
		class BSPMesh : public BSPFace{
			public:
				BSPMesh();
				BSPMesh(BSPTexture*, BSPEffect*, BSPVertex**, int, int const*, int, BSPLightmap*, int const*, int const*, Vector3);
				BSPMesh(const BSPMesh&);
				BSPMesh& operator=(const BSPMesh&);
				void draw() const;
		}; //BSPMesh

///////////// BSPBillboard //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
		class BSPBillboard : public BSPFace{
			public:
				BSPBillboard();
				BSPBillboard(BSPTexture*, BSPEffect*, BSPVertex*, BSPLightmap*, int const*, int const*, Vector3);
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
				int visSize;
				BSPVisdata** visdata;
				std::vector<BSPLeaf*> leaves;
				std::vector<BSPLeaf*>::iterator lit;
			public:
				BSPVisdata();
				BSPVisdata(int);
				BSPVisdata(BSPVisdata**, int);
				BSPVisdata(const BSPVisdata&);
				~BSPVisdata();
				BSPVisdata& operator=(const BSPVisdata&);
				void resetVisData(int);
				void addVisdata(BSPVisdata*);
				void setVisdata(BSPVisdata**, int, int);
				void addLeaf(BSPLeaf*);
				int getNumberOfVisdata() const;
				BSPVisdata* getVisData(int) const;
				int getNumberOfLeaves() const;
				BSPLeaf* getLeaf(int) const;
				void draw() const;
				void drawAllVisible() const;
		}; //BSPVisdata
		
///////////// BSPTreePoint /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		class BSPTreePoint{
			protected:
				bool node;
				scene::BoundingBox box;
			public:
				BSPTreePoint();
				BSPTreePoint(scene::BoundingBox);
				bool isNode();
				bool isInside(Vector3);
				void setBoundingBox(scene::BoundingBox);
				scene::BoundingBox getBoundingBox() const;
				virtual void draw()const = 0;
		}; //BSPTreePoint

///////////// BSPLeaf //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		class BSPLeaf : public BSPTreePoint{
			private:
				BSPVisdata* cluster;
				int area;
				int numFaces;
				BSPFace** faces;
				int numBrushes;
				BSPBrush** brushes;
			public:
				BSPLeaf();
				BSPLeaf(BSPVisdata*, int, BSPFace**, int, BSPBrush**, int, scene::BoundingBox);
				BSPLeaf(const BSPLeaf&);
				~BSPLeaf();
				BSPLeaf& operator=(const BSPLeaf&);
				void setCluster(BSPVisdata*);
				void setArea(int);
				void setFaces(BSPFace**, int);
				void setBrushes(BSPBrush**, int);
				BSPVisdata* getCluster() const;
				int getArea() const;
				int getNumberOfFaces() const;
				BSPFace* getFace(int) const;
				int getNumberOfBrushes() const;
				BSPBrush* getBrush(int) const;
				void draw() const;
		}; //BSPLeaf

///////////// BSPNode ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
		class BSPNode : public BSPTreePoint{
			private:
				BSPPlane* plane;
				BSPTreePoint* left;
				BSPTreePoint* right;
			public:
				BSPNode();
				BSPNode(BSPPlane*, BSPTreePoint*, BSPTreePoint*, scene::BoundingBox);
				void setPlane(BSPPlane*);
				void setLeftChild(BSPTreePoint*);
				void setRightChild(BSPTreePoint*);
				BSPPlane* getPlane() const;
				BSPTreePoint* getLeftChild() const; 
				BSPTreePoint* getRightChild() const; 
				void draw() const;
		}; //BSPNode

		//TODO entity, model, lightval, etc

	}; //gunit
}; //siege

#endif //BSP_STRUCT_H
