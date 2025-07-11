#include "GLProgram.h"

// class GLSLProgram

// Static | private

// Functions | Helper
int gl::Program::getElementCount(GLenum openGLType) {
	switch (openGLType) {
		// Scalar
		case GL_BOOL:
		case GL_INT:
		case GL_UNSIGNED_INT:
		case GL_FLOAT:
		case GL_DOUBLE:
		return 1;
		// vec2
		case GL_BOOL_VEC2:
		case GL_INT_VEC2:
		case GL_UNSIGNED_INT_VEC2:
		case GL_FLOAT_VEC2:
		case GL_DOUBLE_VEC2:
		return 2;
		// vec3
		case GL_BOOL_VEC3:
		case GL_INT_VEC3:
		case GL_UNSIGNED_INT_VEC3:
		case GL_FLOAT_VEC3:
		case GL_DOUBLE_VEC3:
		return 3;
		// vec4
		case GL_BOOL_VEC4:
		case GL_INT_VEC4:
		case GL_UNSIGNED_INT_VEC4:
		case GL_FLOAT_VEC4:
		case GL_DOUBLE_VEC4:
		return 4;
		// mat2
		case GL_FLOAT_MAT2:
		case GL_DOUBLE_MAT2:
		return 4;
		// mat3
		case GL_FLOAT_MAT3:
		case GL_DOUBLE_MAT3:
		return 9;
		// mat4
		case GL_FLOAT_MAT4:
		case GL_DOUBLE_MAT4:
		return 16;
		// mat2x3
		case GL_FLOAT_MAT2x3:
		case GL_DOUBLE_MAT2x3:
		return 6;
		// mat2x4
		case GL_FLOAT_MAT2x4:
		case GL_DOUBLE_MAT2x4:
		return 8;
		// mat3x2
		case GL_FLOAT_MAT3x2:
		case GL_DOUBLE_MAT3x2:
		return 6;
		// mat3x4
		case GL_FLOAT_MAT3x4:
		case GL_DOUBLE_MAT3x4:
		return 12;
		// mat4x2
		case GL_FLOAT_MAT4x2:
		case GL_DOUBLE_MAT4x2:
		return 8;
		// mat4x3
		case GL_FLOAT_MAT4x3:
		case GL_DOUBLE_MAT4x3:
			return 12;
		default:
			return 0;
	}
}
int gl::Program::getElementCount(gl::DataType dataType) {
	switch (dataType) {
		// Scalar
		case DataType::BOOL:
		case DataType::INT:
		case DataType::UNSIGNED_INT:
		case DataType::FLOAT:
		case DataType::DOUBLE:
			return 1;
			// vec2
		case DataType::BOOL_VEC2:
		case DataType::INT_VEC2:
		case DataType::UNSIGNED_INT_VEC2:
		case DataType::FLOAT_VEC2:
		case DataType::DOUBLE_VEC2:
			return 2;
		// vec3
		case DataType::BOOL_VEC3:
		case DataType::INT_VEC3:
		case DataType::UNSIGNED_INT_VEC3:
		case DataType::FLOAT_VEC3:
		case DataType::DOUBLE_VEC3:
			return 3;
		// vec4
		case DataType::BOOL_VEC4:
		case DataType::INT_VEC4:
		case DataType::UNSIGNED_INT_VEC4:
		case DataType::FLOAT_VEC4:
		case DataType::DOUBLE_VEC4:
			return 4;
		// mat2
		case DataType::FLOAT_MAT2:
		case DataType::DOUBLE_MAT2:
			return 4;
		// mat3
		case DataType::FLOAT_MAT3:
		case DataType::DOUBLE_MAT3:
			return 9;
		// mat4
		case DataType::FLOAT_MAT4:
		case DataType::DOUBLE_MAT4:
			return 16;
		// mat2x3
		case DataType::FLOAT_MAT2x3:
		case DataType::DOUBLE_MAT2x3:
			return 6;
		// mat2x4
		case DataType::FLOAT_MAT2x4:
		case DataType::DOUBLE_MAT2x4:
			return 8;
		// mat3x2
		case DataType::FLOAT_MAT3x2:
		case DataType::DOUBLE_MAT3x2:
			return 6;
		// mat3x4
		case DataType::FLOAT_MAT3x4:
		case DataType::DOUBLE_MAT3x4:
			return 12;
		// mat4x2
		case DataType::FLOAT_MAT4x2:
		case DataType::DOUBLE_MAT4x2:
			return 8;
		// mat4x3
		case DataType::FLOAT_MAT4x3:
		case DataType::DOUBLE_MAT4x3:
			return 12;
		default:
			return 0;
	}
}
gl::DataType gl::Program::getBaseType(gl::DataType dataType) {
	switch (dataType) {
		// bool
		case DataType::BOOL:
		case DataType::BOOL_VEC2:
		case DataType::BOOL_VEC3:
		case DataType::BOOL_VEC4:
			return DataType::BOOL;

		// int
		case DataType::BYTE:
		case DataType::SHORT:
		case DataType::INT:
		case DataType::INT_VEC2:
		case DataType::INT_VEC3:
		case DataType::INT_VEC4:
			return DataType::INT;

		// unsigned int
		case DataType::UNSIGNED_INT:
		case DataType::UNSIGNED_INT_VEC2:
		case DataType::UNSIGNED_INT_VEC3:
		case DataType::UNSIGNED_INT_VEC4:
			return DataType::UNSIGNED_INT;

		// float
		case DataType::FLOAT:
		case DataType::FLOAT_VEC2:
		case DataType::FLOAT_VEC3:
		case DataType::FLOAT_VEC4:
		case DataType::FLOAT_MAT2:
		case DataType::FLOAT_MAT3:
		case DataType::FLOAT_MAT4:
		case DataType::FLOAT_MAT2x3:
		case DataType::FLOAT_MAT2x4:
		case DataType::FLOAT_MAT3x2:
		case DataType::FLOAT_MAT3x4:
		case DataType::FLOAT_MAT4x2:
		case DataType::DOUBLE_MAT4x2:
		case DataType::FLOAT_MAT4x3:
			return DataType::FLOAT;

		// double
		case DataType::DOUBLE:
		case DataType::DOUBLE_VEC2:
		case DataType::DOUBLE_VEC3:
		case DataType::DOUBLE_VEC4:
		case DataType::DOUBLE_MAT2:
		case DataType::DOUBLE_MAT3:
		case DataType::DOUBLE_MAT4:
		case DataType::DOUBLE_MAT2x3:
		case DataType::DOUBLE_MAT2x4:
		case DataType::DOUBLE_MAT3x2:
		case DataType::DOUBLE_MAT3x4:
		case DataType::DOUBLE_MAT4x3:
			return DataType::DOUBLE;
	}

	return DataType::NONE;
}

