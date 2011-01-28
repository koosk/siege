#include"gunit/BSPStruct.h"
#include"BadIndexException.h"
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

	}; //gunit
}; //siege
