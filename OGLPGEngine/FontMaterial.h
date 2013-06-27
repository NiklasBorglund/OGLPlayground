//FontMaterial.h
#ifndef FONTMATERIAL_H_INCLUDED
#define FONTMATERIAL_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

#include "Material.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "GameObject.h"
#include "Color.h"

class FontMaterial : public Material
{
public:
	FontMaterial(ShaderProgram* shaderProgram, Color color): Material(shaderProgram),
		_isStarted(false), _worldMatrixID(0), _projectionMatrixID(0),_colorID(0),_diffuseTextureID(0), _color(color)
	{}
	virtual ~FontMaterial(){}

	virtual void Initialize()
	{
		const ShaderProgram* program = GetShaderProgram();
		_worldMatrixID = glGetUniformLocation(program->GetProgram(), "worldMatrix");
		_projectionMatrixID = glGetUniformLocation(program->GetProgram(), "projectionMatrix");
		_colorID = glGetUniformLocation(program->GetProgram(), "color");
		_diffuseTextureID = glGetUniformLocation(program->GetProgram(), "diffuseTexture");
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
			glUniform4fv(_colorID, 1, _color.Pointer());
			glUniform1i( _diffuseTextureID, 0 );
		}
	}
	virtual void SetObjectUniforms(GameObject* object)
	{
		if(_isStarted)
		{
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

private:
	bool _isStarted;
	GLuint _worldMatrixID;
	GLuint _projectionMatrixID;
	GLuint _colorID;
	GLuint _diffuseTextureID;
	Color _color;
};
#endif //FONTMATERIAL_H_INCLUDED