// Static | public

// Functions
void gl::Program::unbind() {
	glUseProgram(0);
}
int gl::Program::getDataTypeSize(gl::DataType dataType) {
	switch (dataType) {
		// Scalars
		case DataType::BOOL:
			return sizeof(bool);
		case DataType::BYTE:
			return sizeof(char);
		case DataType::SHORT:
			return sizeof(short);
		case DataType::INT:
			return sizeof(int);
		case DataType::UNSIGNED_INT:
			return sizeof(unsigned int);
		case DataType::FLOAT:
			return sizeof(float);
		case DataType::DOUBLE:
			return sizeof(double);
		case DataType::FIXED:
			return sizeof(float);

		// vec2
		case DataType::BOOL_VEC2:
			return sizeof(glm::bvec2);
		case DataType::INT_VEC2:
			return sizeof(glm::ivec2);
		case DataType::UNSIGNED_INT_VEC2:
			return sizeof(glm::uvec2);
		case DataType::FLOAT_VEC2:
			return sizeof(glm::vec2);
		case DataType::DOUBLE_VEC2:
			return sizeof(glm::dvec2);

		// vec3
		case DataType::BOOL_VEC3:
			return sizeof(glm::bvec3);
		case DataType::INT_VEC3:
			return sizeof(glm::vec3);
		case DataType::UNSIGNED_INT_VEC3:
			return sizeof(glm::uvec3);
		case DataType::FLOAT_VEC3:
			return sizeof(glm::vec3);
		case DataType::DOUBLE_VEC3:
			return sizeof(glm::dvec3);

		// vec4
		case DataType::BOOL_VEC4:
			return sizeof(glm::bvec4);
		case DataType::INT_VEC4:
			return sizeof(glm::ivec4);
		case DataType::UNSIGNED_INT_VEC4:
			return sizeof(glm::uvec4);
		case DataType::FLOAT_VEC4:
			return sizeof(glm::vec4);
		case DataType::DOUBLE_VEC4:
			return sizeof(glm::dvec4);

		// mat2
		case DataType::FLOAT_MAT2:
			return sizeof(glm::mat2);
		case DataType::DOUBLE_MAT2:
			return sizeof(glm::dmat2);

		// mat3
		case DataType::FLOAT_MAT3:
			return sizeof(glm::mat4);
		case DataType::DOUBLE_MAT3:
			return sizeof(glm::dmat3);

		// mat4
		case DataType::FLOAT_MAT4:
			return sizeof(glm::mat4);
		case DataType::DOUBLE_MAT4:
			return sizeof(glm::dmat4);

		// mat2x3
		case DataType::FLOAT_MAT2x3:
			return sizeof(glm::mat2x3);
		case DataType::DOUBLE_MAT2x3:
			return sizeof(glm::dmat3x3);

		// mat2x4
		case DataType::FLOAT_MAT2x4:
			return sizeof(glm::mat2x4);
		case DataType::DOUBLE_MAT2x4:
			return sizeof(glm::dmat2x4);

		// mat3x2
		case DataType::FLOAT_MAT3x2:
			return sizeof(glm::mat3x4);
		case DataType::DOUBLE_MAT3x2:
			return sizeof(glm::dmat3x2);

		// mat3x4
		case DataType::FLOAT_MAT3x4:
			return sizeof(glm::mat3x4);
		case DataType::DOUBLE_MAT3x4:
			return sizeof(glm::dmat3x4);

		// mat4x2
		case DataType::FLOAT_MAT4x2:
			return sizeof(glm::mat4x2);
		case DataType::DOUBLE_MAT4x2:
			return sizeof(glm::dmat4x2);

		// mat4x3
		case DataType::FLOAT_MAT4x3:
			return sizeof(glm::mat4x3);
		case DataType::DOUBLE_MAT4x3:
			return sizeof(glm::mat4x3);
	}

	return 0;
}

