#version 460 core

out vec4 fragColor;

uniform vec3 wallColor;

void main() {
    fragColor = vec4(wallColor, 1.0);
}