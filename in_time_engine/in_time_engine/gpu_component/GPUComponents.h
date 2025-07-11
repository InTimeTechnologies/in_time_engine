#pragma once

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | gl_engine
#include <gl_engine/GLTransform.h>
#include <gl_engine/object/GLPoint.h>
#include <gl_engine/object/GLLine.h>
#include <gl_engine/object/GLMultiLine.h>
#include <gl_engine/object/GLTriangle.h>
#include <gl_engine/object/GLTriangleStrip.h>
#include <gl_engine/object/GLTriangleFan.h>

// Dependencies | in_time_engine
#include "../GameObject.h"
#include "../Component.h"
#include "../gpu_component/GPUTransform.h"

// Dependencies | std
#include <list>

namespace it {
	class Camera3D : public Component {
		// Object
		public:
			// Properties
			gl::Camera3D camera3D;

			// Constructor / Destructor
			Camera3D(GameObject& gameObject) : Component(gameObject, typeid(Camera3D)) {

			}
			~Camera3D() = default;
	};
	class GPUPoint : public Component {
		// Object
		public:
			// Properties
			gl::Point point = gl::Point();

			// Constructor / Destructor
			GPUPoint(GameObject& gameObject) : Component(gameObject, typeid(GPUPoint)) {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject.getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr)
					gpuTransform = new GPUTransform(gameObject);

				point.gpuData.transformIndex = gpuTransform->glTransform.getIndex();
			}
			~GPUPoint() = default;
	};
	class GPULine : public Component {
		// Object
		public:
			// Properties
			gl::Line line = gl::Line();

			// Constructor / Destructor
			GPULine(GameObject& gameObject) : Component(gameObject, typeid(GPULine)) {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject.getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr)
					gpuTransform = new GPUTransform(gameObject);

				line.gpuData[0].transformIndex = gpuTransform->glTransform.getIndex();
				line.gpuData[1].transformIndex = gpuTransform->glTransform.getIndex();
			}
			~GPULine() = default;
	};
	class GPUMultiLine : public Component {
		// Object
		public:
			// Properties
			gl::MultiLine multiLine = gl::MultiLine();

			// Constructor / Destructor
			GPUMultiLine(GameObject& gameObject) : Component(gameObject, typeid(GPUMultiLine)) {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject.getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr)
					gpuTransform = new GPUTransform(gameObject);
				
				for (size_t i = 0ULL; i < multiLine.gpuData.size(); i++)
					multiLine.gpuData[i].transformIndex = gpuTransform->glTransform.getIndex();
			}
			~GPUMultiLine() = default;
	};
	class GPUTriangle : public Component {
		// Object
		public:
			// Properties
			gl::Triangle triangle = gl::Triangle();

			// Constructor / Destructor
			GPUTriangle(GameObject& gameObject) : Component(gameObject, typeid(GPUTriangle)) {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject.getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr)
					gpuTransform = new GPUTransform(gameObject);

				triangle.gpuData[0].transformIndex = gpuTransform->glTransform.getIndex();
				triangle.gpuData[1].transformIndex = gpuTransform->glTransform.getIndex();
				triangle.gpuData[2].transformIndex = gpuTransform->glTransform.getIndex();
			}
			~GPUTriangle() = default;
	};
	class GPUTriangleStrip : public Component {
		// Object
		public:
			// Properties
			gl::TriangleStrip triangleStrip = gl::TriangleStrip();

			// Constructor / Destructor
			GPUTriangleStrip(GameObject& gameObject) : Component(gameObject, typeid(GPUTriangleStrip)) {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject.getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr)
					gpuTransform = new GPUTransform(gameObject);

				for (size_t i = 0ULL; i < triangleStrip.gpuData.size(); i++)
					triangleStrip.gpuData[i].transformIndex = gpuTransform->glTransform.getIndex();
			}
			~GPUTriangleStrip() = default;
	};
	class GPUTriangleFan : public Component {
		// Object
		public:
			// Properties
			gl::TriangleFan triangleFan = gl::TriangleFan();

			// Constructor / Destructor
			GPUTriangleFan(GameObject& gameObject) : Component(gameObject, typeid(GPUTriangleFan)) {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject.getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr)
					gpuTransform = new GPUTransform(gameObject);

				for (size_t i = 0ULL; i < triangleFan.gpuData.size(); i++)
					triangleFan.gpuData[i].transformIndex = gpuTransform->glTransform.getIndex();
			}
			~GPUTriangleFan() = default;
	};
}