// Object | public

// Constructor / destructor
gl::Program::Program() {

}
gl::Program::~Program() {
	reset();
}

// Getters
unsigned int gl::Program::getId() const {
	return id;
}
std::vector<gl::Attribute> gl::Program::getAttributes() const {
	return attributes;
}
std::vector<gl::Uniform> gl::Program::getUniforms() const {
	return uniforms;
}
std::vector<gl::ShaderStorageBuffer> gl::Program::getSSBOs() const {
	return ssbos;
}

// Functions
bool gl::Program::isLinked() const {
	return id == 0U ? false : true;
}
bool gl::Program::link(const std::initializer_list<unsigned int>& shaderIds) {
	// Free resources if allocated
	reset();

	// Create glsl program
	id = glCreateProgram();
	glProgramParameteri(id, GL_PROGRAM_SEPARABLE, separableProgram);

	// Attach all the shaders to this program and link them
	for (unsigned int shaderId : shaderIds)
		glAttachShader(id, shaderId);
	glLinkProgram(id);

	// Retrieve linking result
	int linkResult = 0;
	glGetProgramiv(id, GL_LINK_STATUS, (int*)&linkResult);
	if (linkResult == GL_FALSE) {
		// Get linking error message
		GLint maxLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::string linkingErrorMessage = std::string(maxLength, '\0');
		glGetProgramInfoLog(id, maxLength, &maxLength, &linkingErrorMessage[0]);

		// Free resources
		glDeleteProgram(id);
		id = 0U;

		// Return fail
		return false;
	}

	// Detach shaders. They are no longer needed
	for (unsigned int shaderId : shaderIds)
		glDetachShader(id, shaderId);

	// Retrieve all properties in program
	updateProperties();

	return true;
}
bool gl::Program::link(const std::initializer_list<gl::Shader*>& shaders) {
	// Free resources if allocated
	reset();

	// Create glsl program
	id = glCreateProgram();
	glProgramParameteri(id, GL_PROGRAM_SEPARABLE, separableProgram);

	// Attach all the shaders to this program and link them
	for (Shader* shader : shaders)
		glAttachShader(id, shader->getId());
	glLinkProgram(id);

	// Retrieve linking result
	int linkResult = 0;
	glGetProgramiv(id, GL_LINK_STATUS, (int*)&linkResult);
	if (linkResult == GL_FALSE) {
		// Get linking error message
		GLint maxLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std:: string linkingErrorMessage = std::string(maxLength, '\0');
		glGetProgramInfoLog(id, maxLength, &maxLength, &linkingErrorMessage[0]);

		// Free resources
		glDeleteProgram(id);
		id = 0U;

		// Return fail
		return false;
	}

	// Detach shaders. They are no longer needed
	for (Shader* shader : shaders)
		glDetachShader(id, shader->getId());

	// Retrieve all properties in program
	updateProperties();

	return true;
}
void gl::Program::bind() const {
	if (!isLinked())
		return;

	glUseProgram(id);
}
void gl::Program::reset() {
	if (isLinked())
		glDeleteProgram(id);
	id = 0U;
}
void gl::Program::updateProperties() {
	updateAttributes();
	updateUniforms();
	updateUniformBlocks();
	updateSSBOs();
}
void gl::Program::updateAttributes() {
	int activeAttributeLocations = -1;
	glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &activeAttributeLocations);
	attributes = std::vector<Attribute>(activeAttributeLocations);
	for (int i = 0; i < activeAttributeLocations; i++) {
		const GLsizei maximumNameLength = 50;		// Maximum name length
		GLchar attributeName[maximumNameLength];	// Variable name in GLSL
		GLsizei nameLength;							// Name length
		GLint arraySize;							// The length of the data (vec4 will be an array size of 1)
		GLenum dataType;							// The data type (GL_FLOAT,GL_BOOL, GL_INT, etc...)
		GLint location;								// Location of the attribut (unique to the program)

		glGetActiveAttrib(id, (unsigned int)i, maximumNameLength, &nameLength, &arraySize, &dataType, attributeName);
		location = glGetAttribLocation(id, attributeName);

		attributes[i].name = std::string(attributeName);
		attributes[i].location = location;
		attributes[i].elementCount = getElementCount(dataType);
		attributes[i].arraySize = arraySize;
		attributes[i].dataType = (DataType)dataType;
		attributes[i].baseDataType = (DataType)getBaseType(attributes[i].dataType);
	}

	// Sort attributes by location
	for (unsigned int i = 0; i < attributes.size(); i++) {
		for (unsigned int j = i + 1; j < attributes.size(); j++) {
			if (attributes[i].location > attributes[j].location) {
				Attribute temp = attributes[i];
				attributes[i] = attributes[j];
				attributes[j] = temp;
			}
		}
	}
}
void gl::Program::updateUniforms() {
	int activeUniformLocations = -1;
	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &activeUniformLocations);
	uniforms = std::vector<Uniform>(activeUniformLocations);
	std::vector<int> uniformIndicesThatBelongToABlock = std::vector<int>(0);


	for (int i = 0; i < activeUniformLocations; i++) {
		const int maximumNameLength = 50;			// Maximum name length
		char uniformName[maximumNameLength];		// Variable name in GLSL
		int nameLength;								// Name length
		int arraySize;								// The length of the data (vec4 will be an array size of 1)
		unsigned int dataType;						// The data type (GL_FLOAT,GL_BOOL, GL_INT, etc...)
		int location;								// Location of the uniform (unique to the program)

		glGetActiveUniform(id, (unsigned int)i, maximumNameLength, &nameLength, &arraySize, &dataType, uniformName);
		location = glGetUniformLocation(id, uniformName);

		if (location == -1) {
			uniformIndicesThatBelongToABlock.push_back(i);
			continue;
		}

		uniforms[i].location = location;
		uniforms[i].elementCount = getElementCount(dataType);
		uniforms[i].arraySize = arraySize;
		uniforms[i].dataType = (gl::DataType)dataType;
		uniforms[i].name = uniformName;
	}

	// Remove uniforms that belong to a uniform block
	for (int i : uniformIndicesThatBelongToABlock)
		uniforms.erase(uniforms.begin() + i);

	// Sort uniforms by location
	for (unsigned int i = 0; i < uniforms.size(); i++) {
		for (unsigned int j = i + 1; j < uniforms.size(); j++) {
			if (uniforms[i].location > uniforms[j].location) {
				gl::Uniform temp = uniforms[i];
				uniforms[i] = uniforms[j];
				uniforms[j] = temp;
			}
		}
	}
}
void gl::Program::updateUniformBlocks() {
	int activeUniformBlocks = -1;
	glGetProgramiv(id, GL_ACTIVE_UNIFORM_BLOCKS, &activeUniformBlocks);
	uniformBlocks.resize(activeUniformBlocks);

	for (int i = 0; i < activeUniformBlocks; i++) {
		const int maximumNameLength = 50;
		char uniformName[maximumNameLength];
		int nameLength = -1;
		int location;

		// Get the length of the uniform block name
		glGetActiveUniformBlockiv(id, i, GL_UNIFORM_BLOCK_NAME_LENGTH, &nameLength);

		// Allocate memory for the uniform block name buffer
		char* uniformNameBuffer = new char[nameLength];

		// Get the uniform block name
		glGetActiveUniformBlockName(id, i, nameLength, nullptr, uniformNameBuffer);

		// Copy the uniform block name to the uniformName array
		strcpy_s(uniformName, maximumNameLength, uniformNameBuffer);

		// Free the memory allocated for the uniform block name buffer
		delete[] uniformNameBuffer;

		// Get the binding point of the uniform block
		glGetActiveUniformBlockiv(id, i, GL_UNIFORM_BLOCK_BINDING, &location);

		// Store the uniform block name and location
		uniformBlocks[i].name = std::string(uniformName);
		uniformBlocks[i].bindingPoint = location;

		// Get number of active variables
		GLenum dataToRetrieve = GL_BUFFER_BINDING;
		int numberOfVariables = -1;
		dataToRetrieve = GL_NUM_ACTIVE_VARIABLES;
		glGetProgramResourceiv(id, GL_UNIFORM_BLOCK, i, 1, &dataToRetrieve, 1, nullptr, &numberOfVariables);
		uniformBlocks[i].variables = std::vector<gl::UniformBlockData>(numberOfVariables);

		// Get all the information about the variables in the uniform block and set it
		for (int j = 0; j < numberOfVariables; j++) {
			// Get current variable's name of current uniform block
			char variableName[255];
			glGetProgramResourceName(id, GL_UNIFORM, j, 1024, nullptr, variableName);

			// Get current variable's data type of current uniform block
			dataToRetrieve = GL_TYPE;
			int dataType = -1;
			glGetProgramResourceiv(id, GL_UNIFORM, j, 1, &dataToRetrieve, 1, nullptr, &dataType);

			// Get current variable's array size of current uniform block
			dataToRetrieve = GL_ARRAY_SIZE;
			int arraySize = -1;
			glGetProgramResourceiv(id, GL_UNIFORM, j, 1, &dataToRetrieve, 1, nullptr, &arraySize);

			// Set the uniform block variable's data
			uniformBlocks[i].variables[j].name = std::string(variableName);
			uniformBlocks[i].variables[j].dataType = (DataType)dataType;
			uniformBlocks[i].variables[j].arraySize = arraySize;
			uniformBlocks[i].variables[j].elementCount = getElementCount(dataType);
		}

	}
}
void gl::Program::updateSSBOs() {
	int shaderStorageBufferCount = 0;
	glGetProgramInterfaceiv(id, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, &shaderStorageBufferCount);
	ssbos = std::vector<ShaderStorageBuffer>(shaderStorageBufferCount);

	for (int i = 0; i < shaderStorageBufferCount; i++) {
		// Get shader storage buffer name
		char shaderStorageBufferName[255];
		glGetProgramResourceName(id, GL_SHADER_STORAGE_BLOCK, i, 1024, nullptr, shaderStorageBufferName);
		ssbos[i].name = std::string(shaderStorageBufferName);

		// Get shader storage buffer binding point
		int bindingPoint = -1;
		GLenum dataToRetrieve = GL_BUFFER_BINDING;
		glGetProgramResourceiv(id, GL_SHADER_STORAGE_BLOCK, i, 1, &dataToRetrieve, 1, nullptr, &bindingPoint);
		ssbos[i].bindingPoint = bindingPoint;

		// Get number of active variables
		int numberOfVariables = -1;
		dataToRetrieve = GL_NUM_ACTIVE_VARIABLES;
		glGetProgramResourceiv(id, GL_SHADER_STORAGE_BLOCK, i, 1, &dataToRetrieve, 1, nullptr, &numberOfVariables);
		ssbos[i].variables = std::vector<ShaderStorageBufferData>(numberOfVariables);

		// Get all the information about the variables in the shader storage buffer and set it
		for (int j = 0; j < numberOfVariables; j++) {
			// Get current variable's name of current shader storage buffer
			char variableName[255];
			glGetProgramResourceName(id, GL_BUFFER_VARIABLE, j, 1024, nullptr, variableName);

			// Get current variable's data type of current shader storage buffer
			dataToRetrieve = GL_TYPE;
			int dataType = -1;
			glGetProgramResourceiv(id, GL_BUFFER_VARIABLE, j, 1, &dataToRetrieve, 1, nullptr, &dataType);

			// Get current variable's array size of current shader storage buffer
			dataToRetrieve = GL_ARRAY_SIZE;
			int arraySize = -1;
			glGetProgramResourceiv(id, GL_BUFFER_VARIABLE, j, 1, &dataToRetrieve, 1, nullptr, &arraySize);

			// Set the shader storage variable's data
			ssbos[i].variables[j].name = std::string(variableName);
			ssbos[i].variables[j].dataType = (DataType)dataType;
			ssbos[i].variables[j].arraySize = arraySize;
			ssbos[i].variables[j].elementCount = getElementCount(dataType);
		}
	}
}

