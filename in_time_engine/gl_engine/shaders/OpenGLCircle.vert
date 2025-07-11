#version 460 core

// In
layout(location = 0) in int transformIndex;
layout(location = 1) in float size;
layout(location = 2) in vec3 offset;
layout(location = 3) in vec4 color;

// Uniforms
layout(location = 0) uniform mat4 uProjectionView;

// Uniform blocks
layout(std140, binding = 0) uniform TranslationBlock {
    vec3 translation0;
    vec3 translation1;
} translationBlock;

// Shader storage buffers
layout(std430, binding = 0) buffer TransformBlock {
    mat4 transforms[];
} transformBlock;

// Out
layout(location = 0) out vec4 outColor;

// Declare gl_PerVertex block
out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
};


void main() {
    mat4 selectedMatrix = transformBlock.transforms[transformIndex];
    gl_Position = uProjectionView * selectedMatrix * vec4(offset + translationBlock.translation0 + translationBlock.translation1, 1.0);
    gl_PointSize = size;
    outColor = color;
}
