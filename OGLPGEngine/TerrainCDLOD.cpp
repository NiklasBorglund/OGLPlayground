//TerrainCDLOD.cpp
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#include "TerrainCDLOD.h"
#include "Camera.h"
#include "Texture2D.h"
#include "HeightMapSourceImage.h"

TerrainCDLOD::TerrainCDLOD(Camera* cameraComponent, Texture2D* heightMap, int renderGridResolution): 
	_selection(4000, cameraComponent,1024,2.0f, 0.66f, true), _heightMap(heightMap)
{

	float heightMapWidth = (float)heightMap->GetWidth();
	float heightMapHeight = (float)heightMap->GetHeight();
	_createDescription._heightMap = new HeightMapSourceImage(heightMap);
	_createDescription._mapDimensions._min = Vector3(0,0,0);
	_createDescription._mapDimensions._size = Vector3(heightMapWidth, (256.0f * 0.2f), heightMapHeight);
	_createDescription._settings.SetDefault();
	_createDescription._settings._renderGridResolution = renderGridResolution;
	_selection.SetVisibilityDistance(sqrtf((heightMapWidth * heightMapWidth) + (heightMapHeight * heightMapHeight)));
	_selection.SetStopAtLevel(_createDescription._settings._levelCount);

	_selection.SetCreateDescription(&_createDescription);
	_quadTree.Create(_createDescription);
}
TerrainCDLOD::~TerrainCDLOD()
{
	if(_createDescription._heightMap != NULL)
	{
		delete _createDescription._heightMap;
	}
}
void TerrainCDLOD::SelectLOD()
{
	_selection.SetSelectionCount(0);
	_quadTree.Select(_selection);
}
CDLODSelection& TerrainCDLOD::GetSelection()
{
	return _selection;
}
int TerrainCDLOD::GetGridResolution()const
{
	return _createDescription._settings._renderGridResolution;
}
const CreateDescription& TerrainCDLOD::GetCreateDescription()const
{
	return _createDescription;
}