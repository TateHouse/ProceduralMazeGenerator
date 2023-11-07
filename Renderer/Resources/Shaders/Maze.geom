#version 460 core

layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float wallThickness;
uniform float aspectRatio;

void main() {
    vec2 direction = normalize(gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy);
    vec2 normal = vec2(-direction.y, direction.x);
    vec2 scaledNormal = normal * wallThickness / 2.0f * vec2(1.0f, aspectRatio);

    gl_Position = gl_in[0].gl_Position + vec4(scaledNormal, 0.0f, 0.0f);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position - vec4(scaledNormal, 0.0f, 0.0f);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + vec4(scaledNormal, 0.0f, 0.0f);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position - vec4(scaledNormal, 0.0f, 0.0f);
    EmitVertex();

    EndPrimitive();
}