#include "scene/Light.h"
namespace siege{
	namespace scene{

		//defaul values according to http://pyopengl.sourceforge.net/documentation/manual/glLight.3G.html
		Light::Light(int index, const Vector4 &position):index(index),position(position),
			ambient(Vector4(0.,0.,0.,1.)),spotDirection(Vector3(0.,0.,-1.)),
			spotCutoff(180.),spotExponent(0.),linearAttenuation(1.),
			quadraticAttenuation(0.),constantAttenuation(0.)
		{
			if(index==0){
				diffuse = specular = Vector4(1.,1.,1.,1.);
			}
		}

		Light::Light(const Light &l){
			index = l.index;
			position = l.position;
			ambient  = l.ambient;
			diffuse  = l.diffuse;
			specular = l.specular;
			spotDirection  = l.spotDirection;
			spotCutoff = l.spotCutoff;
			spotExponent = l.spotExponent;
			linearAttenuation = l.linearAttenuation;
			quadraticAttenuation = l.quadraticAttenuation;
			constantAttenuation = l.constantAttenuation;
		}

		Light::~Light(){
		}

		void Light::render() const{
			float *f = new float[4];
			glLightfv(GL_LIGHT0+index, GL_POSITION, position.get(f));
			glLightfv(GL_LIGHT0+index, GL_AMBIENT , ambient.get(f));
			glLightfv(GL_LIGHT0+index, GL_DIFFUSE , diffuse.get(f));
			glLightfv(GL_LIGHT0+index, GL_SPECULAR, specular.get(f));
			glLightfv(GL_LIGHT0+index, GL_SPOT_DIRECTION, spotDirection.get(f));
			glLightf(GL_LIGHT0+index, GL_SPOT_CUTOFF, spotCutoff);

			delete[] f;
		}

		std::ostream& operator<<(std::ostream &out, const Light &l){
			out << "Light{index=" << l.index << ", position=" << l.position;
			out << ", ambient=" << l.ambient << ", diffuse=" << l.diffuse;
			out << ", specular=" << l.specular << ", spotDirection=" << l.spotDirection;
			out << ", spotCutoff=" << l.spotCutoff << ", spotExponent=" << l.spotExponent;
			out << ", linearAttenuation=" << l.linearAttenuation;
			out << ", quadraticAttenuation=" << l.quadraticAttenuation;
			out << ", constantAttenuation=" << l.constantAttenuation << "}";
			return out;
		}
	};
};
