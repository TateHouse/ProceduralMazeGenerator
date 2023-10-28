#version 460 core

layout (location = 0) in vec3 inPosition;

uniform mat4 projection;
uniform float aspectRatio;

void main() {
    vec3 adjustedPosition = vec3(inPosition.x * aspectRatio, inPosition.y * aspectRatio, inPosition.z);
    gl_Position = projection * vec4(adjustedPosition, 1.0);
}