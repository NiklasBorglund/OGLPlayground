//FontMaterial.h
#ifndef FONTMATERIAL_H_INCLUDED
#define FONTMATERIAL_H_INCLUDED

#include "Material.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "GameObject.h"
#include "Color.h"
#include "GraphicsDevice.h"

class FontMaterial : public Material
{
public:
	FontMaterial(ShaderProgram* shaderProgram, Color color): Material(shaderProgram),
		_isStarted(false), _worldMatrixID(0), _projectionMatrixID(0),_colorID(0),_diffuseTextureID(0), _color(color)
	{}
	virtual ~FontMaterial(){}

	virtual void Initialize(GraphicsDevice* graphicsDevice)
	{
		const ShaderProgram* program = GetShaderProgram();
		_worldMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "worldMatrix");
		_projectionMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "projectionMatrix");
		_colorID = graphicsDevice->GetUniformLocation(program->GetProgram(), "color");
		_diffuseTextureID = graphicsDevice->GetUniformLocation(program->GetProgram(), "diffuseTexture");
	}
	virtual void Start(GraphicsDevice* graphicsDevice)
	{
		if(!_isStarted)
		{
			graphicsDevice->UseShader(GetShaderProgram()->GetProgram());
			_isStarted = true;
		}
	}
	virtual void SetUniforms(GraphicsDevice* graphicsDevice,Camera* thisCamera)
	{
		if(_isStarted)
		{
			graphicsDevice->SetUniform(_projectionMatrixID,false, thisCamera->GetProjectionMatrix());
			graphicsDevice->SetUniform(_colorID, _color);
			graphicsDevice->SetUniform(_diffuseTextureID, 0);
		}
	}
	virtual void SetObjectUniforms(GraphicsDevice* graphicsDevice,GameObject* object)
	{
		if(_isStarted)
		{
			graphicsDevice->SetUniform(_worldMatrixID,false, object->GetTransform().GetWorldMatrix());
		}
	}
	virtual void End(GraphicsDevice* graphicsDevice)
	{
		if(_isStarted)
		{
			graphicsDevice->UseShader(0);
			_isStarted = false;
		}
	}

private:
	bool _isStarted;
	GLuint _worldMatrixID;
	GLuint _projectionMatrixID;
	GLuint _colorID;
	GLuint _diffuseTextureID;
	Color _color;
};
#endif //FONTMATERIAL_H_INCLUDED