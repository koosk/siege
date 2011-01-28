#include"gunit/BSPStruct.h"
#include"BadIndexException.h"
#include"SiegeException.h"
#include<string.h>

namespace siege{
	namespace gunit{

		using namespace math;

//////////////// BSPVertex ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

		BSPVertex::BSPVertex(){}

		BSPVertex::BSPVertex(const Vector3 pos, float const* sur, float const* lm, const Vector3 norm, byte const* color){
			setPosition(pos);
			setSurfaceTextureCoordinate(sur);
			setLightmapTextureCoordinate(lm);
			setNormal(norm);
			setColor(color);
		}

		void BSPVertex::setPosition(const Vector3 p){
			position = p;
		}

		void BSPVertex::setSurfaceTextureCoordinate(float const* f){
			memcpy(texcoord[0], f, sizeof(f));	
		}
		void BSPVertex::setLightmapTextureCoordinate(float const* f){
			memcpy(texcoord[1], f, sizeof(f));
		}

		void BSPVertex::setNormal(const Vector3 n){
			normal = n;
		}

		void BSPVertex::setColor(byte const* c){
				memcpy(color, c, sizeof(c));
		}

		Vector3 BSPVertex::getPosition() const{
			return position;
		}

		float const* BSPVertex::getSurfaceTextureCoordinate() const{
			return texcoord[0];
		}

		float const* BSPVertex::getLightmapTextureCoordinate() const{
			return texcoord[1];
		}

		Vector3 BSPVertex::getNormal() const{
			return normal;
		}

		byte const* BSPVertex::getColor() const{
			return color;
		}

/////////////////////////// BSPLightmap /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

		BSPLightmap::BSPLightmap(){}

		BSPLightmap::BSPLightmap(byte** const* v){
			setValue(v);
		}

		void BSPLightmap::setValue(byte** const* v){
			memcpy(value, v, sizeof(v));
		}

		//TODO
		/*byte** const* BSPLightmap::getValue(){
			return value;
		}*/

//////////////////////////// BSPPlane //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

		BSPPlane::BSPPlane(){}

		BSPPlane::BSPPlane(const Vector3 n, const float d){
			setNormal(n);
			setDistance(d);
		}

		void BSPPlane::setNormal(const Vector3 n){
			normal = n;
		}

		void BSPPlane::setDistance(const float d){
			distance = d;
		}

		Vector3 BSPPlane::getNormal() const{
			return normal;
		}

		float BSPPlane::getDistance() const{
			return distance;
		}

/////////////////////////// BSPTexture ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

		BSPTexture::BSPTexture(){
			strcpy(path, "None");
			texture = 0;
			texquality = GL_LINEAR_MIPMAP_NEAREST;
		}

		BSPTexture::BSPTexture( char const* path, const int flags, const int cont){
			setPath(path);
			setFlags(flags);
			setContents(cont);
			texquality = GL_LINEAR_MIPMAP_NEAREST;
		}

		void BSPTexture::loadTexture(){
			texture = loadImage(path, texquality);
		}

		void BSPTexture::setPath(char const* p){
			if(strcmp(p, "None") == 0 || p == NULL){
				strcpy(path, "None");
				texture = 0;
				return;
			}
			strcpy(path, p);
			loadTexture();
		}

		void BSPTexture::setFlags(const int f){
			flags = f;
		}

		void BSPTexture::setContents(const int c){
			contents = c;
		}

		void BSPTexture::setTextureQuality(GLuint q){
			texquality = q;
			if(strcmp(path, "None") != 0)
				loadTexture();
		}

		char const* BSPTexture::getPath() const{
			return path;
		}

		int BSPTexture::getFlags() const{
			return flags;
		}

		int BSPTexture::getContents() const{
			return contents;
		}

		GLuint BSPTexture::getTexture() const{
			return texture;
		}

//////////////////////// BSPBrushSide ////////////////////////////////
//////////////////////////////////////////////////////////////////////

		BSPBrushSide::BSPBrushSide(){}

		BSPBrushSide::BSPBrushSide(BSPPlane* p, BSPTexture* t){
			setPlane(p);
			setTexture(t);
		}

		void BSPBrushSide::setPlane(BSPPlane* p){
			plane = p;
		}