int gl::Program::getUniformLocation(const std::string& uniformName) const {
	return glGetUniformLocation(id, uniformName.c_str());
}

void gl::Program::setUniform(int location, int value) const {
	glUniform1i(location, value);
}
void gl::Program::setUniform(int location, unsigned int value) const {
	glUniform1ui(location, value);
}
void gl::Program::setUniform(int location, float value) const {
	glUniform1f(location, value);
}
void gl::Program::setUniform(int location, const glm::ivec2& value) const {
	glUniform2i(location, value[0], value[1]);
}
void gl::Program::setUniform(int location, const glm::uvec2& value) const {
	glUniform2ui(location, value[0], value[1]);
}
void gl::Program::setUniform(int location, const glm::vec2& value) const {
	glUniform2f(location, value[0], value[1]);
}
void gl::Program::setUniform(int location, const glm::ivec3& value) const {
	glUniform3i(location, value[0], value[1], value[2]);
}
void gl::Program::setUniform(int location, const glm::uvec3& value) const {
	glUniform3ui(location, value[0], value[1], value[2]);
}
void gl::Program::setUniform(int location, const glm::vec3& value) const {
	glUniform3f(location, value[0], value[1], value[2]);
}
void gl::Program::setUniform(int location, const glm::ivec4& value) const {
	glUniform4i(location, value[0], value[1], value[2], value[3]);
}
void gl::Program::setUniform(int location, const glm::uvec4& value) const {
	glUniform4ui(location, value[0], value[1], value[2], value[3]);
}
void gl::Program::setUniform(int location, const glm::vec4& value) const {
	glUniform4f(location, value[0], value[1], value[2], value[3]);
}

