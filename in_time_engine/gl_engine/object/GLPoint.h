#pragma once

// Dependencies | std
#include <list>
#include <filesystem>
#include <string>

// Dependencies | glm
#include <glm/glm.hpp>

namespace gl {
	class Point {
		// Friends
		friend class PointRenderer;

		// Data types
		public:
			struct GPUData {
				int transformIndex = -1;
				float size = 10.0f;
				glm::vec3 offset = glm::vec3(0.0f);
				glm::vec4 color = glm::vec4(1.0f);
			};

		// Object
		private:
			// Properties
			std::list<Point>::iterator pointNode{};

		public:
			// Properties
			GPUData gpuData{};
	};
}
