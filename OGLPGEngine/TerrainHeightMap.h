//TerrainHeightMap.h
#ifndef TERRAINHEIGHTMAP_H_INCLUDED
#define TERRAINHEIGHTMAP_H_INCLUDED

#include <vector>

class Mesh;
class Texture2D;
class Vector3;
class TerrainHeightMap
{
public:
	TerrainHeightMap();
	~TerrainHeightMap();

	void Clear();
	void CreateHeightMap(Texture2D* heightMap, int patchSize);
	const std::vector<Mesh*>& GetTerrainMeshes();
	int GetNumberOfPatches()const;
private:
	int _terrainWidth;
	int _terrainHeight;
	int _numberOfPatches;
	int _patchWidth;
	int _patchHeight;
	int _totalTerrainVertices;
	int _totalTerrainIndices;
	std::vector<Mesh*> _terrainMeshes;

	Vector3 CalculateNormal(int x, int y, std::vector<std::vector<float>>& heightData);
	Vector3 GetNormalValue(const Vector3& point1, const Vector3& point2, const Vector3& center); 

};
#endif //TERRAINHEIGHTMAP_H_INCLUDED