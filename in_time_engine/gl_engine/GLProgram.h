#pragma once

// Dependencies | std
#include <string>
#include <initializer_list>

// Dependencies | OpenGL
#include <glew/glew.h>

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | OpenGLEngine
#include "GLDataType.h"
#include "GLShader.h"

namespace gl {
	struct Attribute {
		std::string name = "";
		int location = -1;
		int elementCount = -1;
		int arraySize = -1;
		DataType dataType = DataType::NONE;
		DataType baseDataType = DataType::NONE;
		bool normalize = false;
	};

	struct Uniform {
		std::string name = "";
		int location = -1;
		int elementCount = -1;
		int arraySize = -1;
		DataType dataType = DataType::NONE;
	};

	struct UniformBlockData {
		std::string name = "";
		int elementCount = -1;
		int arraySize = -1;
		DataType dataType = DataType::NONE;
	};

	struct UniformBlock {
		std::string name = "";
		int bindingPoint = -1;
		std::vector<UniformBlockData> variables = std::vector<UniformBlockData>();
	};

	struct ShaderStorageBufferData {
		std::string name = "";
		int elementCount = -1;
		int arraySize = -1;
		DataType dataType = DataType::NONE;
	};

	struct ShaderStorageBuffer {
		std::string name = "";
		int bindingPoint = -1;
		std::vector<ShaderStorageBufferData> variables = std::vector<ShaderStorageBufferData>();
	};

	class Program {
		// Static
		private:
			// Functions | Helper
			static int getElementCount(GLenum openGLType);
			static int getElementCount(DataType glslDataType);
			static DataType getBaseType(DataType glslDataType);

		public:
			// Functions
			static void unbind();
			static int getDataTypeSize(DataType glslDataType);

		// Object
		private:
			// Properties
			unsigned int id = 0U;

		public:
			// Properties
			bool separableProgram = false;
			std::vector<Attribute> attributes;
			std::vector<Uniform> uniforms;
			std::vector<UniformBlock> uniformBlocks;
			std::vector<ShaderStorageBuffer> ssbos;

			// Constructors / destructor
			Program();
			~Program();
			Program(const Program&) = delete;
			Program(Program&&) = delete;
			Program& operator=(const Program&) = delete;
			Program& operator=(Program&&) = delete;

			// Getters
			unsigned int getId() const;
			std::vector<Attribute> getAttributes() const;
			std::vector<Uniform> getUniforms() const;
			std::vector<ShaderStorageBuffer> getSSBOs() const;

			// Functions
			bool isLinked() const;
			bool link(const std::initializer_list<unsigned int>& shaderIds);
			bool link(const std::initializer_list<Shader*>& shaders);
			void bind() const;
			void reset();
			void updateProperties();
			void updateAttributes();
			void updateUniforms();
			void updateUniformBlocks();
			void updateSSBOs();

			// Functions | Uniform
			int getUniformLocation(const std::string& uniformName) const;

			void setUniform(int location, int value) const;
			void setUniform(int location, unsigned int value) const;
			void setUniform(int location, float value) const;
			void setUniform(int location, const glm::ivec2& value) const;
			void setUniform(int location, const glm::uvec2& value) const;
			void setUniform(int location, const glm::vec2& value) const;
			void setUniform(int location, const glm::ivec3& value) const;
			void setUniform(int location, const glm::uvec3& value) const;
			void setUniform(int location, const glm::vec3& value) const;
			void setUniform(int location, const glm::ivec4& value) const;
			void setUniform(int location, const glm::uvec4& value) const;
			void setUniform(int location, const glm::vec4& value) const;

			void setUniform(int location, int count, int data[]) const;
			void setUniform(int location, int count, glm::ivec2 data[]) const;
			void setUniform(int location, int count, glm::ivec3 data[]) const;
			void setUniform(int location, int count, glm::ivec4 data[]) const;
			void setUniform(int location, int count, unsigned int data[]) const;
			void setUniform(int location, int count, glm::uvec2 data[]) const;
			void setUniform(int location, int count, glm::uvec3 data[]) const;
			void setUniform(int location, int count, glm::uvec4 data[]) const;
			void setUniform(int location, int count, float data[]) const;
			void setUniform(int location, int count, glm::vec2 data[]) const;
			void setUniform(int location, int count, glm::vec3 data[]) const;
			void setUniform(int location, int count, glm::vec4 data[]) const;

