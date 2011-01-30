#include"gunit/BSPMap.h"
#include"SiegeException.h"
#include"gunit/BSPException.h"
#include<string.h>
#include<fstream>
#include<string>

namespace siege{
	namespace gunit{

	using namespace std;

	void BSPMap::init(){
		path = NULL;
		texQuality = DEFAULT_TEXTURE_QUALITY;
		numVertices = 0;
		vertices = NULL;
		numLightmaps = 0;
		lightmaps = NULL;
		numPlanes = 0;
		planes = NULL;
		numTextures = 0;
		textures = NULL;
		numBrushsides = 0;
		brushsides = NULL;
		numBrushes = 0;
		brushes = NULL;
		numEffects = 0;
		effects = NULL;
		numFaces = 0;
		faces = NULL;
		numClusters = 0;
		clusters = NULL;
		numLeaves = 0;
		leaves = NULL;
		numNodes = 0;
		nodes = NULL;
	}

	BSPMap::BSPMap(){
		init();
	}

	BSPMap::BSPMap(char const* p){
		init();
		setPath(p);
	}

	BSPMap::BSPMap(const BSPMap& m){
		init();
		*this = m;
	}

	BSPMap::~BSPMap(){
		if(path != NULL)
			delete[] path;
		if(vertices != NULL)
			delete[] vertices;
		if(lightmaps != NULL)
			delete[] lightmaps;
		if(planes != NULL)
			delete[] planes;
		if(textures != NULL)
			delete[] textures;
		if(brushsides != NULL)
			delete[] brushsides;
		if(brushes != NULL)
			delete[] brushes;
		if(effects != NULL)
			delete[] effects;
		if(faces != NULL){
			for(unsigned int i=0; i<numFaces; i++)
				delete faces[i];
			delete[] faces;
		}
		if(clusters != NULL)
			delete[] clusters;
		if(leaves != NULL)
			delete[] leaves;
		if(nodes != NULL)
			delete[] nodes;
	}

	BSPMap& BSPMap::operator=(const BSPMap& m){
		setPath(m.path);
		return *this;
	}

	void BSPMap::read(std::ifstream &in, byte type, BSPDir* dirs, void (BSPMap::*func)(char*, unsigned int)){
		int len = dirs[type].getLength();
		char buffer[len];
		in.seekg(dirs[type].getOffset(), std::ios::beg);
		in.read(buffer, len);
		(this->*func)(buffer, len);
	}

	void BSPMap::load(){
		if(path == NULL)
			throw SiegeException("Path hasn't been set in BSPMap!");
		load(path);
	}

	void BSPMap::load(char const* p){
		if(path == NULL)
			setPath(p);
		else if(strcmp(path, p) != 0)
			setPath(p);

		std::ifstream in(p, std::ios::in | std::ios::binary);
		if(!in.is_open()){
			std::string ms("The given path is incorrect or the file cannot be opened: ");
			ms.append(p);
			throw SiegeException(ms);
		}

		////////////// LOAD HEADER ////////////////////////

		int len = 8+BSPDir::NUMDIR*8;
		char* buffer = new char[len];
		char* ptr = buffer;
		in.read(buffer, len);
		char magic[4];
		memcpy(magic, ptr, sizeof(magic));
		ptr += sizeof(magic);
		if(strncmp(magic, "IBSP", 4) != 0)
			throw BSPException("File is not a valid BSP file.");
		int version;
		memcpy(&version, ptr, 4);
		ptr += 4;
		if(version != 46)
			throw BSPException("BSP map's version is not 46!");

		BSPDir dirs[BSPDir::NUMDIR];
		for(int i=0; i<BSPDir::NUMDIR; i++){
			BSPDir d;
			unsigned int tmp;
			memcpy(&tmp, ptr, 4);
			ptr += 4;
			d.setOffset(tmp);
			memcpy(&tmp, ptr, 4);
			ptr += 4;
			d.setLength(tmp);
			dirs[i] = d;
		}
		delete[] buffer;
		read(in, BSPDir::ENTITY, dirs, &BSPMap::loadEntities);
		read(in, BSPDir::VERTEX, dirs, &BSPMap::loadVertices);
		read(in, BSPDir::LIGHTMAP, dirs, &BSPMap::loadLighmaps);
		read(in, BSPDir::PLANE, dirs, &BSPMap::loadPlanes);
		read(in, BSPDir::TEXTURE, dirs, &BSPMap::loadTextures);
		read(in, BSPDir::BRUSHSIDE, dirs, &BSPMap::loadBrushsides);
		read(in, BSPDir::BRUSH, dirs, &BSPMap::loadBrushes);
		read(in, BSPDir::EFFECT, dirs, &BSPMap::loadEffects);
		read(in, BSPDir::MESHVERT, dirs, &BSPMap::loadMeshverts);
		read(in, BSPDir::FACE, dirs, &BSPMap::loadFaces);
		read(in, BSPDir::LEAFFACE, dirs, &BSPMap::loadLeafFaces);
		read(in, BSPDir::LEAFBRUSH, dirs, &BSPMap::loadLeafBrushes);
		read(in, BSPDir::VISDATA, dirs, &BSPMap::loadClusters);
		read(in, BSPDir::LEAF, dirs, &BSPMap::loadLeaves);
		read(in, BSPDir::NODE, dirs, &BSPMap::loadNodes);

		in.close();
	}