void gl::Program::setUniform(int location, int count, int data[]) const {
	glUniform1iv(location, count, data);
}
void gl::Program::setUniform(int location, int count, glm::ivec2 data[]) const {
	glUniform2iv(location, count, (int*)data);
}
void gl::Program::setUniform(int location, int count, glm::ivec3 data[]) const {
	glUniform3iv(location, count, (int*)data);
}
void gl::Program::setUniform(int location, int count, glm::ivec4 data[]) const {
	glUniform4iv(location, count, (int*)data);
}
void gl::Program::setUniform(int location, int count, unsigned int data[]) const {
	glUniform1uiv(location, count, data);
}
void gl::Program::setUniform(int location, int count, glm::uvec2 data[]) const {
	glUniform2uiv(location, count, (unsigned int*)data);
}
void gl::Program::setUniform(int location, int count, glm::uvec3 data[]) const {
	glUniform3uiv(location, count, (unsigned int*)data);
}
void gl::Program::setUniform(int location, int count, glm::uvec4 data[]) const {
	glUniform4uiv(location, count, (unsigned int*)data);
}
void gl::Program::setUniform(int location, int count, float data[]) const {

	glUniform1fv(location, count, data);
}
void gl::Program::setUniform(int location, int count, glm::vec2 data[]) const {
	glUniform2fv(location, count, (float*)data);
}
void gl::Program::setUniform(int location, int count, glm::vec3 data[]) const {
	glUniform3fv(location, count, (float*)data);
}
void gl::Program::setUniform(int location, int count, glm::vec4 data[]) const {
	glUniform4fv(location, count, (float*)data);
}

