//Default fragment shader
#version 450

layout(binding = 0, std140) uniform CameraUniformBuffer {
    mat4 viewProjectionMatrix;
    vec4 position;
    vec2 viewportSize;
} camera;

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec4 v_Color;
layout(location = 2) in vec3 v_Normal;
layout(location = 3) in vec2 v_UV;

layout(location = 0) out vec4 frag_color;

void main(){

	frag_color = vec4(1.0, 0.0, 1.0, 1.0);
}
