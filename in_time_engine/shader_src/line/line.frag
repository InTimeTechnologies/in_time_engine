#version 460 core

// in
layout(location = 0) in vec4 outVertVarColor;

// out
layout(location = 0) out vec4 finalColor;

void main() {
	finalColor = outVertVarColor;
}
