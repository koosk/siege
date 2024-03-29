#ifndef CAMERA_H
#define CAMERA_H

#include "math/Vector3.h"

namespace siege{
  namespace scene{
	using namespace siege::math;

	class Camera{
		private:
			Vector3 pos;
			Vector3 lookAt;
			Vector3 up;
			float movementIntensity;
			float rotationIntensity;
		public:
			static const float defaultMovementIntensity = 1.0;
			static const float defaultRotationIntensity = 0.005;
			static const int MOVE_FORWARD  = 0;
			static const int MOVE_BACKWARD = 1;
			static const int MOVE_RIGHT    = 2;
			static const int MOVE_LEFT     = 3;
			static const int MOVE_UP       = 4;
			static const int MOVE_DOWN     = 5;
			static const int ROTATE_RIGHT  = 0;
			static const int ROTATE_LEFT   = 1;
			static const int ROTATE_UP     = 2;
			static const int ROTATE_DOWN   = 3;
			static const int LEAN_LEFT     = 4;
			static const int LEAN_RIGHT    = 5;

			Camera();
			Camera(const Vector3, const Vector3, const Vector3);
			Camera(const float, const float, const float,
			       const float, const float, const float,
			       const float, const float, const float);
			~Camera();
			void render() const;
			void setMovementIntensity(const float);
			void setRotationIntensity(const float);
			float getMovementIntensity() const;
			float getRotationIntensity() const; 
			void rotate(const int direction);
			void move(const int direction);
			const Vector3& getPosition() const;
			const Vector3& getUp() const;
			const Vector3& getLookAt() const;
			void setPosition(const Vector3 &);
			void setUp(const Vector3 &);
			void setLookAt(const Vector3 &);

	};//class Camera
  };//namespace scene
};//namespace siege
#endif
