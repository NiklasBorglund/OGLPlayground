#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightDirection;

out vec2 texCoordOut;
out float lightingFactor;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(position, 1.0);
    texCoordOut = texCoord;
    
    vec3 newNormal = normalize(normal * mat3(worldMatrix));
    //light direction
    lightingFactor = clamp(dot(newNormal, lightDirection), 0.0, 1.0);
}