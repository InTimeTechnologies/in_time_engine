#version 460 core

// In
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

// Uniforms
layout(location = 0) uniform vec4 lightPosition; // Light position in eye coords.
layout(location = 1) uniform vec3 kd;            // Diffuse reflectivity
layout(location = 2) uniform vec3 ld;            // Diffuse light intensity

layout(location = 3) uniform mat4 modelViewMatrix;
layout(location = 4) uniform mat3 normalMatrix;
layout(location = 5) uniform mat4 projectionMatrix;
layout(location = 6) uniform mat4 mvp;

// Out
layout(location = 0) out vec3 outLightIntensity;

void main() {
    vec3 tnorm = normalize( normalMatrix * vertexNormal);
    vec4 eyeCoords = modelViewMatrix * vec4(vertexPosition,1.0);
    vec3 s = normalize(vec3(lightPosition - eyeCoords));

    outLightIntensity = ld * kd * max(dot( s, tnorm ), 0.0);

    gl_Position = mvp * vec4(vertexPosition,1.0);
}
