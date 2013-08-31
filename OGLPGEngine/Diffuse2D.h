//Diffuse2D.h
#ifndef DIFFUSE2D_H_INCLUDED
#define DIFFUSE2D_H_INCLUDED

#include "Material.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "Camera.h"
#include "Texture2D.h"
#include "GraphicsDevice.h"

class Diffuse2D: public Material
{
public:
	Diffuse2D(ShaderProgram* shaderProgram, Texture2D* diffuseTexture): Material(shaderProgram),
		_isStarted(false), _worldMatrixID(0), _projectionMatrixID(0), _diffuseTextureID(0),
		_diffuseTexture(diffuseTexture)
	{}
	virtual ~Diffuse2D(){}

	virtual void Initialize(GraphicsDevice* graphicsDevice)
	{
		const ShaderProgram* program = GetShaderProgram();
		_worldMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "worldMatrix");
		_projectionMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "projectionMatrix");
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
	virtual void SetUniforms(GraphicsDevice* graphicsDevice, Camera* thisCamera)
	{
		if(_isStarted)
		{
			graphicsDevice->SetUniform(_projectionMatrixID,false, thisCamera->GetProjectionMatrix());

			//Texture
			graphicsDevice->SetActiveTexture(0);
			graphicsDevice->BindTexture(TextureType::Texture2D(), _diffuseTexture->GetTexture());
			graphicsDevice->SetUniform(_diffuseTextureID, 0);
		}
	}
	virtual void SetObjectUniforms(GraphicsDevice* graphicsDevice, GameObject* object)
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
	GLuint _diffuseTextureID;
	Texture2D* _diffuseTexture;
};
#endif //DIFFUSE2D_H_INCLUDED