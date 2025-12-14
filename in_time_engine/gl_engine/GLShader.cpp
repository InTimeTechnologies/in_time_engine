#include "GLShader.h"

// Dependencies | std
#include <vector>
#include <fstream>

namespace gl {
	// class Shader

	// Static | private

	// Properties
	Shader::Type Shader::defaultShaderType = Type::VERTEX;

	// Getters
	Shader::Type Shader::getDefaultShaderType() {
		return defaultShaderType;
	}

	// Setters
	void Shader::setDefaultShaderType(Type shaderType) {
		if (validateShaderType(shaderType))
			defaultShaderType = shaderType;
	}

	// Functions
	bool Shader::validateShaderType(Type shaderType) {
		switch ((int)shaderType) {
		case GL_VERTEX_SHADER:
		case GL_TESS_CONTROL_SHADER:
		case GL_TESS_EVALUATION_SHADER:
		case GL_GEOMETRY_SHADER:
		case GL_FRAGMENT_SHADER:
			return true;
		default:
			return false;
		}
	}
	Shader::Type Shader::fileExtensionToShaderType(const std::string& fileExtension) {
		std::string lowerCaseFileExtension = fileExtension;
		for (int i = 0; i < fileExtension.size(); i++) {
			if (std::isupper(fileExtension[i])) {
				lowerCaseFileExtension[i] = std::tolower(fileExtension[i]);
			}
		}
		Type shaderType = Type::UNKNOWN;

		if (fileExtension == ".vert" || fileExtension == ".vs")
			shaderType = Type::VERTEX;
		else if (fileExtension == ".frag" || fileExtension == ".fs")
			shaderType = Type::FRAGMENT;
		else if (fileExtension == ".geom" || fileExtension == ".gs")
			shaderType = Type::GEOMETRY;
		else if (fileExtension == ".tesc" || fileExtension == ".tcs")
			shaderType = Type::TESSELLATION_CONTROL;
		else if (fileExtension == ".tese" || fileExtension == ".tes")
			shaderType = Type::TESSELLATION_EVALUATION;
		else if (fileExtension == ".comp" || fileExtension == ".cs")
			shaderType = Type::COMPUTE;

		return shaderType;
	}
	Shader::Type Shader::pathToShaderType(const std::filesystem::path& path) {
		return fileExtensionToShaderType(path.extension().string());
	}

	// Static | public

	// Functions

	// Object | public

	// Constructor / Destructor
	Shader::Shader() {

	}
	Shader::Shader(Type shaderType) : shaderType(shaderType) {

	}
	Shader::Shader(const Shader& shader) : shaderType(shader.shaderType), sourceCode(shader.sourceCode) {

	}
	Shader::Shader(Type shaderType, const std::string& sourceCode) : shaderType(shaderType), sourceCode(sourceCode) {

	}
	Shader::Shader(Shader&& other) noexcept : id(other.id), shaderType(other.shaderType), sourceCode(std::move(other.sourceCode)) {
		other.id = 0U;
		other.shaderType = Type::UNKNOWN;
	}
	Shader::~Shader() {
		free();
	}

	// Operators | assignment
	Shader& Shader::operator=(const Shader& shader) {
		if (this != &shader) {
			shaderType = shader.shaderType;
			sourceCode = shader.sourceCode;
		}
		return *this;
	}
	Shader& Shader::operator=(Shader&& other) noexcept {
		if (this != &other) {
			// Free existing GL resource if we own one
			free();

			// Steal resources
			id = other.id;
			shaderType = other.shaderType;
			sourceCode = std::move(other.sourceCode);

			// Reset other
			other.id = 0U;
			other.shaderType = Type::UNKNOWN;
		}
		return *this;
	}

	// Getters
	unsigned int Shader::getId() const {
		return id;
	}
	bool Shader::isCompiled() const {
		return id == 0 ? false : true;
	}

	// Functions
	bool Shader::loadSourceCode(const std::filesystem::path& path, bool assignShaderType) {
		// Open file, place cursor at end of file to get the size of the file in bytes
		std::ifstream ifstream(path, std::ios::binary | std::ios::ate);
		if (!ifstream.is_open())
			return false;
		size_t fileSize = ifstream.tellg();

		// Place the cursor at the beginning of the file and read all of it
		ifstream.seekg(ifstream.beg);
		sourceCode = std::string(fileSize, '\0');
		ifstream.read(&sourceCode[0], fileSize);
		ifstream.close();

		// Set shader type
		if (assignShaderType)
			shaderType = pathToShaderType(path);

		// Return success
		return true;
	}
	bool Shader::compile() {
		std::string compilationErrorMessage{};
		return compile(compilationErrorMessage);
	}
	bool Shader::compile(std::string& compilationErrorMessage) {
		// Free resources if allocated
		free();
		compilationErrorMessage.clear();

		// Create shader
		id = glCreateShader(static_cast<unsigned int>(shaderType));

		// Compile shader
		const char* shaderSourceCode = sourceCode.c_str();
		glShaderSource(id, 1, &shaderSourceCode, nullptr);
		glCompileShader(id);

		// Get compilation result
		int compilationResult = -1;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);

		// If compilation failed, flag this object with error and store compilation error message
		if (!compilationResult) {
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength); // maxLength includes the NULL chraracter
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			compilationErrorMessage.resize(maxLength - 1);
			for (int i = 0; i < maxLength - 1; i++)
				compilationErrorMessage[i] = errorLog[i];

			id = 0U;

			return false;
		}

		// Return success
		return true;
	}
	void Shader::free() {
		if (isCompiled())
			glDeleteShader(id);
		id = 0U;
	}
}
