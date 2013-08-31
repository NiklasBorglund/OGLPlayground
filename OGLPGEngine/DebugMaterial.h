//DebugMaterial.h
#ifndef DEBUGMATERIAL_H_INCLUDED
#define DEBUGMATERIAL_H_INCLUDED

#include "Material.h"
#include "ShaderProgram.h."
#include "Camera.h"
#include "GameObject.h"
#include "Color.h"
#include "GraphicsDevice.h"

class DebugMaterial: public Material
{
public:
	DebugMaterial(ShaderProgram* shaderProgram): Material(shaderProgram),
		_isStarted(false), _worldMatrixID(0), _viewMatrixID(0), _projectionMatrixID(0), _colorID(0), _color(Color::White())
	{}
	virtual ~DebugMaterial(){}

	virtual void Initialize(GraphicsDevice* graphicsDevice)
	{
		const ShaderProgram* program = GetShaderProgram();
		_worldMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "worldMatrix");
		_viewMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "viewMatrix");
		_projectionMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "projectionMatrix");
		_colorID = graphicsDevice->GetUniformLocation(program->GetProgram(), "color");
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
			graphicsDevice->SetUniform(_viewMatrixID,false, thisCamera->GetViewMatrix());
		}
	}
	virtual void SetObjectUniforms(GraphicsDevice* graphicsDevice,GameObject* object)
	{
		if(_isStarted)
		{
			graphicsDevice->SetUniform(_colorID, _color);
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

	void SetColor(const Color& color)
	{
		_color = color;
	}

private:
	bool _isStarted;
	GLuint _worldMatrixID;
	GLuint _viewMatrixID;
	GLuint _projectionMatrixID;
	GLuint _colorID;
	Color _color;
};
#endif //DEBUG_H_INCLUDED