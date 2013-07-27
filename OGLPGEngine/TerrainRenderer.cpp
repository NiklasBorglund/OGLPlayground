//TerrainRender.cpp
//Renders CDLOD Terrain
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf

#include "TerrainRenderer.h"
#include "TerrainCDLOD.h"
#include "TerrainMaterial.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

TerrainRenderer::TerrainRenderer(GameObject* owner, TerrainCDLOD* terrain,TerrainMaterial* terrainMaterial, ComponentUpdateStep componentUpdateStep): 
	Renderer(owner, componentUpdateStep), _terrain(terrain), _terrainMaterial(terrainMaterial)
{
	SetOriginalBoundingBox(Vector3(512, 512, 512), Vector3(512, 512, 512));

	//Create gridMeshes
	int dimension = 2;
	for(int i = 0; i < NumberOfGridMeshes; i++)
	{
		_gridMeshes[i].SetDimensions(dimension);
		dimension *= 2;
	}

	_debugColors.push_back(Color::Red());
	_debugColors.push_back(Color::Green());
	_debugColors.push_back(Color::Blue());
	_debugColors.push_back(Color::White());
	_debugColors.push_back(Color::Yellow());
}
TerrainRenderer::~TerrainRenderer(){}

void TerrainRenderer::PreDraw(Camera* currentCameraComponent)
{
	_terrainMaterial->Start();
	_terrainMaterial->SetUniforms(currentCameraComponent);

	int textureWidth = _terrain->GetCreateDescription()._heightMap->GetSizeX();
	int textureHeight = _terrain->GetCreateDescription()._heightMap->GetSizeY();

	//Set uniforms
	_quadWorldMax = Vector2(_terrain->GetCreateDescription()._mapDimensions.MaxX(), _terrain->GetCreateDescription()._mapDimensions.MaxZ());
	_terrainScale = Vector4(_terrain->GetCreateDescription()._mapDimensions._size._x,
							_terrain->GetCreateDescription()._mapDimensions._size._y,
							_terrain->GetCreateDescription()._mapDimensions._size._z, 0);
	_terrainOffset = Vector4(_terrain->GetCreateDescription()._mapDimensions._min._x,
							_terrain->GetCreateDescription()._mapDimensions._min._y,
							_terrain->GetCreateDescription()._mapDimensions._min._z, 0);
	_samplerWorldToTextureScale = Vector2((textureWidth-1.0f) / (float)textureWidth,
										(textureHeight-1.0f) / (float)textureHeight);
	_heightMapTextureInfo = Vector4((float)textureWidth,
									(float)textureHeight,
									1.0f / (float)textureWidth,
									1.0f / (float)textureHeight);

	glUniform2fv(_terrainMaterial->_quadWorldMaxID, 1, _quadWorldMax.Pointer());
	glUniform4fv(_terrainMaterial->_terrainScaleID, 1, _terrainScale.Pointer());
	glUniform4fv(_terrainMaterial->_terrainOffsetID, 1, _terrainOffset.Pointer());
	glUniform2fv(_terrainMaterial->_samplerWorldToTextureScaleID, 1, _samplerWorldToTextureScale.Pointer());
	glUniform4fv(_terrainMaterial->_heightMapTextureInfoID, 1, _heightMapTextureInfo.Pointer());

	_terrain->SelectLOD();
}
void TerrainRenderer::Update(GameTime* gameTime)
{
	//Pick a grid mesh
	int drawCalls = 0;
	int triangles = 0;
	const CDLODGridMesh* gridMesh = PickGridMesh(_terrain->GetCreateDescription()._settings.GetGridDimensions());
	if(gridMesh == NULL)
	{
		SetNumberOfDrawCalls(drawCalls);
		SetNumberOfTriangles(triangles);
		return;
	}

	VertexBuffer* vertexBuffer = gridMesh->GetVertexBuffer();
	IndexBuffer* indexBuffer = gridMesh->GetIndexBuffer();
	vertexBuffer->BindBuffer();
	indexBuffer->BindBuffer();
	_terrainMaterial->SetObjectUniforms(GetGameObject());

	unsigned int numberOfAttributeInformations = vertexBuffer->GetNumberOfAttributeInfos();
	for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
	{
		const VertexAttributeInformation& thisInfo = vertexBuffer->GetVertexAttributeInformation(i);
		glEnableVertexAttribArray(thisInfo.GetIndex());
		glVertexAttribPointer(thisInfo.GetIndex(), 
							  thisInfo.GetSize(), 
							  thisInfo.GetType(),
							  thisInfo.GetIsNormalized(), 
							  thisInfo.GetStride(), 
							  thisInfo.GetOffset());
	}

	CDLODSelectedNode* selectionBuffer = _terrain->GetSelection().GetSelectionBuffer();
	int selectionCount = _terrain->GetSelection().GetSelectionCount();
	int rasterSizeX = _terrain->GetCreateDescription()._heightMap->GetSizeX();
	int rasterSizeY = _terrain->GetCreateDescription()._heightMap->GetSizeY();
	const MapDimensions& mapDimensions = _terrain->GetCreateDescription()._mapDimensions;

	_gridDimensionValues = Vector3((float)gridMesh->GetDimensions(),
									(float)gridMesh->GetDimensions() * 0.5f, 
									2.0f / (float)gridMesh->GetDimensions());
	glUniform3fv(_terrainMaterial->_gridDimID, 1, _gridDimensionValues.Pointer());

	int prevMorphConstLevelSet = -1;
	Vector4 morphConsts;
	Vector4 quadScale;
	Vector4 quadOffset;
	for(int i = 0; i < selectionCount; i++)
	{
		const CDLODSelectedNode& selectedNode = selectionBuffer[i];

		if(prevMorphConstLevelSet != selectedNode._level)
		{
			prevMorphConstLevelSet = selectedNode._level;
			morphConsts = _terrain->GetSelection().GetMorphConsts(prevMorphConstLevelSet);
			glUniform4fv(_terrainMaterial->_morphConstsID, 1, morphConsts.Pointer());
		}

		BoundingBox boundingBox = selectedNode.GetBoundingBox(rasterSizeX, rasterSizeY, mapDimensions);
		Vector3 bbMin = boundingBox.Min();
		Vector3 bbMax = boundingBox.Max();

		quadScale = Vector4(boundingBox._halfSize._x * 2,
							(float)selectedNode._level,
							boundingBox._halfSize._z * 2,
							1);
		glUniform4fv(_terrainMaterial->_quadScaleID, 1, quadScale.Pointer());

		quadOffset = Vector4(bbMin._x,
							(bbMin._y + bbMax._y) * 0.5f,
							 bbMin._z,
							1);
		glUniform4fv(_terrainMaterial->_quadOffsetID, 1, quadOffset.Pointer());


		bool drawFull = selectedNode._topLeft && selectedNode._topRight && selectedNode._bottomLeft && selectedNode._bottomRight;

		int gridDim = gridMesh->GetDimensions();
		drawFull = true; //TEMP
		int totalIndices = indexBuffer->GetNumberOfElements();
		if(drawFull)
		{
			glDrawElements(GL_TRIANGLES,totalIndices, indexBuffer->GetIndexType(), (GLvoid*)0);
			drawCalls++;
			triangles += totalIndices / 3;
		}
		else
		{
			int halfd = gridMesh->GetNumberOfSubMeshIndices();

			if(selectedNode._topLeft)
			{
				glDrawElements(GL_TRIANGLES,halfd, indexBuffer->GetIndexType(), (GLvoid*)0);
				drawCalls++;
				triangles += halfd / 3;
			}
			if(selectedNode._topRight)
			{
				glDrawElements(GL_TRIANGLES,halfd, indexBuffer->GetIndexType(), (GLvoid*)gridMesh->GetEndIndexTopLeft());
				drawCalls++;
				triangles += halfd / 3;
			}
			if(selectedNode._bottomLeft)
			{
				glDrawElements(GL_TRIANGLES,halfd, indexBuffer->GetIndexType(), (GLvoid*)gridMesh->GetEndIndexTopRight());
				drawCalls++;
				triangles += halfd / 3;
			}
			if(selectedNode._bottomRight)
			{
				glDrawElements(GL_TRIANGLES,halfd, indexBuffer->GetIndexType(), (GLvoid*)gridMesh->GetEndIndexBottomLeft());
				drawCalls++;
				triangles += halfd / 3;
			}
		}
	}

	for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
	{
		glDisableVertexAttribArray(vertexBuffer->GetVertexAttributeInformation(i).GetIndex());
	}
	indexBuffer->UnbindBuffer();
	vertexBuffer->UnbindBuffer();
	SetNumberOfDrawCalls(drawCalls);
	SetNumberOfTriangles(triangles);
}
void TerrainRenderer::PostDraw()
{
	_terrainMaterial->End();
}
void TerrainRenderer::GetDebugBoundingBoxes(std::vector<DebugBoundingBox>& boxArray)
{
	CDLODSelectedNode* selectionBuffer = _terrain->GetSelection().GetSelectionBuffer();
	int selectionCount = _terrain->GetSelection().GetSelectionCount();
	int rasterSizeX = _terrain->GetCreateDescription()._heightMap->GetSizeX();
	int rasterSizeY = _terrain->GetCreateDescription()._heightMap->GetSizeY();
	const MapDimensions& mapDimensions = _terrain->GetCreateDescription()._mapDimensions;

	for(int i = 0; i < selectionCount; i++)
	{
		BoundingBox boundingBox = selectionBuffer[i].GetBoundingBox(rasterSizeX, rasterSizeY, mapDimensions);
		Color color;
		unsigned int level = selectionBuffer[i]._level;
		unsigned int colorArraySize = _debugColors.size() - 1;
		if(level >= _debugColors.size())
		{
			level = colorArraySize % level;
		}
		color = _debugColors[level];

		boxArray.push_back(DebugBoundingBox(boundingBox, color));
	}
}

const CDLODGridMesh* TerrainRenderer::PickGridMesh(int dimensions)const
{
	for(int i = 0; i < NumberOfGridMeshes; i++)
	{
		if(_gridMeshes[i].GetDimensions() == dimensions)
		{
			return &_gridMeshes[i];
		}
	}
	return NULL;
}
