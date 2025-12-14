#pragma once

// Dependencies | std
#include <string>
#include <chrono>
#include <filesystem>

// Dependencies | gl_engine
#include "GLDebug.h"
#include "GLHeader.h"
#include "GLTime.h"
#include "GLBuffer.h"
#include "GLShader.h"
#include "GLProgram.h"
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
#include "object/GLRenderableSprite.h"

namespace gl {
	class Engine {
		// Friends
		friend class InTimeEngine;

		// Structs
		struct ShaderPaths {
			std::string point{ "point" };
			std::string line{ "line" };
			std::string multiline{ "multiline" };
			std::string triangle{ "triangle" };
			std::string triangleStrip{ "triangle_strip" };
			std::string triangleFan{ "triangle_fan" };
			std::string renderableSprite{ "renderable_sprite" };
		};

		// Static
		private:
			// Properties
			static Engine* s_singleton;
	
		public:
			// Function
			static Engine* s_getSingleton();
				
		// Object
		public:
			// Properties
			Debug debug{};
			std::filesystem::path rootPathToShaders{ std::filesystem::current_path() / "shader_src" };
			std::string openGLVersion{};
			Time time{};
			ShaderPaths shaderPaths{};

			// Constructor / Destructor
			Engine();
			~Engine();

			// Functions | render
			void render();
			void render(Camera* camera);
			void swapBuffers();
	};	
}
