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
						//m = m.normalize();
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
			//TODO idozites
			currentTime += ((sdltic - startTime) / 20000.0) * (model.getTotalFrames()/model.getFPS());
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
			bool glBlend = glIsEnabled(GL_BLEND);
			bool glDepth = glIsEnabled(GL_DEPTH_TEST);
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

					//TODO alpha
					/*if(mat->hasAlphamap() && glBlend){
						glEnable(GL_BLEND);
						glDisable(GL_DEPTH_TEST);
						glEnable(GL_TEXTURE_2D);
						glBlendFunc(GL_DST_COLOR, GL_ZERO);
						glBindTexture(GL_TEXTURE_2D, mat->getAlphamap());
					}else{
						glDisable(GL_BLEND);
						glDisable(GL_TEXTURE_2D);
					}*/

					if(mat->hasTexture() && glText){
						//glBlendFunc(GL_ONE, GL_ONE);
						//glDisable(GL_BLEND);
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, mat->getTexure());
					}else
						glDisable(GL_TEXTURE_2D);

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
			if(glBlend)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);
			if(glDepth)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);

			if(isAnimationOn())
				animate();
		}

		int MS3DModel::getMaxFrames(){
			return model.getTotalFrames();
		}

		void MS3DModel::drawSkeleton(){
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
					Vector3f v2 = joint->getPositionVector();
					m2 = m2.rotate(joint->getRotationVector());
					v2 = v2*m2;
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
					Vector3f pv = joint->getParent()->getPositionVector();
					Matrix16f m;
					m = m.rotate(joint->getParent()->getRotationVector());
					pv = pv*m;
					m = finMatrices[joint->getParent()->getIndex()];
					pv = pv*m;
					m = Matrix16f();
					Vector3f v = joint->getPositionVector();
					m = m.rotate(joint->getRotationVector());
					v = v*m;
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
		}

	}; //gunit
}; //siege