	void BSPMap::loadEntities(char* ptr, unsigned int len){
		char data[len];
		memcpy(data, ptr, len);
		//cout << data << endl;
		//TODO data feldolgozasa
	}

	void BSPMap::initVertices(int n){
		if(vertices != NULL){
			delete[] vertices;
			vertices = NULL;
			numVertices = 0;
		}
		if(n == 0)
			return;
		numVertices = n;
		vertices = new BSPVertex[n];
	}

	void BSPMap::loadVertices(char* ptr, unsigned int len){
		int num = len/BSP_VERTEX_SIZE;
		initVertices(num);
		for(int i=0; i<num; i++){
			float pos[3];
			memcpy(pos, ptr, sizeof(pos));
			ptr += sizeof(pos);
			math::Vector3 position(pos);
			float sc[2];
			memcpy(sc, ptr, sizeof(sc));
			ptr += sizeof(sc);
			float lc[2];
			memcpy(lc, ptr, sizeof(lc));
			ptr += sizeof(lc);
			memcpy(pos, ptr, sizeof(pos));
			ptr += sizeof(pos);
			math::Vector3 norm(pos);
			byte col[4];
			memcpy(col, ptr, sizeof(col));
			ptr += sizeof(col);
			vertices[i] = BSPVertex(position, sc, lc, norm, col);
		}
	}

	void BSPMap::initLightmaps(int n){
		if(lightmaps != NULL){
			delete[] lightmaps;
			lightmaps = NULL;
			numLightmaps = 0;
		}
		if(n == 0)
			return;
		numLightmaps = n;
		lightmaps = new BSPLightmap[n];
	}

	void BSPMap::loadLighmaps(char* ptr, unsigned int len){
		//TODO
		/*int num = len/BSP_LIGHTMAP_SIZE;
		initLightmaps(num);
		for(int i=0; i<num; i++){
			memcpy(b, ptr, sizeof(b));
			ptr += sizeof(b);
			lightmaps[i] = BSPLightmap(b);
		}*/
	}

	void BSPMap::initPlanes(int n){
		if(planes != NULL){
			delete[] planes;
			planes = NULL;
			numPlanes = 0;
		}
		if(n == 0)
			return;
		numPlanes = n;
		planes = new BSPPlane[n];
	}

	void BSPMap::loadPlanes(char* ptr, unsigned int len){
		int num = len/BSP_PLANE_SIZE;
		initPlanes(num);
		for(int i=0; i<num; i++){
			float f[3];
			memcpy(f, ptr, sizeof(f));
			ptr += sizeof(f);
			math::Vector3 norm(f);
			float d;
			memcpy(&d, ptr, sizeof(d));
			ptr += sizeof(d);
			planes[i] = BSPPlane(norm, d);
		}
	}

	void BSPMap::initTextures(int n){
		if(textures != NULL){
			delete[] textures;
			textures = NULL;
			numTextures = 0;
		}
		if(n == 0)
			return;
		numTextures = n;
		textures = new BSPTexture[n];
	}

