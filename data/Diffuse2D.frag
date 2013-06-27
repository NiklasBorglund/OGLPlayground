#version 330

in vec2 texCoordOut;

uniform sampler2D diffuseTexture;

out vec4 outputColor;

void main()
{
    outputColor = texture(diffuseTexture, texCoordOut);
}