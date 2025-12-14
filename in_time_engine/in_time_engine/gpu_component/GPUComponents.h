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
			Camera3D() {

			}
			~Camera3D() = default;

			// Getters
			const std::type_info& getTypeInfo() const {
				return typeid(Camera3D);
			}

			// Events
	};
	class GPUPoint : public Component {
		// Object
		public:
			// Properties
			gl::Point point = gl::Point();

			// Getters
			const std::type_info& getTypeInfo() const override {
				return typeid(GPUPoint);
			}

			// Events
			void onAddToGameObject() {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject->getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr) {
					gpuTransform = new GPUTransform();
					gameObject->addComponent(gpuTransform);
				}

				point.gpuData.transformIndex = gpuTransform->glTransform.getIndex();
			}
	};
	class GPULine : public Component {
		// Object
		public:
			// Properties
			gl::Line line = gl::Line();

			// Getters
			const std::type_info& getTypeInfo() const override {
				return typeid(GPULine);
			}

			// Events
			void onAddToGameObject() override {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject->getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr) {
					gpuTransform = new GPUTransform();
					gameObject->addComponent(gpuTransform);
				}

				line.gpuData[0].transformIndex = gpuTransform->glTransform.getIndex();
				line.gpuData[1].transformIndex = gpuTransform->glTransform.getIndex();
			}
	};
	class GPUMultiLine : public Component {
		// Object
		public:
			// Properties
			gl::MultiLine multiLine = gl::MultiLine();

			// Getters
			const std::type_info& getTypeInfo() const override {
				return typeid(GPUMultiLine);
			}

			// Events
			void onAddToGameObject() override {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject->getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr) {
					gpuTransform = new GPUTransform();
					gameObject->addComponent(gpuTransform);
				}

				for (size_t i = 0ULL; i < multiLine.gpuData.size(); i++)
					multiLine.gpuData[i].transformIndex = gpuTransform->glTransform.getIndex();
			}
	};
	class GPUTriangle : public Component {
		// Object
		public:
			// Properties
			gl::Triangle triangle = gl::Triangle();

			// Getters
			const std::type_info& getTypeInfo() const override {
				return typeid(GPUTriangle);
			}

			// Events
			void onAddToGameObject() override {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject->getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr) {
					gpuTransform = new GPUTransform();
					gameObject->addComponent(gpuTransform);
				}

				triangle.gpuData[0].transformIndex = gpuTransform->glTransform.getIndex();
				triangle.gpuData[1].transformIndex = gpuTransform->glTransform.getIndex();
				triangle.gpuData[2].transformIndex = gpuTransform->glTransform.getIndex();
			}
	};
	class GPUTriangleStrip : public Component {
		// Object
		public:
			// Properties
			gl::TriangleStrip triangleStrip = gl::TriangleStrip();

			// Getters
			const std::type_info& getTypeInfo() const override {
				return typeid(GPUTriangleStrip);
			}

			void onAddToGameObject() override {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject->getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr) {
					gpuTransform = new GPUTransform();
					gameObject->addComponent(gpuTransform);
				}

				for (size_t i = 0ULL; i < triangleStrip.gpuData.size(); i++)
					triangleStrip.gpuData[i].transformIndex = gpuTransform->glTransform.getIndex();

			}
	};
	class GPUTriangleFan : public Component {
		// Object
		public:
			// Properties
			gl::TriangleFan triangleFan = gl::TriangleFan();

			// Getters
			const std::type_info& getTypeInfo() const override {
				return typeid(GPUTriangleFan);
			}

			// Events
			void onAddToGameObject() override {
				GPUTransform* gpuTransform = (GPUTransform*)gameObject->getComponent(typeid(GPUTransform));
				if (gpuTransform == nullptr) {
					gpuTransform = new GPUTransform();
					gameObject->addComponent(gpuTransform);
				}

				for (size_t i = 0ULL; i < triangleFan.gpuData.size(); i++)
					triangleFan.gpuData[i].transformIndex = gpuTransform->glTransform.getIndex();
			}
	};
}
