#include"gunit/Model.h"
#include"SiegeException.h"
#include<string.h>


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
		}

		Model::Model(char* f){
			animBegin = 0;
			animEnd = 0;
			animOn = false;
			modelPath = NULL;
			setModelPath(f);
		}

		Model::Model(Model& m){
			animBegin = m.animBegin;
			animEnd = m.animEnd;
			animOn = m.animOn;
			modelPath = NULL;
			setModelPath(m.modelPath);
		}

		Model::~Model(){
			if(modelPath != NULL)
				delete[] modelPath;
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
			if(strcmp(modelPath, f) != 0)
				setModelPath(f);
			loadModel(f);
		}	

		void Model::start(){
			if(animBegin != animEnd)
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
			//TODO gl_push, glTranslate
			drawModel();
			//TODO gl_pop
		}

		int Model::getAnimationBegin(){
			return animBegin;
		}

		int Model::getAnimationEnd(){
			return animEnd;
		}

	}; //gunit
}; //siege
