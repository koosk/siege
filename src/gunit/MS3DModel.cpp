#include"gunit/MS3DModel.h"
#include"gunit/MS3DException.h"
#include"math/MathException.h"
#include<GL/gl.h>
#include<SDL/SDL.h>
#include<string>

namespace siege{
	namespace gunit{

		void MS3DModel::initMatrices(word i = 0){
			if(absMatrices != NULL){
				delete[] absMatrices;
				delete[] relMatrices;
				delete[] finMatrices;
				absMatrices = NULL;
				relMatrices = NULL;
				finMatrices = NULL;
			}
			if(i == 0)
				return;
			absMatrices = new Matrix16f[i];
			relMatrices = new Matrix16f[i];
			finMatrices = new Matrix16f[i];
		}

		void MS3DModel::init(){
			absMatrices = NULL;
			relMatrices = NULL;
			finMatrices = NULL;
			initMatrices();
		}

		void MS3DModel::cpyMatrices(Matrix16f* trg, const Matrix16f* src, word num){
			for(int i=0; i<num; i++)
				trg[i] = src[i];
		}

		void MS3DModel::loadModel(char* f){
			model.load(f);
			setupMatrices();
			setupVertices();
		}

		MS3DModel::MS3DModel():Model(){
			init();	
		}

		MS3DModel::MS3DModel(char* f):Model(f){
			init();	
		}

		MS3DModel::MS3DModel(MS3DModel& m):Model(m){
			init();
			*this = m;
		}

		MS3DModel::~MS3DModel(){
			initMatrices();
		}

		MS3DModel& MS3DModel::operator=(MS3DModel& m){
			model = m.model;
			word num = model.getNumberOfJoints();
			initMatrices(num);
			cpyMatrices(absMatrices, m.absMatrices, num);
			cpyMatrices(relMatrices, m.relMatrices, num);
			cpyMatrices(finMatrices, m.finMatrices, num);
			return *this;
		}

		void MS3DModel::start(){
			Model::start();
			startTime = SDL_GetTicks();
		}

		void MS3DModel::reset(){
			currentTime = getAnimationBegin()/model.getFPS();
		}

		void MS3DModel::setAnimationInterval(int from, int to){
			Model::setAnimationInterval(from, to);
			currentTime = from/model.getFPS();
		}

		void MS3DModel::setupMatrices(){
			initMatrices(model.getNumberOfJoints());
			for(int i=0; i<model.getNumberOfJoints(); i++){
				MS3DJoint* joint = model.getJoint(i);	
				Matrix16f mat;
				mat = mat.translate(joint->getPositionVector());
				mat = mat.rotate(joint->getRotationVector());
				Vector3f v = joint->getPositionVector();
				if(joint->hasParent()){
					absMatrices[i] = absMatrices[joint->getParent()->getIndex()] * mat;
				}
				else{
					absMatrices[i] = mat;
				}
				relMatrices[i] = mat;
				finMatrices[i] = absMatrices[i];
			}
		}

		void MS3DModel::setupVertices(){
			for(int i=0; i<model.getNumberOfVertices(); i++){
				MS3DVertex *v = model.getVertex(i);
				if(v->hasBone()){
					Matrix16f m = absMatrices[(word)v->getBoneId()];
					try{
						m = m.invert();
					}catch(MathException &e){std::cout << e.what() << std::endl;}
					Vector3f vec = v->operator()();
					vec = vec * m;
					v->setVertex(vec);
				}
			}
		}

		Vector3f MS3DModel::getKeyFrameVector(MS3DKeyFrame* kf, word num, float time){
			word fi = 0;
			while(fi < num && kf[fi].getTime() < time)
				fi++;
			Vector3f v;
			if(fi == 0){
				v = kf[fi]();
				return v;
			}
			if(fi == num){
				v = kf[num-1]();
				return v;
			}
			v = kf[fi-1].interpolate(kf[fi], time);
			return v;
		}

		void MS3DModel::animate(){
			unsigned int sdltic = SDL_GetTicks();
			currentTime += ((sdltic - startTime) / 1000.0);// * model.getFPS()) / model.getFPS();
			startTime = sdltic;
			float end = (float)getAnimationEnd()/model.getFPS();
			if(currentTime > end)
				currentTime = (float)getAnimationBegin() + (currentTime - end);


			for(int i=0; i<model.getNumberOfJoints(); i++){
				MS3DJoint *j = model.getJoint(i);
				if(!j->hasRotationKeyFrames() && !j->hasTranslationKeyFrames()){
					finMatrices[i] = absMatrices[i];
					continue;
				}
				Matrix16f m;
				m = m.translate(getKeyFrameVector(j->getTranslationKeyFrames(), j->getNumberOfTranslationKeyFrames(), currentTime));
				m = m.rotate(getKeyFrameVector(j->getRotationKeyFrames(), j->getNumberOfRotationKeyFrames(), currentTime));

				m = m * relMatrices[i];

				if(j->hasParent())
					finMatrices[i] = m * finMatrices[j->getParent()->getIndex()];
				else
					finMatrices[i] = m;
			}
		}

