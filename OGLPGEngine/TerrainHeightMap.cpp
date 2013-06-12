//TerrainHeightMap.cpp
#include "TerrainHeightMap.h"
#include "Mesh.h"
#include "VertexDeclarations.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Texture2D.h"

TerrainHeightMap::TerrainHeightMap()
{

}
TerrainHeightMap::~TerrainHeightMap()
{

}

Mesh* TerrainHeightMap::CreateHeightMap(Texture2D* heightMap)
{
	_terrainWidth = heightMap->GetWidth();
	_terrainHeight = heightMap->GetWidth();
	int numberOfVertices = _terrainWidth * _terrainHeight;
	int numberOfIndices = (_terrainWidth - 1) * (_terrainHeight - 1) * 6;

	std::vector<Color> imageData = heightMap->GetImageData();

	std::vector<std::vector<float>> heightData;
	heightData.resize(_terrainWidth);
	for(int i = 0; i < _terrainWidth; i++)
	{
		heightData[i].resize(_terrainHeight);
	}
	for(int x = 0; x < _terrainWidth; x++)
	{
		for(int y = 0; y < _terrainHeight; y++)
		{
			heightData[x][y] = imageData[x + y * _terrainWidth]._r * 255.0f / 5;
		}
	}

	VertexPosNormTex* vertices = new VertexPosNormTex[numberOfVertices];
    for (int x = 0; x < _terrainWidth; x++)
    {
       for (int y = 0; y < _terrainHeight; y++)
       {
			vertices[x + y * _terrainWidth]._position = Vector3((float)x, heightData[x][y], (float)y);
			vertices[x + y * _terrainWidth]._normal = Vector3::Zero();
			vertices[x + y * _terrainWidth]._texCoord = Vector2(((float)x / 30.0f), ((float)y / 30.0f));
       }
    }

	GLushort* indices = new GLushort[numberOfIndices];
    int counter = 0;
    for (int y = 0; y < _terrainHeight - 1; y++)
    {
        for (int x = 0; x < _terrainWidth - 1; x++)
        {
            int lowerLeft = x + y*_terrainWidth;
            int lowerRight = (x + 1) + y*_terrainWidth;
            int topLeft = x + (y + 1) * _terrainWidth;
            int topRight = (x + 1) + (y + 1) * _terrainWidth;
 
            indices[counter++] = topLeft;
            indices[counter++] = lowerRight;
            indices[counter++] = lowerLeft;

			indices[counter++] = topLeft;
            indices[counter++] = topRight;
            indices[counter++] = lowerRight;
        }
    }

	//Calculate the normals for each triangle
	for(int i = 0; i < numberOfIndices / 3; i++)
	{
		int index1 = indices[i * 3];
		int index2 = indices[i * 3 + 1];
		int index3 = indices[i * 3 + 2];

		Vector3 side1 = vertices[index1]._position - vertices[index3]._position;
		Vector3 side2 = vertices[index1]._position - vertices[index2]._position;
		Vector3 normal = Vector3::Cross(side1, side2);

		vertices[index1]._normal += normal;
		vertices[index2]._normal += normal;
		vertices[index3]._normal += normal;
	}
	//Normalize all the normals
	for(int i = 0; i < numberOfVertices; i ++)
	{
		vertices[i]._normal.Normalize();
	}

	VertexBuffer* vertexBuffer = new VertexBuffer(numberOfVertices, vertices);
	vertexBuffer->AddVertexAttributeInformation(0,3,GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), 0);
	vertexBuffer->AddVertexAttributeInformation(1,3,GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), sizeof(Vector3));
	vertexBuffer->AddVertexAttributeInformation(2,2,GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), sizeof(Vector3) * 2);
	IndexBuffer* indexBuffer = new IndexBuffer(numberOfIndices, indices);

	Mesh* newMesh = new Mesh(vertexBuffer,indexBuffer);

	return newMesh;
}
