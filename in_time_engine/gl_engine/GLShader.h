#pragma once

// Dependencies | std
#include <string>
#include <filesystem>

// Dependencies | gl_engine
#include "GLHeader.h"

namespace gl {
	class Shader {
		public:
			// Enums
			enum class Type {
				UNKNOWN = -1,

				VERTEX = GL_VERTEX_SHADER,
				TESSELLATION_CONTROL = GL_TESS_CONTROL_SHADER,
				TESSELLATION_EVALUATION = GL_TESS_EVALUATION_SHADER,
				GEOMETRY = GL_GEOMETRY_SHADER,
				FRAGMENT = GL_FRAGMENT_SHADER,
				COMPUTE = GL_COMPUTE_SHADER
			};

		// Static
		private:
			// Properties
			static Type defaultShaderType;

			// Getters
			static Type getDefaultShaderType();

			// Setters
			static void setDefaultShaderType(Type shaderType);
			
		public:
			// Functions
			static bool validateShaderType(Type shaderType);
			static Type fileExtensionToShaderType(const std::string& fileExtension);
			static Type pathToShaderType(const std::filesystem::path& path);
		
		// Object
		private:
			// Properties
			unsigned int id{ 0U };

		public:
			// Properties
			Type shaderType{ Type::UNKNOWN };
			std::string sourceCode{};

			// Constructor / destructor
			Shader();
			Shader(Type shaderType);
			Shader(Type shaderType, const std::string& sourceCode);
			Shader(const Shader& shader);
			Shader(Shader&& shader) noexcept;
			~Shader();

			// Operators | assignment
			Shader& operator=(const Shader& shader);
			Shader& operator=(Shader&& shader) noexcept;

			// Getters
			unsigned int getId() const;

			// Functions
			bool isCompiled() const;
			bool loadSourceCode(const std::filesystem::path& path, bool assignShaderType = true);
			bool compile();
			bool compile(std::string& compilationErrorMessage);
			void free();
	};
}
