#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include"math/Vector3.h"

namespace siege{
	namespace scene{

	class BoundingBox{
		private:
			math::Vector3 position[2];
		public:
			BoundingBox();
			BoundingBox(math::Vector3, math::Vector3);
			math::Vector3& operator[](int);
			bool isInside(math::Vector3) const;
			void draw() const;
	}; //BoundingBox

	}; //scene
}; //siege

#endif //BOUNDING_BOX_H
