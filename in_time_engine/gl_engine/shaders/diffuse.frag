#version 460 core

// In
layout(location = 0) in vec3 inLightIntensity;

// Out
layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(inLightIntensity, 1.0);
}
