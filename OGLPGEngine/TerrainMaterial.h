//TerrainMaterial.h
#ifndef TERRAINMATERIAL_H_INCLUDED
#define TERRAINMATERIAL_H_INCLUDED

#include "Material.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Texture2D.h"
#include "GraphicsDevice.h"

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

	virtual void Initialize(GraphicsDevice* graphicsDevice)
	{
		const ShaderProgram* program = GetShaderProgram();
		_viewMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "viewMatrix");
		_projectionMatrixID = graphicsDevice->GetUniformLocation(program->GetProgram(), "projectionMatrix");
		_cameraPositionID = graphicsDevice->GetUniformLocation(program->GetProgram(), "cameraPosition");
		_quadOffsetID = graphicsDevice->GetUniformLocation(program->GetProgram(), "quadOffset");
		_quadScaleID = graphicsDevice->GetUniformLocation(program->GetProgram(), "quadScale");
		_quadWorldMaxID = graphicsDevice->GetUniformLocation(program->GetProgram(), "quadWorldMax");
		_gridDimID = graphicsDevice->GetUniformLocation(program->GetProgram(), "gridDim");
		_terrainScaleID = graphicsDevice->GetUniformLocation(program->GetProgram(), "terrainScale");
		_terrainOffsetID = graphicsDevice->GetUniformLocation(program->GetProgram(), "terrainOffset");
		_samplerWorldToTextureScaleID = graphicsDevice->GetUniformLocation(program->GetProgram(), "samplerWorldToTextureScale");
		_heightMapTextureInfoID = graphicsDevice->GetUniformLocation(program->GetProgram(), "heightMapTextureInfo");
		_lightDirectionID = graphicsDevice->GetUniformLocation(program->GetProgram(), "lightDirection");
		_morphConstsID = graphicsDevice->GetUniformLocation(program->GetProgram(), "morphConsts");
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
	virtual void SetUniforms(GraphicsDevice* graphicsDevice, Camera* thisCamera)
	{
		if(_isStarted)
		{
			graphicsDevice->SetUniform(_projectionMatrixID,false, thisCamera->GetProjectionMatrix());
			graphicsDevice->SetUniform(_viewMatrixID,false, thisCamera->GetViewMatrix());
			graphicsDevice->SetUniform(_cameraPositionID, thisCamera->GetGameObject()->GetTransform().GetPosition());

			graphicsDevice->SetUniform(_lightDirectionID, _lightDirection);

			//Texture
			graphicsDevice->SetActiveTexture(0);
			graphicsDevice->BindTexture(TextureType::Texture2D(), _heightTexture->GetTexture());
			graphicsDevice->SetUniform(_diffuseTextureID, 0);
		}
	}
	virtual void SetObjectUniforms(GraphicsDevice* graphicsDevice, GameObject* object)
	{
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