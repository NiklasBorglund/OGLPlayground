//TerrainCDLOD.h
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#ifndef TERRAINCDLOD_H_INCLUDED
#define TERRAINCDLOD_H_INCLUDED

#include "CDLODSettings.h"
#include "CDLODQuadTree.h"
#include "CDLODSelection.h"

class Camera;
class Texture2D;
class TerrainCDLOD
{
public:
	TerrainCDLOD(Camera* cameraComponent, Texture2D* heightMap, int renderGridResolution = 4);
	~TerrainCDLOD();

	void SelectLOD();
	CDLODSelection& GetSelection();

	int GetGridResolution()const;

	const CreateDescription& GetCreateDescription()const;

private:
	CreateDescription _createDescription;
	CDLODQuadTree _quadTree;
	CDLODSelection _selection;
	Texture2D* _heightMap;
};
#endif //TERRAINCDLOD_H_INCLUDED