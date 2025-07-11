#pragma once

// Dependencies | std
#include <vector>

// Dependencies | glew
#include <glew/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

// Dependencies | OpenGLEngine
#include "GLProgram.h"
#include "GLShaderType.h"

namespace gl {
	class ProgramPipeline {
		// Object
		private:
			// Properties
			unsigned int id = 0U;

		public:
			// Constructor / Destructor
			ProgramPipeline();
			~ProgramPipeline();

			// Getters
			unsigned int getId() const;

			// Functions
			void useProgramStages(unsigned int shaderType, unsigned int glslProgramId) const;
			void useProgramStages(ShaderType shaderType, const Program& glslProgram) const;
			void bind() const;
	};
}