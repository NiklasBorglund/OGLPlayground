//Diffuse2D.h
#ifndef DIFFUSE2D_H_INCLUDED
#define DIFFUSE2D_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

#include "Material.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "Camera.h"
#include "Texture2D.h"

class Diffuse2D: public Material
{
public:
	Diffuse2D(ShaderProgram* shaderProgram, Texture2D* diffuseTexture): Material(shaderProgram),
		_isStarted(false), _worldMatrixID(0), _projectionMatrixID(0), _diffuseTextureID(0),
		_diffuseTexture(diffuseTexture)
	{}
	virtual ~Diffuse2D(){}

	virtual void Initialize()
	{
		const ShaderProgram* program = GetShaderProgram();
		_worldMatrixID = glGetUniformLocation(program->GetProgram(), "worldMatrix");
		_projectionMatrixID = glGetUniformLocation(program->GetProgram(), "projectionMatrix");
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
	GLuint _projectionMatrixID;
	GLuint _diffuseTextureID;
	Texture2D* _diffuseTexture;
};
#endif //DIFFUSE2D_H_INCLUDED