		void BSPBrushSide::setTexture(BSPTexture* t){
			texture = t;
		}

		BSPPlane* BSPBrushSide::getPlane() const{
			return plane;
		}

		BSPTexture* BSPBrushSide::getTexture() const{
			return texture;
		}

////////////////////// BSPBrush ////////////////////////////////////
////////////////////////////////////////////////////////////////////

		BSPBrush::BSPBrush(){
			numbs = 0;
			brusSides = NULL;	
		}

		BSPBrush::BSPBrush(BSPBrushSide** bs, int n, BSPTexture* t){
			numbs = 0;
			brusSides = NULL;	
			setBrushSides(bs, n);
			setTexture(t);
		}

		BSPBrush::BSPBrush(const BSPBrush &b){
			*this = b;
		}

		BSPBrush::~BSPBrush(){
			if(brusSides != NULL)
				delete[] brusSides;
		}

		BSPBrush& BSPBrush::operator=(const BSPBrush& b){
			numbs = 0;
			brusSides = NULL;	
			setBrushSides(b.brusSides, b.numbs);
			setTexture(b.texture);
			return *this;
		}

		void BSPBrush::setBrushSides(BSPBrushSide** bs, int n){
			if(brusSides != NULL){
				delete[] brusSides;
				brusSides = NULL;
				numbs = 0;
			}
			if(bs == NULL || n == 0)
				return;
			numbs = n;
			brusSides = new BSPBrushSide*[n];
			memcpy(brusSides, bs, sizeof(bs));
		}

		void BSPBrush::setTexture(BSPTexture* t){
			texture = t;
		}

		int BSPBrush::getNumberOfBrushSides() const{
			return numbs;
		}

		BSPBrushSide* BSPBrush::getBrushSide(int i) const{
			if(i<0 || i>=numbs)
				throw BadIndexException("Index is out of bounds in BSPBrush while getting BSPBrushSide!");
			return brusSides[i];
		}

		BSPTexture* BSPBrush::getTexture() const{
			return texture;
		}

/////////////////// BSPEffect /////////////////////////////////////
///////////////////////////////////////////////////////////////////

		BSPEffect::BSPEffect(){
			setName((char*)NULL);
		}

		BSPEffect::BSPEffect(char const* nm, BSPBrush* b){
			setName(nm);
			setBrush(b);
		}

		void BSPEffect::setName(char const* n){
			if(n == NULL)
				strcpy(name, "Unnamed");
			else
				strcpy(name, n);
		}

		void BSPEffect::setBrush(BSPBrush* b){
			brush = b;
		}

		char const* BSPEffect::getName() const{
			return name;
		}

		BSPBrush* BSPEffect::getBrush() const{
			return brush;
		}

///////////////////// BSPFace ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

		BSPFace::BSPFace(){
			numVertices = 0;
			vertices = NULL;
			numMeshes = 0;
			meshes = NULL;
		}

		BSPFace::BSPFace(BSPTexture* tex, BSPEffect* eff, BSPVertex** ver, int nv, int const* mesh,
						int nm, BSPLightmap* lm, int const* lmst, int const* lmsi, const Vector3 norm)
		{
			setTexture(tex);
			setEffect(eff);
			numVertices = 0;
			vertices = NULL;
			numMeshes = 0;
			meshes = NULL;
			setVertices(ver, nv);
			setMeshes(mesh, nm);
			setLighMap(lm, lmst, lmsi);
			setNormal(norm);
		}

		BSPFace::BSPFace(const BSPFace &f){
			*this = f;
		}

		BSPFace::~BSPFace(){
			if(vertices != NULL)
				delete[] vertices;
			if(meshes != NULL)
				delete[] meshes;
		}

		BSPFace& BSPFace::operator=(const BSPFace &f){
			setTexture(f.texture);
			setEffect(f.effect);
			numVertices = 0;
			vertices = NULL;
			numMeshes = 0;
			meshes = NULL;
			setVertices(f.vertices, f.numVertices);
			setMeshes(f.meshes, f.numMeshes);
			setLighMap(f.lightmap, f.lightmapStart, f.lightmapSize);
			setNormal(f.normal);
			return *this;
		}

		void BSPFace::setTexture(BSPTexture* t){
			texture = t;
		}

		void BSPFace::setEffect(BSPEffect* e){
			effect = e;
		}