		void MS3DModel::drawModel(){
			bool glText = glIsEnabled(GL_TEXTURE_2D);
			for(int gi=0; gi<model.getNumberOfGroups(); gi++){
				char mindex = model.getGroup(gi)->getMaterialIndex();
				if(mindex >= 0){
					MS3DMaterial* mat = model.getMaterial(mindex);
					float tmp[4];
					mat->getAmbient().get(tmp);
					glMaterialfv(GL_FRONT, GL_AMBIENT, tmp);
					mat->getDiffuse().get(tmp);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, tmp);
					mat->getSpecular().get(tmp);
					glMaterialfv(GL_FRONT, GL_SPECULAR, tmp);
					mat->getEmissive().get(tmp);
					glMaterialfv(GL_FRONT, GL_EMISSION, tmp);
					float shi = mat->getShininess();
					glMaterialfv(GL_FRONT, GL_SHININESS, &shi);
					
					//a fenyek jobb megjelenitesehez
					//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

					//TODO alpha

					if(mat->hasTexture() && isTextureEnabled()){
						//glActiveTexture(GL_TEXTURE0);
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, mat->getTexure());
						/*glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_REPLACE);
						glActiveTexture(GL_TEXTURE1);
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, mat->getAlphamap());

						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
						glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_INTERPOLATE);

						glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE0_ALPHA, GL_TEXTURE0);
						glTexEnvi(GL_TEXTURE_ENV,GL_OPERAND0_ALPHA,GL_SRC_COLOR); 

						glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE1_ALPHA,GL_TEXTURE2);
						glTexEnvi(GL_TEXTURE_ENV,GL_OPERAND1_ALPHA,GL_SRC_COLOR); */
					}else{
						glDisable(GL_TEXTURE_2D);
					}

				}else
					glDisable(GL_TEXTURE_2D);

				glBegin(GL_TRIANGLES);
					MS3DGroup* group = model.getGroup(gi);
					for(int i=0; i<group->getNumberOfTriangles(); i++){
						try{
						MS3DTriangle* tri = model.getTriangle(group->operator[](i));
						float tmp[3];
						for(int k=0; k<3; k++){
							glTexCoord2f(tri->getS()[k], tri->getT()[k]);

							MS3DVertex *ver = model.getVertex(tri->getVertexIndex(k));
							Matrix16f m;
							bool b = false;
							if(ver->hasBone()){
								m = finMatrices[(word)ver->getBoneId()];
								b = true;
							}
							Vector3f v = ver->operator()();
							if(b)
								v = v*m;
							v.get(tmp);

							glVertex3fv(tmp);

							v = tri->getVertexNormal(k);
							if(b)
								v = v*m;
							v.get(tmp);
							glNormal3fv(tmp);

						}
						}catch(std::exception &e){std::cout << e.what() << std::endl;}
					}
				glEnd();
				
			}
			if(glText)
				glEnable(GL_TEXTURE_2D);
			else
				glDisable(GL_TEXTURE_2D);

			if(isAnimationOn())
				animate();
		}

		int MS3DModel::getMaxFrames(){
			return model.getTotalFrames();
		}

		void MS3DModel::drawSkeleton(){
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			Vector3f pos = getPosition();
			Vector3f rot = getRotation();
			glTranslatef(pos[0], pos[1], pos[2]);
			glRotatef(rot[0], 1, 0, 0);
			glRotatef(rot[1], 0, 1, 0);
			glRotatef(rot[2], 0, 0, 1);
			bool glDepth = glIsEnabled(GL_DEPTH_TEST);
			bool glLight = glIsEnabled(GL_LIGHTING);
			bool glText = glIsEnabled(GL_TEXTURE_2D);
			if(glDepth)
				glDisable(GL_DEPTH_TEST);
			if(glLight)
				glDisable(GL_LIGHTING);
			if(glText)
				glDisable(GL_TEXTURE_2D);
			glPointSize(6.0);
			glLineWidth(2.0);
			for(int i=0; i<model.getNumberOfJoints(); i++){
				MS3DJoint* joint = model.getJoint(i);
				glColor3f(1,1,0);
				glBegin(GL_POINTS);
					Matrix16f m2;
					Vector3f v2(1,1,1);
					m2 = finMatrices[i];
					v2 = v2*m2;
					float f2[3];
					v2.get(f2);
					glVertex3fv(f2);
				glEnd();
				if(!joint->hasParent())
					continue;
				glColor3f(0,1,0);
				glBegin(GL_LINES);
					Vector3f pv(1,1,1);
					Matrix16f m;
					m = finMatrices[joint->getParent()->getIndex()];
					pv = pv*m;
					m = Matrix16f();
					Vector3f v(1,1,1);
					m = finMatrices[i];
					v = v*m;
					float f[3];
					pv.get(f);
					glVertex3fv(f);
					v.get(f);
					glVertex3fv(f);
				glEnd();
				glColor3f(1,1,1);
			}
			glLineWidth(1.0f);
			glPointSize(1.0f);

			if(glDepth)
				glEnable(GL_DEPTH_TEST);
			if(glLight)
				glEnable(GL_LIGHTING);
			if(glText)
				glEnable(GL_TEXTURE_2D);

			if(isAnimationOn())
				animate();

			glPopMatrix();
		}

	}; //gunit
}; //siege