	void BSPMap::loadTextures(char* ptr, unsigned int len){
		int num = len/BSP_TEXTURE_SIZE;
		initTextures(num);
		for(int i=0; i<num; i++){
			char path[64];
			memcpy(path, ptr, sizeof(path));
			ptr += sizeof(path);
			int flag;
			memcpy(&flag, ptr, sizeof(flag));
			ptr += sizeof(flag);
			int cts;
			memcpy(&cts, ptr, sizeof(cts));
			ptr += sizeof(cts);
			try{ //TODO utvonal beallitasa
				textures[i] = BSPTexture(path, flag, cts);
			}catch(std::exception &e){std::cerr << e.what() << std::endl;}
		}
		if(texQuality != BSPTexture::DEFAULT_TEXTURE_QUALITY){
			try{
				setTextureQuality(texQuality); //setting textures quality
			}catch(std::exception &e){std::cerr << e.what() << std::endl;}
		}
	}

	void BSPMap::initBrushsides(int n){
		if(brushsides != NULL){
			delete[] brushsides;
			brushsides = NULL;
			numBrushsides = 0;
		}
		if(n == 0)
			return;
		numBrushsides = n;
		brushsides = new BSPBrushSide[n];
	}

	void BSPMap::loadBrushsides(char* ptr, unsigned int len){
		int num = len/BSP_BRUSHSIDE_SIZE;
		initBrushsides(num);
		for(int i=0; i<num; i++){
			int p;
			memcpy(&p, ptr, sizeof(p));
			ptr += sizeof(p);
			int t;
			memcpy(&t, ptr, sizeof(t));
			ptr += sizeof(t);
			brushsides[i] = BSPBrushSide(&planes[p], &textures[t]);
		}
	}

	void BSPMap::initBrushes(int n){
		if(brushes != NULL){
			delete[] brushes;
			brushes = NULL;
			numBrushes = 0;
		}
		if(n == 0)
			return;
		numBrushes = n;
		brushes = new BSPBrush[n];
	}

	void BSPMap::loadBrushes(char* ptr, unsigned int len){
		int num = len/BSP_BRUSH_SIZE;
		initBrushes(num);
		for(int i=0; i<num; i++){
			int fb;
			memcpy(&fb, ptr, sizeof(fb));
			ptr += sizeof(fb);
			int nb;
			memcpy(&nb, ptr, sizeof(nb));
			ptr += sizeof(nb);
			int t;
			memcpy(&t, ptr, sizeof(t));
			ptr += sizeof(t);
			BSPBrushSide* bs[nb];
			for(int k=0; k<nb; k++)
				bs[k] = &brushsides[k+fb];
			brushes[i] = BSPBrush(bs, nb, &textures[t]);
		}
	}

	void BSPMap::initEffects(int n){
		if(effects != NULL){
			delete[] effects;
			effects = NULL;
			numEffects = 0;
		}
		if(n == 0)
			return;
		numEffects = n;
		effects = new BSPEffect[n];
	}

	void BSPMap::loadEffects(char* ptr, unsigned int len){
		int num = len/BSP_EFFECT_SIZE;
		initEffects(num);
		for(int i=0; i<num; i++){
			char name[64];
			memcpy(name, ptr, sizeof(name));
			ptr += sizeof(name);
			int b;
			memcpy(&b, ptr, sizeof(b));
			ptr += sizeof(b) + sizeof(int); // +4 because of unknown data
			effects[i] = BSPEffect(name, &brushes[b]);
		}
	}

	void BSPMap::loadMeshverts(char* ptr, unsigned int len){
		int num = len/4;
		meshverts = new int[num];
		for(int i=0; i<num; i++){
			memcpy(&meshverts[i], ptr, 4);
			ptr += 4;
		}
	}

	void BSPMap::loadLeafFaces(char* ptr, unsigned int len){
		int num = len/4;
		leaffaces = new int[num];
		for(int i=0; i<num; i++){ 
			memcpy(&leaffaces[i], ptr, 4);
			ptr += 4;
		}
	}

	void BSPMap::loadLeafBrushes(char* ptr, unsigned int len){
		int num = len/4;
		leafbrushes = new int[num];
		for(int i=0; i<num; i++){
			memcpy(&leafbrushes[i], ptr, 4);
			ptr += 4;
		}
	}

	void BSPMap::initFaces(int n){
		if(faces != NULL){
			delete[] faces;
			faces = NULL;
			numFaces = 0;
		}
		if(n == 0)
			return;
		numFaces = n;
		faces = new BSPFace*[n];
	}

