#version 330

in vec2 texCoordOut;

uniform sampler2D diffuseTexture;
uniform vec4 color;

out vec4 outputColor;

void main()
{
    outputColor = vec4(1, 1, 1, texture2D(diffuseTexture, texCoordOut).r) * color;
    //outputColor = color;
}