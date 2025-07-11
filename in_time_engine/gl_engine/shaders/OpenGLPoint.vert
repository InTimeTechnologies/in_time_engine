#version 460 core

// In
layout(location = 0) in int transformIndex;
layout(location = 1) in float size;
layout(location = 2) in vec3 offset;
layout(location = 3) in vec4 color;

// Uniforms
layout(location = 0) uniform mat4 uProjectionView;

// Shader storage buffers
layout(std430, binding = 0) buffer ssboTransform {
	mat4 transforms[];
};

// Out
layout(location = 0) out vec4 outColor;

void main() {
	mat4 selectedMatrix = transforms[transformIndex];
	gl_Position = uProjectionView * selectedMatrix * vec4(offset, 1.0);
	gl_PointSize = size;
	outColor = color;
}
