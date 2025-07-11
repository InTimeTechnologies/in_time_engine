#version 460 core

// in
layout(location = 0) in int transformIndex;
layout(location = 1) in vec3 position;
layout(location = 2) in vec4 color;

// uniform
layout(location = 0) uniform mat4 uProjectionView;

// shader storage buffer
layout(std430, binding = 0) buffer ssboTransform {
	mat4 transforms[];
};

// out
layout(location = 0) out vec4 outColor;

void main() {
	gl_Position = uProjectionView * transforms[transformIndex] * vec4(position, 1.0);
	outColor = color;
}
