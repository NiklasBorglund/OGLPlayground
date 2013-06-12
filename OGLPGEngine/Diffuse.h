//Diffuse.h
#ifndef DIFFUSE_H_INCLUDED
#define DIFFUSE_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

#include "Material.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "Camera.h"
#include "Texture2D.h"

class Diffuse: public Material
{
public:
	Diffuse(ShaderProgram* shaderProgram, Texture2D* diffuseTexture): Material(shaderProgram),
		_isStarted(false), _worldMatrixID(0), _viewMatrixID(0), _projectionMatrixID(0), _diffuseTextureID(0),_lightDirectionID(0),
		_diffuseTexture(diffuseTexture)
	{}
	virtual ~Diffuse(){}

	virtual void Initialize()
	{
		const ShaderProgram* program = GetShaderProgram();
		_worldMatrixID = glGetUniformLocation(program->GetProgram(), "worldMatrix");
		_viewMatrixID = glGetUniformLocation(program->GetProgram(), "viewMatrix");
		_projectionMatrixID = glGetUniformLocation(program->GetProgram(), "projectionMatrix");
		_lightDirectionID = glGetUniformLocation(program->GetProgram(), "lightDirection");
		_diffuseTextureID = glGetUniformLocation(program->GetProgram(), "diffuseTexture");
	}
	virtual void Start()
	{
		if(!_isStarted)
		{
			glUseProgram(GetShaderProgram()->GetProgram());
			_isStarted = true;

			//Lights - Hardcoded for now
			_lightDirection._y = -1.0f;
			_lightDirection._z = 0.3f;
			_lightDirection.Normalize();
		}
	}
	virtual void SetUniforms(Camera* thisCamera)
	{
		if(_isStarted)
		{
			glUniformMatrix4fv(_viewMatrixID,1 , GL_FALSE, thisCamera->GetViewMatrix().Pointer());
			glUniformMatrix4fv(_projectionMatrixID,1 , GL_FALSE, thisCamera->GetProjectionMatrix().Pointer());

			glUniform3fv(_lightDirectionID, 1, _lightDirection.Pointer());

			//Texture
			glActiveTexture( GL_TEXTURE0 );
			glBindTexture(GL_TEXTURE_2D, _diffuseTexture->GetTexture());
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
	GLuint _viewMatrixID;
	GLuint _projectionMatrixID;
	GLuint _diffuseTextureID;
	GLuint _lightDirectionID;
	Texture2D* _diffuseTexture;
	Vector3 _lightDirection; 
};
#endif //DIFFUSE_H_INCLUDED