#pragma once

// Dependencies | std
#include <list>
#include <filesystem>
#include <string>

// Dependencies | glew
#include <glew/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | opengl_engine
#include "../GLBuffer.h"
#include "../GLShader.h"
#include "../GLProgram.h"

namespace gl {
	class Point {
		// Friends
		friend class GLEngine;

		// Data types
		public:
			struct GPUData {
				int transformIndex = -1;
				float size = 10.0f;
				glm::vec3 offset = glm::vec3(0.0f);
				glm::vec4 color = glm::vec4(1.0f);
			};

		// Static
		private:
			// Properties
			static unsigned int s_vertexArrayObject;
			static Program* s_program;
			static std::list<Point*> s_pointList;
			static std::string s_vertexShaderFileName;
			static std::string s_fragmentShaderFileName;

			// Functions
			static bool s_init(const std::filesystem::path& pathToShaders);
			static void s_deinit();
			static void s_render(Buffer* transformBuffer, glm::mat4* viewProjectionMatrix);

		// Object
		protected:
			// Properties
			std::list<Point*>::iterator pointNode;
			Buffer buffer = Buffer(BufferType::VERTEX_BUFFER, BufferUsage::STREAM_DRAW, sizeof(gpuData), nullptr);

		public:
			// Properties
			GPUData gpuData;

			// Constructor / Destructor
			Point();
			~Point();
	};
}
