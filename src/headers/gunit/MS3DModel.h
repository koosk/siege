#ifndef MS3D_MODEL_H
#define MS3D_MODEL_H

#include"Model.h"
#include"MS3DData.h"
#include"math/Matrix16f.h"

namespace siege{
	namespace gunit{

		class MS3DModel : public Model{
			private:
				float currentTime;
				unsigned int startTime;
				MS3DData model;
				Matrix16f* absMatrices;
				Matrix16f* relMatrices;
				Matrix16f* finMatrices;
				void init();
				Vector3f& getKeyFrameVector(MS3DKeyFrame*, word, float);
			protected:
				void loadModel(char*);
				void drawModel();
				virtual void setupMatrices();
				virtual void setupVertices();
				virtual void initMatrices(word);
				virtual void cpyMatrices(Matrix16f*, const Matrix16f*, word);
				virtual void animate();
			public:
				MS3DModel();
				MS3DModel(char*);
				MS3DModel(MS3DModel&);
				~MS3DModel();
				MS3DModel& operator=(MS3DModel&);
				void reset();
				void setAnimationInterval(int, int);
				void start();
				int getMaxFrames();
		}; //MS3DModel

	}; //gunit
}; //siege

#endif //MS3D_MODEL_H
