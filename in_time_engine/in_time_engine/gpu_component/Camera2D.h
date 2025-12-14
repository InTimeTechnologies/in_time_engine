#pragma once

// Dependencies | in_time_engine
#include "../Component.h"
#include "../GameObject.h"

// Dependencies | gl_engine
#include <gl_engine/GLCamera2D.h>

namespace it {
	class Camera2D : public Component {
		// Friends
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static std::list<Camera2D*> s_camera2DList;

			// Functions
			static void s_updateTransforms();

		// Object
		private:
			// Properties
			std::list<Camera2D*>::iterator node;

		public:
			// Properties
			gl::Camera2D camera2D;

			// Constructor / Destructor
			Camera2D();
			~Camera2D();

			// Getters
			const std::type_info& getTypeInfo() const override;
	};
}
