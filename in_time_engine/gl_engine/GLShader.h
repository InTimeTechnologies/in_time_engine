#pragma once

// Dependencies | std
#include <string>
#include <filesystem>

// Dependencies | glew
#include <glew/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

// Dependencies | OpenGLEngine
#include "GLShaderType.h"

namespace gl {
	class Shader {
		// Static
		private:
			// Properties
			static ShaderType defaultShaderType;

			// Getters
			static ShaderType getDefaultShaderType();

			// Setters
			static void setDefaultShaderType(ShaderType shaderType);
			
		public:
			// Functions
			static bool validateShaderType(ShaderType shaderType);
			static ShaderType fileExtensionToShaderType(const std::string& fileExtension);
			static ShaderType pathToShaderType(const std::filesystem::path& path);
		
		// Object
		private:
			// Properties
			unsigned int id = 0ULL;

		public:
			// Properties
			ShaderType shaderType = defaultShaderType;
			std::string sourceCode = "";

			// Constructor / destructor
			Shader();
			Shader(ShaderType shaderType);

			Shader(const Shader& shader);
			Shader& operator=(const Shader& shader);

			Shader(Shader&& shader) noexcept = delete;
			Shader& operator=(Shader&& shader) noexcept = delete;

			~Shader();

			// Getters
			unsigned int getId() const;

			// Functions
			bool isCompiled() const;
			bool loadSourceCode(const std::filesystem::path& path);
			bool loadSourceCode(const std::filesystem::path& path, bool assignShaderType);
			bool compile();
			bool compile(std::string& compilationErrorMessage);
			void reset();
	};
}
