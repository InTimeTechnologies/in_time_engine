#version 460 core

// Int
layout (location = 0) in vec4 outVertVarColor;

// Out
layout(location = 0) out vec4 finalColor;

void main() {
	finalColor = outVertVarColor;
}
