#include"scene/BoundingBox.h"
#include"BadIndexException.h"

namespace siege{
	namespace scene{
		
		BoundingBox::BoundingBox(){}

		BoundingBox::BoundingBox(math::Vector3 v1, math::Vector3 v2){
			position[0] = v1;
			position[1] = v2;
		}

		math::Vector3& BoundingBox::operator[](int i){
			if(i<0 || i>1)
				throw BadIndexException("Bad index while getting BoundingBox's Vector3!");
			return position[i];
		}

		bool BoundingBox::isInside(math::Vector3 v) const{
			if(position[0] > position[1]){
				if(v <= position[0] && v >= position[1])
					return true;
			}else if(position[0] < position[1]){
				if(v <= position[1] && v >= position[0])
					return true;
			}else if(v == position[0])
				return true;
			return false;
		}

		void BoundingBox::draw() const{
			//TODO
		}

	}; //scene
}; //siege