			void setUniform(int location, int count, bool transpose, glm::mat2 data[]) const;
			void setUniform(int location, int count, bool transpose, glm::mat2x3 data[]) const;
			void setUniform(int location, int count, bool transpose, glm::mat2x4 data[]) const;
			void setUniform(int location, int count, bool transpose, glm::mat3 data[]) const;
			void setUniform(int location, int count, bool transpose, glm::mat3x2 data[]) const;
			void setUniform(int location, int count, bool transpose, glm::mat3x4 data[]) const;
			void setUniform(int location, int count, bool transpose, glm::mat4 data[]) const;
			void setUniform(int location, int count, bool transpose, glm::mat4x2 data[]) const;
			void setUniform(int location, int count, bool transpose, glm::mat4x3 data[]) const;

			void setProgramUniform(int location, int value) const;
			void setProgramUniform(int location, unsigned int value) const;
			void setProgramUniform(int location, float value) const;
			void setProgramUniform(int location, const glm::ivec2& value) const;
			void setProgramUniform(int location, const glm::uvec2& value) const;
			void setProgramUniform(int location, const glm::vec2& value) const;
			void setProgramUniform(int location, const glm::ivec3& value) const;
			void setProgramUniform(int location, const glm::uvec3& value) const;
			void setProgramUniform(int location, const glm::vec3& value) const;
			void setProgramUniform(int location, const glm::ivec4& value) const;
			void setProgramUniform(int location, const glm::uvec4& value) const;
			void setProgramUniform(int location, const glm::vec4& value) const;

			void setProgramUniform(int location, int count, int data[]) const;
			void setProgramUniform(int location, int count, glm::ivec2 data[]) const;
			void setProgramUniform(int location, int count, glm::ivec3 data[]) const;
			void setProgramUniform(int location, int count, glm::ivec4 data[]) const;
			void setProgramUniform(int location, int count, unsigned int data[]) const;
			void setProgramUniform(int location, int count, glm::uvec2 data[]) const;
			void setProgramUniform(int location, int count, glm::uvec3 data[]) const;
			void setProgramUniform(int location, int count, glm::uvec4 data[]) const;
			void setProgramUniform(int location, int count, float data[]) const;
			void setProgramUniform(int location, int count, glm::vec2 data[]) const;
			void setProgramUniform(int location, int count, glm::vec3 data[]) const;
			void setProgramUniform(int location, int count, glm::vec4 data[]) const;

			void setProgramUniform(int location, int count, bool transpose, glm::mat2 data[]) const;
			void setProgramUniform(int location, int count, bool transpose, glm::mat2x3 data[]) const;
			void setProgramUniform(int location, int count, bool transpose, glm::mat2x4 data[]) const;
			void setProgramUniform(int location, int count, bool transpose, glm::mat3 data[]) const;
			void setProgramUniform(int location, int count, bool transpose, glm::mat3x2 data[]) const;
			void setProgramUniform(int location, int count, bool transpose, glm::mat3x4 data[]) const;
			void setProgramUniform(int location, int count, bool transpose, glm::mat4 data[]) const;
			void setProgramUniform(int location, int count, bool transpose, glm::mat4x2 data[]) const;
			void setProgramUniform(int location, int count, bool transpose, glm::mat4x3 data[]) const;

			// Function | Attribute
			void enableAttribute(unsigned int index) const;
			void disableAttribute(unsigned int index) const;
			void enableAttributes() const;
			void disableAttributes() const;

			void setAttributeFormat(unsigned int attributeLocation, int elementCount, DataType dataType, bool normalized, unsigned int relativeOffset) const;
			void setAttributeIFormat(unsigned int attributeLocation, int elementCount, DataType dataType, unsigned int relativeOffset) const;
			void setAttributeLFormat(unsigned int attributeLocation, int elementCount, DataType dataType, unsigned int relativeOffset) const;
			void autoSetAttributeFormat();

			void setAttributeBinding(unsigned int attributeLocation, unsigned int bindingIndex) const;
			void autoSetAttributeBinding(unsigned int bindingIndex) const;
	};
}