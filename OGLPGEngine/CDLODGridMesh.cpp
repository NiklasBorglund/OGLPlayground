//CDLODGridMesh.cpp
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#include "CDLODGridMesh.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexDeclarations.h"

CDLODGridMesh::CDLODGridMesh(): _dimensions(0), _endIndexTopLeft(0), _endIndexTopRight(0), 
	_endIndexBottomLeft(0), _endIndexBottomRight(0), _numberOfSubmeshIndices(0)
{
}
CDLODGridMesh::~CDLODGridMesh()
{
}
void CDLODGridMesh::SetDimensions(int dimension)
{
	_dimensions = dimension;
	CreateBuffers();
}
int CDLODGridMesh::GetDimensions()const
{
	return _dimensions;
}
VertexBuffer* CDLODGridMesh::GetVertexBuffer()const
{
	return _vertexBuffer.get();
}
IndexBuffer* CDLODGridMesh::GetIndexBuffer()const
{
	return _indexBuffer.get();
}
int CDLODGridMesh::GetEndIndexTopLeft()const
{
	return _endIndexTopLeft;
}
int CDLODGridMesh::GetEndIndexTopRight()const
{
	return _endIndexTopRight;
}
int CDLODGridMesh::GetEndIndexBottomLeft()const
{
	return _endIndexBottomLeft;
}
int CDLODGridMesh::GetEndIndexBottomRight()const
{
	return _endIndexBottomRight;
}

void CDLODGridMesh::CreateBuffers()
{
	if(_dimensions <= 0)
	{
		return;
	}

	_endIndexTopLeft = 0;
	_endIndexTopRight = 0;
	_endIndexBottomLeft = 0;
	_endIndexBottomRight = 0;
	_numberOfSubmeshIndices = 0;

	const int gridDimension = _dimensions;
	int totalVertices = (gridDimension + 1) * (gridDimension + 1);
	int totalIndices = gridDimension * gridDimension * 2 * 3;

	VertexPosContainer* vertices = new VertexPosContainer(totalVertices);
	int vertexDimension = gridDimension + 1;
	for(int y = 0; y < vertexDimension; y++)
	{
		for(int x = 0; x < vertexDimension; x++)
		{
			//vertices->GetVertex(x + vertexDimension * y)._position = Vector3(x / (float)gridDimension, y / (float)gridDimension, 0);
			vertices->GetVertex(x + vertexDimension * y)._position = Vector3(x / (float)gridDimension, 0, y / (float)gridDimension);
		}
	}
	_vertexBuffer = std::unique_ptr<VertexBuffer>(new VertexBuffer(totalVertices, vertices, sizeof(VertexPos)));
	_vertexBuffer->AddVertexAttributeInformation(0,3,GL_FLOAT, GL_FALSE, vertices->GetVertexSize(), 0);

	GLuint* indices = new GLuint[totalIndices];
	int index = 0;
	int halfD = vertexDimension / 2;
	int fullD = gridDimension;

	_numberOfSubmeshIndices = halfD * (halfD * 6);

	//Top Left
	for(int y = 0; y < halfD;y++)
	{
		for(int x = 0; x < halfD; x++)
		{
			indices[index++] = (GLuint)(x + vertexDimension * y);
			indices[index++] = (GLuint)(x + vertexDimension * (y + 1));
			indices[index++] = (GLuint)((x + 1) + vertexDimension * y);
			indices[index++] = (GLuint)((x + 1) + vertexDimension * y);
			indices[index++] = (GLuint)(x + vertexDimension * (y + 1));
			indices[index++] = (GLuint)((x + 1) + vertexDimension * (y + 1));
		}
	}
	_endIndexTopLeft = index;

	//Top Right
	for(int y = 0; y < halfD;y++)
	{
		for(int x = halfD; x < fullD; x++)
		{
			indices[index++] = (GLuint)(x + vertexDimension * y);
			indices[index++] = (GLuint)(x + vertexDimension * (y + 1));
			indices[index++] = (GLuint)((x + 1) + vertexDimension * y);
			indices[index++] = (GLuint)((x + 1) + vertexDimension * y);
			indices[index++] = (GLuint)(x + vertexDimension * (y + 1));
			indices[index++] = (GLuint)((x + 1) + vertexDimension * (y + 1));
		}
	}
	_endIndexTopRight = index;

	//Bottom Left
	for(int y = halfD; y < fullD;y++)
	{
		for(int x = 0; x < halfD; x++)
		{
			indices[index++] = (GLuint)(x + vertexDimension * y);
			indices[index++] = (GLuint)(x + vertexDimension * (y + 1));
			indices[index++] = (GLuint)((x + 1) + vertexDimension * y);
			indices[index++] = (GLuint)((x + 1) + vertexDimension * y);
			indices[index++] = (GLuint)(x + vertexDimension * (y + 1));
			indices[index++] = (GLuint)((x + 1) + vertexDimension * (y + 1));
		}
	}
	_endIndexBottomLeft = index;

	//Bottom Right
	for(int y = halfD; y < fullD;y++)
	{
		for(int x = halfD; x < fullD; x++)
		{
			indices[index++] = (GLuint)(x + vertexDimension * y);
			indices[index++] = (GLuint)(x + vertexDimension * (y + 1));
			indices[index++] = (GLuint)((x + 1) + vertexDimension * y);
			indices[index++] = (GLuint)((x + 1) + vertexDimension * y);
			indices[index++] = (GLuint)(x + vertexDimension * (y + 1));
			indices[index++] = (GLuint)((x + 1) + vertexDimension * (y + 1));
		}
	}
	_endIndexBottomRight = index;

	//Create the indexBuffer
	_indexBuffer = std::unique_ptr<IndexBuffer>(new IndexBuffer(totalIndices, indices));
}

int CDLODGridMesh::GetNumberOfSubMeshIndices()const
{
	return _numberOfSubmeshIndices;
}
