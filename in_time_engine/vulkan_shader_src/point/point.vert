#version 460 core

// in
layout(location = 0) in int transformIndex;
layout(location = 1) in float size;
layout(location = 2) in vec3 offset;
layout(location = 3) in vec4 color;

// uniform
layout(set = 0, binding = 0) uniform CameraData {
    mat4 projectionView;
} cameraData;

// shader storage buffer
layout(std430, binding = 0) buffer ssboTransform {
	mat4 transforms[];
};

// out
layout(location = 0) out vec4 outColor;

void main() {
	mat4 selectedMatrix = transforms[transformIndex];
	gl_Position = cameraData.projectionView * selectedMatrix * vec4(offset, 1.0);
	gl_PointSize = size;
	outColor = color;
}
