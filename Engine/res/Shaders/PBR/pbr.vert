//Default Vertex Shader
#version 450 

layout(binding = 0, std140) uniform CameraUniformBuffer {
    mat4 viewProjectionMatrix;
    vec4 position;
    vec2 viewportSize;
} camera;

layout(binding = 1, std140) uniform ModelUniformBuffer {
    mat4 modelMatrix;
} model;

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec2 UV;

layout(location = 0) out vec3 v_Position;
layout(location = 1) out vec4 v_Color;
layout(location = 2) out vec3 v_Normal;
layout(location = 3) out vec2 v_UV;

void main() {
    gl_Position = camera.viewProjectionMatrix * model.modelMatrix * Position;
    v_Position = vec3(gl_Position);
    v_Color = Color;
    v_Normal = Normal;
    v_UV = UV;
}