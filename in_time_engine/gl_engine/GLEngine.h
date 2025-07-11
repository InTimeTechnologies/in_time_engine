#pragma once

// Dependencies | std
#include <string>
#include <chrono>

// Dependencies | glew
#include <glew/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

// Dependencies | OpenGLEngine
#include "GLTime.h"
#include "GLBuffer.h"
#include "GLShader.h"
#include "GLProgram.h"
#include "GLProgramPipeline.h"
#include "GLTransform.h"
#include "GLCamera.h"
#include "GLCamera2D.h"
#include "GLCamera3D.h"
#include "object/GLPoint.h"
#include "object/GLLine.h"
#include "object/GLMultiLine.h"
#include "object/GLTriangle.h"
#include "object/GLTriangleStrip.h"
#include "object/GLTriangleFan.h"

#if defined(_DEBUG)
#include "GLDebug.h"
#endif

namespace gl {
	class GLEngine {
		// Friends
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static GLEngine* s_singleton;
	
		public:
			// Function
			static GLEngine* s_getSingleton();
	
		// Object
		public:
			// Properties
			std::filesystem::path rootPathToShaders = std::filesystem::path();
			std::string openGLVersion = "";
			Time time = Time();

			// Constructor / Destructor
			GLEngine(const std::filesystem::path& rootPathToShaders);
			~GLEngine();
	
			// Functions
			void render();
			void render(Camera* camera);
			void swapBuffers();
	};	
}
