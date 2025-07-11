#version 450

void main() {
    gl_PointSize = 5.0;
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}

//C7531: global variable gl_VertexIndex requires "#extension GL_KHR_vulkan_glsl : enable" before use