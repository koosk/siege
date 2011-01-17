#ifndef MODEL_H
#define MODEL_H

namespace siege{
	namespace gunit{

		class Model{
			private:
				//TODO posintin matrix
				int animBegin;
				int animEnd;
				char* modelPath;
				bool animOn;
			protected:
				virtual void loadModel(char*) = 0;
				virtual void drawModel() = 0;
				bool isAnimationOn();
				virtual void setAnimationBegin(int);
				virtual void setAnimationEnd(int);
			public:
				Model();
				Model(char*);
				Model(Model&);
				~Model();
				void load(char*);
				virtual void start();
				virtual void pause();
				virtual void stop();
				virtual void reset() = 0;
				virtual void setAnimationInterval(int, int);
				int getAnimationBegin();
				int getAnimationEnd();
				void draw();
		}; //Model

	}; //gunit
}; //siege

#endif //MODEL_H