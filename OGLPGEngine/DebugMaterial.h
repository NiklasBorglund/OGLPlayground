//DebugMaterial.h
#ifndef DEBUGMATERIAL_H_INCLUDED
#define DEBUGMATERIAL_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

#include "Material.h"
#include "ShaderProgram.h."
#include "Camera.h"
#include "GameObject.h"
#include "Color.h"

class DebugMaterial: public Material
{
public:
	DebugMaterial(ShaderProgram* shaderProgram): Material(shaderProgram),
		_isStarted(false), _worldMatrixID(0), _viewMatrixID(0), _projectionMatrixID(0), _colorID(0), _color(Color::White())
	{}
	virtual ~DebugMaterial(){}

	virtual void Initialize()
	{
		const ShaderProgram* program = GetShaderProgram();
		_worldMatrixID = glGetUniformLocation(program->GetProgram(), "worldMatrix");
		_viewMatrixID = glGetUniformLocation(program->GetProgram(), "viewMatrix");
		_projectionMatrixID = glGetUniformLocation(program->GetProgram(), "projectionMatrix");
		_colorID = glGetUniformLocation(program->GetProgram(), "color");
	}
	virtual void Start()
	{
		if(!_isStarted)
		{
			glUseProgram(GetShaderProgram()->GetProgram());
			_isStarted = true;
		}
	}
	virtual void SetUniforms(Camera* thisCamera)
	{
		if(_isStarted)
		{
			glUniformMatrix4fv(_projectionMatrixID,1 , GL_FALSE, thisCamera->GetProjectionMatrix().Pointer());
			glUniformMatrix4fv(_viewMatrixID, 1 , GL_FALSE, thisCamera->GetViewMatrix().Pointer());
		}
	}
	virtual void SetObjectUniforms(GameObject* object)
	{
		if(_isStarted)
		{
			glUniform4fv(_colorID, 1, _color.Pointer()); //want to be able to change color per object
			glUniformMatrix4fv(_worldMatrixID,1 , GL_FALSE, object->GetTransform().GetWorldMatrix().Pointer());
		}
	}
	virtual void End()
	{
		if(_isStarted)
		{
			glUseProgram(0);
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