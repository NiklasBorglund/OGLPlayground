//TerrainHeightMap.h
#ifndef TERRAINHEIGHTMAP_H_INCLUDED
#define TERRAINHEIGHTMAP_H_INCLUDED

class Mesh;
class Texture2D;
class TerrainHeightMap
{
public:
	TerrainHeightMap();
	~TerrainHeightMap();

	Mesh* CreateHeightMap(Texture2D* heightMap);

private:
	int _terrainWidth;
	int _terrainHeight;

};
#endif //TERRAINHEIGHTMAP_H_INCLUDED