void gl::Program::setUniform(int location, int count, bool transpose, glm::mat2 data[]) const {
	glUniformMatrix2fv(location, count, transpose, (float*)data);
}
void gl::Program::setUniform(int location, int count, bool transpose, glm::mat2x3 data[]) const {
	glUniformMatrix2x3fv(location, count, transpose, (float*)data);
}
void gl::Program::setUniform(int location, int count, bool transpose, glm::mat2x4 data[]) const {
	glUniformMatrix2x4fv(location, count, transpose, (float*)data);
}
void gl::Program::setUniform(int location, int count, bool transpose, glm::mat3 data[]) const {
	glUniformMatrix3fv(location, count, transpose, (float*)data);
}
void gl::Program::setUniform(int location, int count, bool transpose, glm::mat3x2 data[]) const {
	glUniformMatrix3x2fv(location, count, transpose, (float*)data);
}
void gl::Program::setUniform(int location, int count, bool transpose, glm::mat3x4 data[]) const {
	glUniformMatrix3x4fv(location, count, transpose, (float*)data);
}
void gl::Program::setUniform(int location, int count, bool transpose, glm::mat4 data[]) const {
	glUniformMatrix4fv(location, count, transpose, (float*)data);
}
void gl::Program::setUniform(int location, int count, bool transpose, glm::mat4x2 data[]) const {
	glUniformMatrix4x2fv(location, count, transpose, (float*)data);
}
void gl::Program::setUniform(int location, int count, bool transpose, glm::mat4x3 data[]) const {
	glUniformMatrix4x3fv(location, count, transpose, (float*)data);
}