		void BSPFace::setVertices(BSPVertex** v, int n){
			if(vertices != NULL){
				delete[] vertices;
				vertices = NULL;
				numVertices = 0;
			}
			if(v == NULL || n == 0)
				return;
			numVertices = n;
			vertices = new BSPVertex*[n];
			memcpy(vertices, v, sizeof(v));
		}

		void BSPFace::setMeshes(int const* m, int n){
			if(meshes != NULL){
				delete[] meshes;
				meshes = NULL;
				numMeshes = 0;
			}
			if(m == NULL || n == 0)
				return;
			numMeshes = n;
			meshes = new int[n];
			memcpy(meshes, m, sizeof(m));
		}

		void BSPFace::setLighMap(BSPLightmap* lm, int const* lmst, int const* lmsi){
			lightmap = lm;
			if(lm == NULL)
				return;
			memcpy(lightmapStart, lmst, sizeof(lmst));
			memcpy(lightmapSize, lmsi, sizeof(lmsi));
		}

		void BSPFace::setNormal(const Vector3 n){
			normal = n;
		}

		BSPTexture* BSPFace::getTexture() const{
			return texture;
		}

		BSPEffect* BSPFace::getEffect() const{
			return effect;
		}

		BSPLightmap* BSPFace::getLightmap() const{
			return lightmap;
		}

		Vector3 BSPFace::getNormal() const{
			return normal;
		}

/////////////////////////// BSPPolygon ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

		BSPPolygon::BSPPolygon() : BSPFace(){}

		BSPPolygon::BSPPolygon(BSPTexture* tex, BSPEffect* eff, BSPVertex** ver, int nv, int const* mesh, int nm,
								BSPLightmap* lm, int const* lmst, int const* lmsi, Vector3 norm, Vector3 lmo, Vector3 lms, Vector3 lmt)
								: BSPFace(tex, eff, ver, nv, mesh, nm, lm, lmst, lmsi, norm)
		{
			setLightmapOrigin(lmo);
			setLightmapS(lms);
			setLightmapT(lmt);
		}

		BSPPolygon::BSPPolygon(const BSPPolygon &p){
			*this = p;
		}

		BSPPolygon& BSPPolygon::operator=(const BSPPolygon &p){
			*((BSPFace*)this) = BSPFace::operator=(*((BSPFace*)&p));
			setLightmapOrigin(p.lightmapOrigin);
			setLightmapS(p.lightmapS);
			setLightmapT(p.lightmapT);
			return *this;
		}

		void BSPPolygon::setLightmapOrigin(Vector3 o){
			lightmapOrigin = o;
		}

		void BSPPolygon::setLightmapS(Vector3 s){
			lightmapS = s;
		}

		void BSPPolygon::setLightmapT(Vector3 t){
			lightmapT = t;
		}

		Vector3 BSPPolygon::getLightmapOrigin() const{
			return lightmapOrigin;
		}

		Vector3 BSPPolygon::getLightmapS() const {
			return lightmapS;
		}

		Vector3 BSPPolygon::getLightmapT() const {
			return lightmapT;
		}

		void BSPPolygon::draw() const{
			//TODO
		}

/////////////////////////// BSPPatch ////////////////////////////////
/////////////////////////////////////////////////////////////////////

		BSPPatch::BSPPatch() : BSPFace() {}

		BSPPatch::BSPPatch(BSPTexture* tex, BSPEffect* eff, BSPVertex** ver, int nv, BSPLightmap* lm, int const* lmst, int const* lmsi,
							Vector3 norm, int const* dim) : BSPFace(tex, eff, ver, nv, NULL, 0, lm, lmst, lmsi, norm)
		{
			setDimension(dim);
		}

		BSPPatch::BSPPatch(const BSPPatch &p){
			*this = p;
		}

		BSPPatch& BSPPatch::operator=(const BSPPatch &p){
			*((BSPFace*)this) = BSPFace::operator=(*((BSPFace*)&p));	
			setDimension(p.dimension);
			return *this;
		}

		void BSPPatch::setDimension(int const* d){
			if(d == NULL){
				dimension[0] = 0;
				dimension[1] = 0;
				return;
			}
			memcpy(dimension, d, sizeof(dimension));
		}

