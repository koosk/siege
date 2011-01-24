#include"gunit/Model.h"
#include"SiegeException.h"
#include<string.h>
#include<GL/gl.h>


namespace siege{
	namespace gunit{

		bool Model::isAnimationOn(){
			return animOn;
		}

		void Model::setAnimationBegin(int n){
			animBegin = n;
		}

		void Model::setAnimationEnd(int n){
			animEnd = n;
		}

		void Model::setAnimationInterval(int from, int to ){
			if(from >= to)
				throw SiegeException("Begin must be larger than end!");
			setAnimationBegin(from);
			setAnimationEnd(to);
		}

		Model::Model(){
			animBegin = 0;
			animEnd = 0;
			animOn = false;
			modelPath = NULL;
			enaTex = true;
			pos = math::Vector3f(0, 0, 0);
			rot = math::Vector3f(0, 0, 0);
		}

		Model::Model(char* f){
			animBegin = 0;
			animEnd = 0;
			animOn = false;
			modelPath = NULL;
			setModelPath(f);
			enaTex = true;
			pos = math::Vector3f(0, 0, 0);
			rot = math::Vector3f(0, 0, 0);
		}

		Model::Model(Model& m){
			/*animBegin = m.animBegin;
			animEnd = m.animEnd;
			animOn = m.animOn;
			modelPath = NULL;
			setModelPath(m.modelPath);
			enaTex = m.enaTex;*/
			*this = m;
		}

		Model::~Model(){
			if(modelPath != NULL)
				delete[] modelPath;
		}

		Model& Model::operator=(Model& m){
			animBegin = m.animBegin;
			animEnd = m.animEnd;
			animOn = m.animOn;
			modelPath = NULL;
			setModelPath(m.modelPath);
			enaTex = m.enaTex;
			pos = m.pos;
			rot = m.rot;
			return *this;
		}

		void Model::setModelPath(char* f){
			if(modelPath != NULL){
				delete[] modelPath;
				modelPath = NULL;
			}
			modelPath = new char[strlen(f)];
			strcpy(modelPath, f);
		}

		void Model::load(){
			load(modelPath);
		}

		void Model::load(char* f){
			if(f == NULL)
				throw SiegeException("The model path hasn't been set!");
			if(strcmp(modelPath, f) != 0)
				setModelPath(f);
			loadModel(f);
		}	

		void Model::start(){
			if(animBegin < animEnd)
				animOn = true;
		}

		void Model::pause(){
			animOn = false;
		}

		void Model::stop(){
			animOn = false;
			reset();
		}
		
		void Model::draw(){
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glTranslatef(pos[0], pos[1], pos[2]);
			glRotatef(rot[0], 1, 0, 0);
			glRotatef(rot[1], 0, 1, 0);
			glRotatef(rot[2], 0, 0, 1);
			drawModel();
			glPopMatrix();
		}

		int Model::getAnimationBegin(){
			return animBegin;
		}

		int Model::getAnimationEnd(){
			return animEnd;
		}

		bool Model::isTextureEnabled(){
			return enaTex;
		}

		void Model::useTexture(bool b){
			enaTex = b;
		}

		math::Vector3f Model::getPosition(){
			return pos;
		}

		math::Vector3f Model::getRotation(){
			return rot;
		}

		void Model::setPosition(math::Vector3f v){
			pos = v;
		}

		void Model::setRotation(math::Vector3f v){
			rot = v;
		}

	}; //gunit
}; //siege
