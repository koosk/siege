#include"gunit/MS3DModel.h"
#include"gunit/MS3DException.h"
#include<GL/gl.h>
#include<string>

namespace siege{
	namespace gunit{
		
		void MS3DModel::loadModel(char* f){
			model.load(f);
		}

		MS3DModel::MS3DModel():Model(){}

		MS3DModel::MS3DModel(char* f):Model(f){}

		MS3DModel::MS3DModel(MS3DModel& m):Model(m){
			model = m.model;
		}

		MS3DModel::~MS3DModel(){

		}

		void MS3DModel::reset(){
			//TODO az idot megcsinalni
		}

		void MS3DModel::setAnimationInterval(int from, int to){
			setAnimationBegin(from);
			setAnimationEnd(to);
			//TODO akt ido megcsinalasa
		}

		void MS3DModel::drawModel(){
			//TODO animacio
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

					if(mat->hasTexture() && glText){
						glBindTexture(GL_TEXTURE_2D, mat->getTexure());
						glEnable(GL_TEXTURE_2D);
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
							tri->getVertexNormal(k).get(tmp);
							glNormal3fv(tmp);

							glTexCoord2f(tri->getS()[k], tri->getT()[k]);

							(*model.getVertex(tri->getVertexIndex(k)))().get(tmp);
							glVertex3fv(tmp);
						}
						}catch(std::exception &e){std::cout << e.what() << std::endl;}
					}
				glEnd();
				
			}
			if(glText)
				glEnable(GL_TEXTURE_2D);
			else
				glDisable(GL_TEXTURE_2D);
		}

	}; //gunit
}; //siege