void gl::Program::setProgramUniform(int location, int value) const {
	glProgramUniform1i(id, location, value);
}
void gl::Program::setProgramUniform(int location, unsigned int value) const {
	glProgramUniform1ui(id, location, value);
}
void gl::Program::setProgramUniform(int location, float value) const {
	glProgramUniform1f(id, location, value);
}
void gl::Program::setProgramUniform(int location, const glm::ivec2& value) const {
	glProgramUniform2i(id, location, value[0], value[1]);
}
void gl::Program::setProgramUniform(int location, const glm::uvec2& value) const {
	glProgramUniform2ui(id, location, value[0], value[1]);
}
void gl::Program::setProgramUniform(int location, const glm::vec2& value) const {
	glProgramUniform2f(id, location, value[0], value[1]);
}
void gl::Program::setProgramUniform(int location, const glm::ivec3& value) const {
	glProgramUniform3i(id, location, value[0], value[1], value[2]);
}
void gl::Program::setProgramUniform(int location, const glm::uvec3& value) const {
	glProgramUniform3ui(id, location, value[0], value[1], value[2]);
}
void gl::Program::setProgramUniform(int location, const glm::vec3& value) const {
	glProgramUniform3f(id, location, value[0], value[1], value[2]);
}
void gl::Program::setProgramUniform(int location, const glm::ivec4& value) const {
	glProgramUniform4i(id, location, value[0], value[1], value[2], value[3]);
}
void gl::Program::setProgramUniform(int location, const glm::uvec4& value) const {
	glProgramUniform4ui(id, location, value[0], value[1], value[2], value[3]);
}
void gl::Program::setProgramUniform(int location, const glm::vec4& value) const {
	glProgramUniform4f(id, location, value[0], value[1], value[2], value[3]);
}

