#version 460 core

// In
layout(location = 0) in vec4 inColor;

// Out
layout(location = 0) out vec4 outColor;

void main() {
	outColor = inColor;
}
