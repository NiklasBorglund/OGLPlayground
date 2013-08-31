//Diffuse.h
#ifndef DIFFUSE_H_INCLUDED
#define DIFFUSE_H_INCLUDED

#include "Material.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "Camera.h"
#include "Texture2D.h"
#include "GraphicsDevice.h"

class Diffuse: public Material
{
public:
	Diffuse(ShaderProgram* shaderProgram, Texture2D* diffuseTexture): Material(shaderProgram),
		_isStarted(false), _worldMatrixID(0), _viewMatrixID(0), _projectionMatrixID(0), _diffuseTextureID(0),_lightDirectionID(0),
		_diffuseTexture(diffuseTexture)
	{}
	virtual ~Diffuse(){}

	virtual void Initialize(GraphicsDevice* graphicsDevice)
	{
		const ShaderProgram* program = GetShaderProgram();
		_worldMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "worldMatrix");
		_viewMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "viewMatrix");
		_projectionMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "projectionMatrix");
		_lightDirectionID = graphicsDevice->GetUniformLocation(program->GetProgram(), "lightDirection");
		_diffuseTextureID = graphicsDevice->GetUniformLocation(program->GetProgram(), "diffuseTexture");
	}
	virtual void Start(GraphicsDevice* graphicsDevice)
	{
		if(!_isStarted)
		{
			graphicsDevice->UseShader(GetShaderProgram()->GetProgram());
			_isStarted = true;

			//Lights - Hardcoded for now
			_lightDirection._y = -1.0f;
			_lightDirection._z = 0.3f;
			_lightDirection.Normalize();
		}
	}
	virtual void SetUniforms(GraphicsDevice* graphicsDevice,Camera* thisCamera)
	{
		if(_isStarted)
		{
			graphicsDevice->SetUniform(_projectionMatrixID,false, thisCamera->GetProjectionMatrix());
			graphicsDevice->SetUniform(_viewMatrixID,false, thisCamera->GetViewMatrix());

			graphicsDevice->SetUniform(_lightDirectionID, _lightDirection);

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
	GLuint _viewMatrixID;
	GLuint _projectionMatrixID;
	GLuint _diffuseTextureID;
	GLuint _lightDirectionID;
	Texture2D* _diffuseTexture;
	Vector3 _lightDirection; 
};
#endif //DIFFUSE_H_INCLUDED