#include "GLShader.h"

// Dependencies | std
#include <vector>
#include <fstream>

// class GLSLShaderSource

// Static | private

// Properties
gl::ShaderType gl::Shader::defaultShaderType = gl::ShaderType::VERTEX;

// Getters
gl::ShaderType gl::Shader::getDefaultShaderType() {
	return defaultShaderType;
}

// Setters
void gl::Shader::setDefaultShaderType(gl::ShaderType shaderType) {
	if (validateShaderType(shaderType))
		defaultShaderType = shaderType;
}

// Functions
bool gl::Shader::validateShaderType(gl::ShaderType shaderType) {
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
gl::ShaderType gl::Shader::fileExtensionToShaderType(const std::string& fileExtension) {
	std::string lowerCaseFileExtension = fileExtension;
	for (int i = 0; i < fileExtension.size(); i++) {
		if (std::isupper(fileExtension[i])) {
			lowerCaseFileExtension[i] = std::tolower(fileExtension[i]);
		}
	}
	gl::ShaderType shaderType = gl::ShaderType::NONE;

	if (fileExtension == ".vert" || fileExtension == ".vs")
		shaderType = ShaderType::VERTEX;
	else if (fileExtension == ".frag" || fileExtension == ".fs")
		shaderType = ShaderType::FRAGMENT;
	else if (fileExtension == ".geom" || fileExtension == ".gs")
		shaderType = ShaderType::GEOMETRY;
	else if (fileExtension == ".tesc" || fileExtension == ".tcs")
		shaderType = ShaderType::TESSELLATION_CONTROL;
	else if (fileExtension == ".tese" || fileExtension == ".tes")
		shaderType = ShaderType::TESSELLATION_EVALUATION;
	else if (fileExtension == ".comp" || fileExtension == ".cs")
		shaderType = ShaderType::COMPUTE;

	return shaderType;
}
gl::ShaderType gl::Shader::pathToShaderType(const std::filesystem::path& path) {
	return fileExtensionToShaderType(path.extension().string());
}

// Static | public

// Functions

// Object | public

// Constructor / Destructor
gl::Shader::Shader() {

}
gl::Shader::Shader(gl::ShaderType shaderType) : shaderType(shaderType) {

}
gl::Shader::Shader(const gl::Shader& shader) : shaderType(shader.shaderType), sourceCode(shader.sourceCode) {

}
gl::Shader& gl::Shader::operator=(const gl::Shader& shader) {
	if (this != &shader) {
		shaderType = shader.shaderType;
		sourceCode = shader.sourceCode;
	}
	return *this;
}
gl::Shader::~Shader() {
	reset();
}

// Getters
unsigned int gl::Shader::getId() const {
	return id;
}
bool gl::Shader::isCompiled() const {
	return id == 0 ? false : true;
}

// Functions
bool gl::Shader::loadSourceCode(const std::filesystem::path& path) {
	return loadSourceCode(path, false);
}
bool gl::Shader::loadSourceCode(const std::filesystem::path& path, bool assignShaderType) {
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
bool gl::Shader::compile() {
	std::string compilationErrorMessage = "";
	return compile(compilationErrorMessage);
}
bool gl::Shader::compile(std::string& compilationErrorMessage) {
	// Free resources if allocated
	reset();
	compilationErrorMessage = "";

	// Create shader
	id = glCreateShader((unsigned int)shaderType);

	// Compile shader
	const char* tempShaderSourceCode = sourceCode.c_str(); // Do not edit. You'll brake it.
	glShaderSource(id, 1, &tempShaderSourceCode, nullptr);
	glCompileShader(id);

	// Get compilation result
	int compilationResult = -1;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);

	// If compilation failed, flag this object with error and store compilation error message
	if (!compilationResult) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);
		id = 0U;

		return false;
	}

	// Return success
	return true;
}
void gl::Shader::reset() {
	if (isCompiled())
		glDeleteShader(id);
	id = 0U;
}
