#pragma once

// Dependencies | std
#include <list>
#include <filesystem>

// Dependencies | OpenGL
#include <glew/glew.h>

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | OpenGLEngine
#include "../GLBuffer.h"
#include "../GLShader.h"
#include "../GLProgram.h"
#include "../GLTransform.h"

namespace gl {
	class Line {
		// Friends OpenGLEngine
		friend class GLEngine;

		// Data types
		public:
			struct GPUData {
				int transformIndex = -1;
				glm::vec3 position = glm::vec3(0.0f);
				glm::vec3 offset = glm::vec3(0.0f);
				glm::vec4 color = glm::vec4(1.0f);
			};

		// Static
		private:
			// Properties
			static unsigned int s_vertexArrayObject;
			static Program* s_program;
			static std::list<Line*> s_lineList;
			static std::string s_vertexShaderFileName;
			static std::string s_fragmentShaderFileName;
			
			// Functions
			static bool s_init(const std::filesystem::path& parentPathToShaders);
			static void s_deinit();
			static void s_render(Buffer* transformBuffer, glm::mat4* viewProjectionMatrix);

		// Object
		public:
			// Properties
			std::list<Line*>::iterator lineNode;
			GPUData gpuData[2];
			float width = 10.0f;
			Buffer buffer = Buffer(BufferType::VERTEX_BUFFER, BufferUsage::STREAM_DRAW, sizeof(gpuData), nullptr);
			
			// Constructor / Destructor
			Line();
			~Line();
	};
}