void gl::Program::setProgramUniform(int location, int count, int data[]) const {
	glProgramUniform1iv(id, location, count, data);
}
void gl::Program::setProgramUniform(int location, int count, glm::ivec2 data[]) const {
	glProgramUniform2iv(id, location, count, (int*)data);
}
void gl::Program::setProgramUniform(int location, int count, glm::ivec3 data[]) const {
	glProgramUniform3iv(id, location, count, (int*)data);
}
void gl::Program::setProgramUniform(int location, int count, glm::ivec4 data[]) const {
	glProgramUniform4iv(id, location, count, (int*)data);
}
void gl::Program::setProgramUniform(int location, int count, unsigned int data[]) const {
	glProgramUniform1uiv(id, location, count, data);
}
void gl::Program::setProgramUniform(int location, int count, glm::uvec2 data[]) const {
	glProgramUniform2uiv(id, location, count, (unsigned int*)data);
}
void gl::Program::setProgramUniform(int location, int count, glm::uvec3 data[]) const {
	glProgramUniform3uiv(id, location, count, (unsigned int*)data);
}
void gl::Program::setProgramUniform(int location, int count, glm::uvec4 data[]) const {
	glProgramUniform4uiv(id, location, count, (unsigned int*)data);
}
void gl::Program::setProgramUniform(int location, int count, float data[]) const {
	glProgramUniform1fv(id, location, count, data);
}
void gl::Program::setProgramUniform(int location, int count, glm::vec2 data[]) const {
	glProgramUniform2fv(id, location, count, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, glm::vec3 data[]) const {
	glProgramUniform3fv(id, location, count, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, glm::vec4 data[]) const {
	glProgramUniform4fv(id, location, count, (float*)data);
}

void gl::Program::setProgramUniform(int location, int count, bool transpose, glm::mat2 data[]) const {
	glProgramUniformMatrix2fv(id, location, count, transpose, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, bool transpose, glm::mat2x3 data[]) const {
	glProgramUniformMatrix2x3fv(id, location, count, transpose, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, bool transpose, glm::mat2x4 data[]) const {
	glProgramUniformMatrix2x4fv(id, location, count, transpose, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, bool transpose, glm::mat3 data[]) const {
	glProgramUniformMatrix3fv(id, location, count, transpose, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, bool transpose, glm::mat3x2 data[]) const {
	glProgramUniformMatrix3x2fv(id, location, count, transpose, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, bool transpose, glm::mat3x4 data[]) const {
	glProgramUniformMatrix3x4fv(id, location, count, transpose, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, bool transpose, glm::mat4 data[]) const {
	glProgramUniformMatrix4fv(id, location, count, transpose, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, bool transpose, glm::mat4x2 data[]) const {
	glProgramUniformMatrix4x2fv(id, location, count, transpose, (float*)data);
}
void gl::Program::setProgramUniform(int location, int count, bool transpose, glm::mat4x3 data[]) const {
	glProgramUniformMatrix4x3fv(id, location, count, transpose, (float*)data);
}

// Function | Attribute
void gl::Program::enableAttribute(unsigned int index) const {
	glEnableVertexAttribArray(index);
}
void gl::Program::disableAttribute(unsigned int index) const {
	glDisableVertexAttribArray(index);
}
void gl::Program::enableAttributes() const {
	for (const Attribute& attribute : attributes)
		glEnableVertexAttribArray(attribute.location);
}
void gl::Program::disableAttributes() const {
	for (const Attribute& attribute : attributes)
		glDisableVertexAttribArray(attribute.location);
}


void gl::Program::setAttributeFormat(unsigned int attributeLocation, int elementCount, gl::DataType dataType, bool normalized, unsigned int relativeOffset) const {
	glVertexAttribFormat(attributeLocation, elementCount, (GLenum)dataType, normalized, relativeOffset);
}
void gl::Program::setAttributeIFormat(unsigned int attributeLocation, int elementCount, gl::DataType dataType, unsigned int relativeOffset) const {
	glVertexAttribIFormat(attributeLocation, elementCount, (GLenum)dataType, relativeOffset);
}
void gl::Program::setAttributeLFormat(unsigned int attributeLocation, int elementCount, gl::DataType dataType, unsigned int relativeOffset) const {
	glVertexAttribLFormat(attributeLocation, elementCount, (GLenum)dataType, relativeOffset);
}
void gl::Program::autoSetAttributeFormat() {
	int relativeOffset = 0;
	for (const gl::Attribute& attribute : attributes) {
		switch (attribute.baseDataType) {
			case gl::DataType::INT:
				setAttributeIFormat(attribute.location, attribute.elementCount, attribute.baseDataType, relativeOffset);
				break;
			case gl::DataType::FLOAT:
				setAttributeFormat(attribute.location, attribute.elementCount, attribute.baseDataType, attribute.normalize, relativeOffset);
				break;
		}
		relativeOffset += attribute.arraySize * getDataTypeSize(attribute.dataType);
	}
}

void gl::Program::setAttributeBinding(unsigned int attributeLocation, unsigned int bindingIndex) const {
	glVertexAttribBinding(attributeLocation, bindingIndex);
}
void gl::Program::autoSetAttributeBinding(unsigned int bindingIndex) const {
	for (const Attribute& attribute : attributes)
		setAttributeBinding(attribute.location, bindingIndex);
}
