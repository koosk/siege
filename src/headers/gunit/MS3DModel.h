#ifndef MS3D_MODEL_H
#define MS3D_MODEL_H

#include"Model.h"
#include"MS3DData.h"

namespace siege{
	namespace gunit{

		class MS3DModel : public Model{
			private:
				MS3DData model;
			protected:
				void loadModel(char*);
				void drawModel();
			public:
				MS3DModel();
				MS3DModel(char*);
				MS3DModel(MS3DModel&);
				~MS3DModel();
				void reset();
				void setAnimationInterval(int, int);
		}; //MS3DModel

	}; //gunit
}; //siege

#endif //MS3D_MODEL_H