	void BSPMap::loadFaces(char* ptr, unsigned int len){
		int num = len/BSP_FACE_SIZE;
		initFaces(num);
		for(int i=0; i<num; i++){
			int tex;
			memcpy(&tex, ptr, sizeof(tex));
			ptr += sizeof(tex);
			int eff;
			memcpy(&eff, ptr, sizeof(eff));
			ptr += sizeof(eff);
			int type;
			memcpy(&type, ptr, sizeof(type));
			ptr += sizeof(type);
			int vi;
			memcpy(&vi, ptr, sizeof(vi));
			ptr += sizeof(vi);
			int nv;
			memcpy(&nv, ptr, sizeof(nv));
			ptr += sizeof(nv);
			int mi;
			memcpy(&mi, ptr, sizeof(mi));
			ptr += sizeof(mi);
			int nm;
			memcpy(&nm, ptr, sizeof(nm));
			ptr += sizeof(nm);
			int lmi;
			memcpy(&lmi, ptr, sizeof(lmi));
			ptr += sizeof(lmi);
			int lmst[2];
			memcpy(lmst, ptr, sizeof(lmst));
			ptr += sizeof(lmst);
			int lmsi[2];
			memcpy(lmsi, ptr, sizeof(lmsi));
			ptr += sizeof(lmsi);
			float lmo[3];
			memcpy(lmo, ptr, sizeof(lmo));
			ptr += sizeof(lmo);
			float lmv[2][3];
			memcpy(lmv, ptr, sizeof(lmv));
			ptr += sizeof(lmv);
			float nor[3];
			memcpy(nor, ptr, sizeof(nor));
			ptr += sizeof(nor);
			math::Vector3 normal(nor);
			int dim[2];
			memcpy(dim, ptr, sizeof(dim));
			ptr += sizeof(dim);

			BSPVertex* vert[nv];
			for(int k=0; k<nv; k++)
				vert[k] = &vertices[vi+k];
			int mesh[nm];
			for(int k=0; k<nm; k++)
				mesh[k] = meshverts[mi+k];
			if(type == 1){ //polygon
				faces[i] = new BSPPolygon(&textures[tex], &effects[eff], vert, nv, mesh, nm, &lightmaps[lmi], lmst, lmsi, normal, math::Vector3(lmo),
										math::Vector3(lmv[0]), math::Vector3(lmv[1]));
			}else if(type == 2){ //patch
				faces[i] = new BSPPatch(&textures[tex], &effects[eff], vert, nv, &lightmaps[lmi], lmst, lmsi, normal, dim);
			}else if(type == 3){ //mesh
				faces[i] = new BSPMesh(&textures[tex], &effects[eff], vert, nv, mesh, nm, &lightmaps[lmi], lmst, lmsi, normal);
			}else{ //billboard
				faces[i] = new BSPBillboard(&textures[tex], &effects[eff], vert[0], &lightmaps[lmi], lmst, lmsi, normal);
			}
		}
		delete[] meshverts;
	}

	void BSPMap::initClusters(int n){
		if(clusters != NULL){
			delete[] clusters;
			clusters = NULL;
			numClusters = 0;
		}
		if(n == 0)
			return;
		numClusters = n;
		clusters = new BSPVisdata[n];
	}

	void BSPMap::loadClusters(char* ptr, unsigned int len){
		int num;
		memcpy(&num, ptr, sizeof(num));
		ptr += sizeof(num);
		int size;
		memcpy(&size, ptr, sizeof(size));
		ptr += sizeof(size);
		
		initClusters(num);
		for(int i=0; i<num; i++)
			clusters[i] = BSPVisdata(num);
		byte vec[num*size];
		memcpy(vec, ptr, sizeof(vec));
		for(int y=0; y<num; y++){
			for(int x=0; x<num; x++){
				if(vec[x*size + y/8] & (1<<y%8))
					clusters[y].addVisdata(&clusters[x]);
			}
		}
	}

	void BSPMap::initLeaves(int n){
		if(leaves != NULL){
			delete[] leaves;
			leaves = NULL;
			numLeaves = 0;
		}
		if(n == 0)
			return;
		numLeaves = n;
		leaves = new BSPLeaf[n];
	}

