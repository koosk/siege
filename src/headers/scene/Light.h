#include "GL/gl.h"
#include <iostream>
#include "math/Vector4.h"
using namespace siege::math;

namespace siege{
	namespace scene{
		class Light{
			private:
				int index;
				Vector4 position;
				Vector4 ambient;
				Vector4 diffuse;
				Vector4 specular;
				Vector3 spotDirection;
				float spotCutoff;
				float spotExponent;
				float linearAttenuation;
				float quadraticAttenuation;
				float constantAttenuation;
			public:
				friend std::ostream& operator<<(std::ostream&, const Light &);

				Light(int index, const Vector4 &position = Vector4(0.,0.,1.,0.));
				Light(const Light&);
				~Light();
				inline int getIndex() const;
				inline const Vector4& getPosition() const;
				inline const Vector4& getAmbient() const;
				inline const Vector4& getDiffuse() const;
				inline const Vector4& getSpecular() const;
				inline const Vector3& getSpotDirection() const;
				inline float getSpotCutoff() const;
				inline float getSpotExponent() const;
				inline float getLinearAttenuation() const;
				inline float getQuadraticAttenuation() const; 
				inline float getConstantAttenuation() const;
				inline void setIndex(const int);
				inline void setPosition(const Vector4 &);
				inline void setAmbient(const Vector4 &);
				inline void setDiffuse(const Vector4 &);
				inline void setSpecular(const Vector4 &);
				inline void setSpotDirection(const Vector3 &);
				inline void setSpotCutoff(const float);
				inline void setSpotExponent(const float);
				inline void setLinearAttenuation(const float);
				inline void setQuadraticAttenuation(const float);
				inline void setConstantAttenuation(const float);
				void render() const;
				inline void enable() const;
				inline void disable() const;
				inline static void enableLighting();
				inline static void disableLighting();
		};//class Light

		int Light::getIndex() const{
			return index;
		}

		const Vector4& Light::getPosition() const{
			return position;
		}

		const Vector4& Light::getAmbient() const{
			return ambient;
		}

		const Vector4& Light::getDiffuse() const{
			return diffuse;
		}

		const Vector4& Light::getSpecular() const{
			return specular;
		}
		
		const Vector3& Light::getSpotDirection() const{
			return spotDirection;
		}
		
		float Light::getSpotCutoff() const{
			return spotCutoff;
		}

		float Light::getSpotExponent() const{
			return spotExponent;
		}

		float Light::getLinearAttenuation() const{
			return linearAttenuation;
		}

		float Light::getQuadraticAttenuation() const{
			return quadraticAttenuation;
		}

		float Light::getConstantAttenuation() const{
			return constantAttenuation;
		}
		
		void Light::setIndex(const int index){
			this->index = index;
		}
		
		void Light::setPosition(const Vector4 &position){
			this->position = position;
		}

		void Light::setAmbient(const Vector4 &ambient){
			this->ambient = ambient;
		}

		void Light::setDiffuse(const Vector4 &diffuse){
			this->diffuse = diffuse;
		}

		void Light::setSpecular(const Vector4 &specular){
			this->specular = specular;
		}
		
		void Light::setSpotDirection(const Vector3 &spotDir){
			this->spotDirection = spotDir;
		}
		
		void Light::setSpotCutoff(const float spotCutoff){
			this->spotCutoff = spotCutoff;
		}

		void Light::setSpotExponent(const float spotExponent){
			this->spotExponent = spotExponent;
		}

		void Light::setLinearAttenuation(const float linearAttenuation){
			this->linearAttenuation = linearAttenuation;
		}

		void Light::setQuadraticAttenuation(const float quadraticAttenuation){
			this->quadraticAttenuation = quadraticAttenuation;
		}

		void Light::setConstantAttenuation(const float constantAttenuation){
			this->constantAttenuation = constantAttenuation;
		}

		void Light::enable() const{
			glEnable(GL_LIGHT0+index);
		}

		void Light::disable() const{
			glDisable(GL_LIGHT0+index);
		}

		void Light::enableLighting(){
			glEnable(GL_LIGHTING);
		}

		void Light::disableLighting(){
			glDisable(GL_LIGHTING);
		}

	};//namespace scene
};//namespace siege
