#pragma once

// Dependencies | std
#include <list>
#include <limits>

// Dependencies | utility
#include <utility/IdFactory.h>
#include <utility/BinaryRangeTree.h>

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | gl_engine
#include "GLHeader.h"

// Dependencies | OpenGLRenderer
#include "GLBuffer.h"

namespace gl {
	//class TransformSystem {
	//	// Object
	//	private:
	//		// Properties
	//		size_t transformCapacity{ 60000ULL };
	//		Buffer* transformBuffer{ nullptr };
	//		BinaryRangeTree<int> idTracker{ Range<int>{ 0, std::numeric_limits<int>::max() } };

	//	public:
	//		// Constructor / Destructor
	//		TransformSystem() = default;
	//		~TransformSystem() = default;
	//};
	class Transform {
		// Friends
		friend class Engine;

		// Static
		private:
			// Properties
			static int s_initialTransformCapacity;
			static int s_transformCapacity;
			static Buffer* s_transformBuffer;
			static BinaryRangeTree<int> s_idTracker;

			// Functions
			static void s_init();
			static void s_deinit();

		// Object
		private:
			// Properties
			int transformIndex = -1;

		public:
			// Constructor / Destructor
			Transform();
			Transform(const glm::mat4& tranform);
			Transform(const Transform& glslTransform) = delete;
			Transform(const Transform&& glslTransform) = delete;
			~Transform();
			
			// Assignment operators
			Transform& operator=(const Transform& glslTransform) = delete;
			Transform& operator=(Transform&& glslTransform) = delete;

			// Getters
			int getIndex() const;

			// Functions
			void setTransform(const glm::mat4& transformMatrix);
	};
}
