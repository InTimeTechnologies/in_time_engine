#version 460 core

// In
layout(location = 0) in int transformIndex;
layout(location = 1) in vec3 position;
layout(location = 3) in vec4 color;

// Uniforms
layout(location = 0) uniform mat4 uProjectionView;

// Shader storage buffers
layout(std430, binding = 0) buffer ssboTransform {
	mat4 transforms[];
};

// Out
layout(location = 0) out vec4 outVertVarColor;

void main() {
	gl_Position = uProjectionView * transforms[transformIndex] * vec4(position, 1.0);
	outVertVarColor = color;
}
