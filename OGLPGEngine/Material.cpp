//Material.cpp
#include "Material.h"
#include "ShaderProgram.h"
#include "GameObject.h"

Material::Material(ShaderProgram* shaderProgram): _shaderProgram(shaderProgram){}
Material::~Material(){}

void Material::SetObjectUniforms(GraphicsDevice* graphicsDevice, GameObject* object){}

const ShaderProgram* Material::GetShaderProgram()
{
	return _shaderProgram;
}