//CDLODGridMesh.h
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#ifndef CDLODGRIDMESH_H_INCLUDED
#define CDLODGRIDMESH_H_INCLUDED

#include <memory>

class VertexBuffer;
class IndexBuffer;
class CDLODGridMesh
{
public:
	CDLODGridMesh();
	~CDLODGridMesh();

	void SetDimensions(int dimension);
	int GetDimensions()const;

	VertexBuffer* GetVertexBuffer()const;
	IndexBuffer* GetIndexBuffer()const;
	int GetEndIndexTopLeft()const;
	int GetEndIndexTopRight()const;
	int GetEndIndexBottomLeft()const;
	int GetEndIndexBottomRight()const;
	int GetNumberOfSubMeshIndices()const;

private:
	std::unique_ptr<VertexBuffer> _vertexBuffer;
	std::unique_ptr<IndexBuffer> _indexBuffer;
	int _dimensions;
	int _endIndexTopLeft;
	int _endIndexTopRight;
	int _endIndexBottomLeft;
	int _endIndexBottomRight;
	int _numberOfSubmeshIndices;

	void CreateBuffers();
};

#endif //CDLODGRIDMESH_H_INCLUDED