		int const* BSPPatch::getDimension() const{
			return dimension;
		}

		void BSPPatch::draw() const{
			//TODO
		}

/////////////////// BSPMesh //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

		BSPMesh::BSPMesh() : BSPFace() {}

		BSPMesh::BSPMesh(BSPTexture* tex, BSPEffect* eff, BSPVertex** ver, int nv, int const* mesh, int nm, 
						BSPLightmap* lm, int const* lmst, int const* lmsi, Vector3 norm) : BSPFace(tex, eff, ver, nv, mesh, nm, lm, lmst,lmsi, norm) {}

		BSPMesh::BSPMesh(const BSPMesh &m){
			*this = m;
		}

		BSPMesh& BSPMesh::operator=(const BSPMesh &m){
			*((BSPFace*)this) = BSPFace::operator=(*((BSPFace*)&m));
			return *this;
		}

		void BSPMesh::draw() const{
			//TODO
		}

/////////////////// BSPBillboard ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

		BSPBillboard::BSPBillboard() : BSPFace() {}

		BSPBillboard::BSPBillboard(BSPTexture* tex, BSPEffect* eff, BSPVertex* ver, BSPLightmap* lm, 
									int const* lmst, int const* lmsi, Vector3 norm) : BSPFace(tex, eff, NULL, 0, NULL, 0, lm, lmst, lmsi, norm)
		{
			BSPVertex* v[1] = {ver};
			setVertices(v, 1);
		}

		BSPBillboard::BSPBillboard(const BSPBillboard &b){
			*this = b;
		}

		BSPBillboard& BSPBillboard::operator=(const BSPBillboard &b){
			*((BSPFace*)this) = BSPFace::operator=(*((BSPFace*)&b));
			return *this;
		}


		void BSPBillboard::draw() const{
			//TODO
		}

/////////////////// BSPVisdata ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


		void BSPVisdata::setVisdata(BSPVisdata** vd, int size, int num = -1){
			if(num == -1)
				num = size;
			if(visdata == NULL){
				delete[] visdata;
				visdata = NULL;
				numVisdata = 0;
				visSize = 0;
			}
			if(vd == NULL || size == 0)
				return;
			visSize = size;
			numVisdata = num;
			visdata = new BSPVisdata*[size];
			for(int i=0; i<num; i++)
				visdata[i] = vd[i];
		}

		BSPVisdata::BSPVisdata(){
			numVisdata = 0;
			visSize = 0;
			visdata = NULL;
			lit = leaves.begin();
		}

		BSPVisdata::BSPVisdata(int n){
			numVisdata = 0;
			visSize = 0;
			visdata = NULL;
			resetVisData(n);
			lit = leaves.begin();
		}

		BSPVisdata::BSPVisdata(BSPVisdata** vd, int n ){
			numVisdata = 0;
			visSize = 0;
			visdata = NULL;
			setVisdata(vd, n);
			lit = leaves.begin();
		}

		BSPVisdata::BSPVisdata(const BSPVisdata &v){
			numVisdata = 0;
			visSize = 0;
			visdata = NULL;
			*this = v;
		}

		BSPVisdata::~BSPVisdata(){
			if(visdata != NULL)
				delete[] visdata;
		}

		BSPVisdata& BSPVisdata::operator=(const BSPVisdata &v){
			setVisdata(v.visdata, v.visSize, v.numVisdata);
			leaves = v.leaves;
			lit = leaves.end();
			return *this;
		}

		void BSPVisdata::resetVisData(int n){
			if(visdata != NULL){
				delete[] visdata;
				visdata = NULL;
				numVisdata = 0;
				visSize = 0;
			}
			if(n == 0)
				return;
			numVisdata = 0;
			visSize = n;
			visdata = new BSPVisdata*[n];
		}

		void BSPVisdata::addVisdata(BSPVisdata* vd){
			if(numVisdata >= visSize)
				throw SiegeException("BSPVisdata cannont be added!");
			visdata[numVisdata] = vd;
			numVisdata++;
		}

		void BSPVisdata::addLeaf(BSPLeaf* l){
			leaves.insert(lit, l);
		}

		int BSPVisdata::getNumberOfVisdata() const{
			return numVisdata;
		}

