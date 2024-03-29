#ifndef MODEL_H
#define MODEL_H

#include"math/Vector3.h"

namespace siege{
	namespace gunit{

		class Model{
			private:
				int animBegin;
				int animEnd;
				char* modelPath;
				bool animOn;
				bool enaTex;
				math::Vector3 pos;
				math::Vector3 rot;
			protected:
				virtual void loadModel(char*) = 0;
				virtual void drawModel() = 0;
				bool isAnimationOn();
				virtual void setAnimationBegin(int);
				virtual void setAnimationEnd(int);
				void setModelPath(char*);
			public:
				Model();
				Model(char*);
				Model(Model&);
				~Model();
				Model& operator=(Model&);
				void load();
				void load(char*);
				virtual void start();
				virtual void pause();
				virtual void stop();
				virtual void reset() = 0;
				virtual void setAnimationInterval(int, int);
				int getAnimationBegin();
				int getAnimationEnd();
				virtual int getMaxFrames() = 0;
				void draw();
				bool isTextureEnabled();
				void useTexture(bool);
				math::Vector3 getPosition();
				math::Vector3 getRotation();
				void setPosition(math::Vector3);
				void setRotation(math::Vector3);
		}; //Model

	}; //gunit
}; //siege

#endif //MODEL_H
