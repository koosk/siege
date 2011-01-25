#ifndef MS3D_MODEL_H
#define MS3D_MODEL_H

#include"Model.h"
#include"MS3DData.h"
#include"math/Matrix4.h"

namespace siege{
	namespace gunit{

		class MS3DModel : public Model{
			private:
				float currentTime;
				unsigned int startTime;
				MS3DData model;
				Matrix4* absMatrices;
				Matrix4* relMatrices;
				Matrix4* finMatrices;
				void init();
				Vector3 getKeyFrameVector(MS3DKeyFrame*, word, float);
			protected:
				void loadModel(char*);
				void drawModel();
				virtual void setupMatrices();
				virtual void setupVertices();
				virtual void initMatrices(word);
				virtual void cpyMatrices(Matrix4*, const Matrix4*, word);
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
				void drawSkeleton();
		}; //MS3DModel

	}; //gunit
}; //siege

#endif //MS3D_MODEL_H
