//TerrainRenderer.h
//Renders CDLOD Terrain
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#ifndef TERRAINRENDERER_H_INCLUDED
#define TERRAINRENDERER_H_INCLUDED

#include "Renderer.h"
#include "Vector2.h"
#include "Vector4.h"
#include "CDLODGridMesh.h"

class TerrainCDLOD;
class TerrainMaterial;
class TerrainRenderer: public Renderer
{
public:
	TerrainRenderer(GameObject* owner, TerrainCDLOD* terrain, TerrainMaterial* terrainMaterial, ComponentUpdateStep componentUpdateStep = ComponentUpdateStep::RenderUpdate());
	virtual ~TerrainRenderer();

	virtual void PreDraw(Camera* currentCameraComponent);
	virtual void Update(GameTime* gameTime); //<---Draw
	virtual void PostDraw();
	virtual void GetDebugBoundingBoxes(std::vector<DebugBoundingBox>& boxArray);

private:
	static const int NumberOfGridMeshes = 7;
	TerrainCDLOD* _terrain;
	TerrainMaterial* _terrainMaterial;
	Vector2 _quadWorldMax;
	Vector4 _terrainScale;
	Vector4 _terrainOffset;
	Vector2 _samplerWorldToTextureScale;
	Vector4 _heightMapTextureInfo;
	CDLODGridMesh _gridMeshes[NumberOfGridMeshes];
	int _gridDimensions;
	Vector3 _gridDimensionValues;
	std::vector<Color> _debugColors;

	const CDLODGridMesh* PickGridMesh(int dimensions)const;

};
#endif //TERRAINRENDERER_H_INCLUDED