	void BSPMap::loadLeaves(char* ptr, unsigned int len){
		int num = len/BSP_LEAF_SIZE;
		initLeaves(num);
		for(int i=0; i<num; i++){
			int clu;
			memcpy(&clu, ptr, sizeof(clu));
			ptr += sizeof(clu);
			int are;
			memcpy(&are, ptr, sizeof(are));
			ptr += sizeof(are);
			int tmpi[3];
			memcpy(tmpi, ptr, sizeof(tmpi));
			ptr += sizeof(tmpi);
			float tmpf[3] = {tmpi[0], tmpi[1], tmpi[2]};
			math::Vector3 min(tmpf);
			memcpy(tmpi, ptr, sizeof(tmpi));
			ptr += sizeof(tmpi);
			float tmpf2[3] = {tmpi[0], tmpi[1], tmpi[2]};
			math::Vector3 max(tmpf2);
			int lf;
			memcpy(&lf, ptr, sizeof(lf));
			ptr += sizeof(lf);
			int nlf;
			memcpy(&nlf, ptr, sizeof(nlf));
			ptr += sizeof(nlf);
			int lb;
			memcpy(&lb, ptr, sizeof(lb));
			ptr += sizeof(lb);
			int nlb;
			memcpy(&nlb, ptr, sizeof(nlb));
			ptr += sizeof(nlb);
			BSPFace* fac[nlf];
			for(int k=0; k<nlf; k++){
				fac[k] = faces[leaffaces[lf+k]];
			}
			BSPBrush* bru[nlb];
			for(int k=0; k<nlb; k++)
				bru[k] = &brushes[leafbrushes[lb+k]];
			BSPVisdata* vd = NULL;
			if(clu > -1)
				vd = &clusters[clu];
			leaves[i] = BSPLeaf(vd, are, fac, nlf, bru, nlb, scene::BoundingBox(min, max));
		}
		delete[] leaffaces;
		delete[] leafbrushes;
	}

	void BSPMap::initNodes(int n){
		if(nodes != NULL){
			delete[] nodes;
			nodes = NULL;
			numNodes = 0;
		}
		if(n == 0)
			return;
		numNodes = n;
		nodes = new BSPNode[n];
	}

	void BSPMap::loadNodes(char* ptr, unsigned int len){
		int num = len/BSP_NODE_SIZE;
		initNodes(num);
		for(int i=0; i<num; i++){
			int plane;
			memcpy(&plane, ptr, sizeof(plane));
			ptr += sizeof(plane);
			int ch[2];
			memcpy(ch, ptr, sizeof(ch));
			ptr += sizeof(ch);
			int tmp[3];
			memcpy(tmp, ptr, sizeof(tmp));
			ptr += sizeof(tmp);
			float f1[3] = {tmp[0], tmp[1], tmp[2]};
			math::Vector3 min(f1);
			memcpy(tmp, ptr, sizeof(tmp));
			ptr += sizeof(tmp);
			float f2[3] = {tmp[0], tmp[1], tmp[2]};
			math::Vector3 max(f2);
			BSPTreePoint* left;
			if(ch[0] < 0)
				left = &leaves[-(ch[0]+1)];
			else
				left = &nodes[ch[0]];

			BSPTreePoint* right;
			if(ch[1] < 0)
				right= &leaves[-(ch[1]+1)];
			else
				right = &nodes[ch[1]];

			nodes[i] = BSPNode(&planes[plane], left, right, scene::BoundingBox(min, max));
		}
	}

	void BSPMap::setPath(char const* p){
		if(path != NULL){
			delete[] path;
			path = NULL;
		}
		if(p == NULL)
			return;
		path = new char[strlen(p)+1];
		strcpy(path, p);
	}

	void BSPMap::draw() const{
		if(leaves != NULL){
			for(unsigned int i=0; i<numLeaves; i++)
				leaves[i].draw();
		}
	}

	void BSPMap::draw(math::Vector3 v) const{
		BSPTreePoint* t = &nodes[0];
		while(t->isNode()){
			BSPNode* n = (BSPNode*)t;
			if(n->getLeftChild()->isInside(v))
				t = n->getLeftChild();
			else
				t = n->getRightChild();
		}
		BSPLeaf* l = (BSPLeaf*)t;
		if(l->getCluster() == NULL)
			l->draw();
		else
			l->getCluster()->drawAllVisible();
	}

	void BSPMap::setTextureQuality(GLuint q){
		texQuality = q;
		if(textures != NULL){
			for(unsigned int i=0; i<numTextures; i++)
				textures[i].setTextureQuality(q);
		}
	}

	}; //gunit
}; //siege
