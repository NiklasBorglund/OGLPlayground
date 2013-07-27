//TerrainMaterial.h
#ifndef TERRAINMATERIAL_H_INCLUDED
#define TERRAINMATERIAL_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

#include "Material.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Texture2D.h"

class TerrainMaterial : public Material
{
public:
	friend class TerrainRenderer;
	TerrainMaterial(ShaderProgram* shaderProgram, Texture2D* heightTexture) : Material(shaderProgram),
		_isStarted(false)
	{
		_viewMatrixID = 0;
		_projectionMatrixID = 0;
		_cameraPositionID = 0;
		_quadOffsetID = 0;
		_quadScaleID = 0;
		_quadWorldMaxID = 0;
		_gridDimID = 0;
		_terrainScaleID = 0;
		_terrainOffsetID = 0;
		_samplerWorldToTextureScaleID = 0;
		_heightMapTextureInfoID = 0;
		_lightDirectionID = 0;
		_morphConstsID = 0;
		_diffuseTextureID = 0;
		_heightTexture = heightTexture;
	}
	virtual ~TerrainMaterial(){}

	virtual void Initialize()
	{
		const ShaderProgram* program = GetShaderProgram();
		_viewMatrixID = glGetUniformLocation(program->GetProgram(), "viewMatrix");
		_projectionMatrixID = glGetUniformLocation(program->GetProgram(), "projectionMatrix");
		_cameraPositionID = glGetUniformLocation(program->GetProgram(), "cameraPosition");
		_quadOffsetID = glGetUniformLocation(program->GetProgram(), "quadOffset");
		_quadScaleID = glGetUniformLocation(program->GetProgram(), "quadScale");
		_quadWorldMaxID = glGetUniformLocation(program->GetProgram(), "quadWorldMax");
		_gridDimID = glGetUniformLocation(program->GetProgram(), "gridDim");
		_terrainScaleID = glGetUniformLocation(program->GetProgram(), "terrainScale");
		_terrainOffsetID = glGetUniformLocation(program->GetProgram(), "terrainOffset");
		_samplerWorldToTextureScaleID = glGetUniformLocation(program->GetProgram(), "samplerWorldToTextureScale");
		_heightMapTextureInfoID = glGetUniformLocation(program->GetProgram(), "heightMapTextureInfo");
		_lightDirectionID = glGetUniformLocation(program->GetProgram(), "lightDirection");
		_morphConstsID = glGetUniformLocation(program->GetProgram(), "morphConsts");
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
			glUniform3fv(_cameraPositionID,1, thisCamera->GetGameObject()->GetTransform().GetPosition().Pointer());

			glUniform3fv(_lightDirectionID, 1, _lightDirection.Pointer());

			//Texture
			glActiveTexture( GL_TEXTURE0 );
			glBindTexture(GL_TEXTURE_2D, _heightTexture->GetTexture());
			glUniform1i( _diffuseTextureID, 0 );
		}
	}
	virtual void SetObjectUniforms(GameObject* object)
	{
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
	GLuint _viewMatrixID;
	GLuint _projectionMatrixID;
	GLuint _cameraPositionID;
	GLuint _quadOffsetID;
	GLuint _quadScaleID;
	GLuint _quadWorldMaxID;
	GLuint _gridDimID;
	GLuint _terrainScaleID;
	GLuint _terrainOffsetID;
	GLuint _samplerWorldToTextureScaleID;
	GLuint _heightMapTextureInfoID;
	GLuint _lightDirectionID;
	GLuint _morphConstsID;
	GLuint _diffuseTextureID;

	Texture2D* _heightTexture;
	Vector3 _lightDirection; 
};
#endif //TERRAINMATERIAL_H_INCLUDED