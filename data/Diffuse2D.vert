#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 worldMatrix;
uniform mat4 projectionMatrix;

out vec2 texCoordOut;

void main()
{
    gl_Position = projectionMatrix * worldMatrix * vec4(position, 1.0);
    texCoordOut = texCoord;
}