		BSPVisdata* BSPVisdata::getVisData(int i) const{
			if(i<0 || i>=numVisdata)
				throw BadIndexException("Bad index in BSPVisdata while gettint BSPVisdata!");
			return visdata[i];
		}

		int BSPVisdata::getNumberOfLeaves() const{
			return leaves.size();
		}

		BSPLeaf* BSPVisdata::getLeaf(int i) const{
			if(i<0 || i>=((unsigned int)leaves.size()))
				throw BadIndexException("Bad index in BSPVisdata while gettint BSPLeaf!");
			return leaves[i];
		}

/////////////////////////////// BSPTreePoint ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

		BSPTreePoint::BSPTreePoint(){}

		BSPTreePoint::BSPTreePoint(scene::BoundingBox b){
			setBoundingBox(b);
		}

		void BSPTreePoint::setBoundingBox(scene::BoundingBox b){
			box = b;
		}

		bool BSPTreePoint::isNode(){
			return node;
		}

		bool BSPTreePoint::isInside(Vector3 v){
			return box.isInside(v);
		}

		scene::BoundingBox BSPTreePoint::getBoundingBox() const{
			return box;
		}

////////////////////////////// BSPLeaf /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

		BSPLeaf::BSPLeaf(){
			numFaces = 0;
			faces = NULL;
			numBrushes = 0;
			brushes = NULL;
		}

		BSPLeaf::BSPLeaf(BSPVisdata* vd, int ar, BSPFace** fc, int nf, BSPBrush** bs, int ns, scene::BoundingBox b) : BSPTreePoint(b){
			setCluster(vd);
			setArea(ar);
			numFaces = 0;
			faces = NULL;
			numBrushes = 0;
			brushes = NULL;
			setFaces(fc, nf);
			setBrushes(bs, ns);
		}

		BSPLeaf::BSPLeaf(const BSPLeaf &l){
			*this = l;
		}

		BSPLeaf::~BSPLeaf(){
			if(faces == NULL)
				delete[] faces;
			if(brushes == NULL)
				delete[] brushes;
		}

		BSPLeaf& BSPLeaf::operator=(const BSPLeaf &l){
			*((BSPTreePoint*)this) = *(BSPTreePoint*)&l;
			numFaces = 0;
			faces = NULL;
			numBrushes = 0;
			brushes = NULL;
			setCluster(l.cluster);
			setArea(l.area);
			setFaces(l.faces, l.numFaces);
			setBrushes(l.brushes, l.numBrushes);
			return *this;
		}

		void BSPLeaf::setCluster(BSPVisdata* vd){
			cluster = vd;
		}

		void BSPLeaf::setArea(int a){
			area = a;
		}

		void BSPLeaf::setFaces(BSPFace** f, int n){
			if(faces == NULL){
				delete[] faces;
				faces = NULL;
				numFaces = 0;
			}
			if(f == NULL || n == 0)
				return;
			numFaces = n;
			faces = new BSPFace*[n];
			memcpy(faces, f, sizeof(f));
		}

		void BSPLeaf::setBrushes(BSPBrush** b, int n){
			if(brushes == NULL){
				delete[] brushes;
				brushes = NULL;
				numBrushes = 0;
			}
			if(b == NULL || n == 0)
				return;
			numBrushes = n;
			brushes = new BSPBrush*[n];
			memcpy(brushes, b, sizeof(b));
		}

		BSPVisdata* BSPLeaf::getCluster() const{
			return cluster;
		}

		int BSPLeaf::getArea() const{
			return area;
		}

		int BSPLeaf::getNumberOfFaces() const{
			return numFaces;
		}

		BSPFace* BSPLeaf::getFace(int i) const{
			if(i<0 || i>=numFaces)
				throw BadIndexException("Bad index while getting BSPFace in BSPLeaf!");
			return faces[i];
		}

		int BSPLeaf::getNumberOfBrushes() const{
			return numBrushes;
		}

		BSPBrush* BSPLeaf::getBrush(int i) const{
			if(i<0 || i>=numBrushes)
				throw BadIndexException("Bad index while getting BSPBrush in BSPLeaf!");
			return brushes[i];
		}

		void BSPLeaf::draw() const{
			for(int i=0; i<numFaces; i++)
				faces[i]->draw();
		}

	}; //gunit
}; //siege
