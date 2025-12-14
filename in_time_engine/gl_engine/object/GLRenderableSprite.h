#pragma once

// Dependencies | std
#include <memory>

// Dependencies | gl_engine
#include "../GLHeader.h"
#include "../GLTexture.h"
#include "../GLBuffer.h"
#include "../GLProgram.h"

namespace gl {
	class RenderableSprite {
		// Friends
		friend class Engine;

		// structs
		public:
			struct GPUData {
				int transformIndex{ -1 };
				glm::vec3 position = glm::vec3{ 0.0f };
				glm::vec4 colorTint = glm::vec4{ 1.0f };
				int textureSlot{ -1 };
				bool flipX{ false };
				bool flipY{ false };
			};

		// Object
		public:
			// Properties
			std::weak_ptr<texture::Texture2D> textureWeakPointer{};
			GPUData gpuData{};
	};
}