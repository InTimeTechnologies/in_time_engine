#pragma once

// Dependencies | glew
#include <glew/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

namespace gl {
	enum class ShaderType {
		NONE = -1,
		VERTEX = GL_VERTEX_SHADER,
		TESSELLATION_CONTROL = GL_TESS_CONTROL_SHADER,
		TESSELLATION_EVALUATION = GL_TESS_EVALUATION_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};
}
