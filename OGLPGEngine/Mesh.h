//Mesh.h
#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <memory>

class IndexBuffer;
class VertexBuffer;
class Mesh
{
public:
	Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer);
	~Mesh();

	IndexBuffer* GetIndexBuffer();
	VertexBuffer* GetVertexBuffer();

private:
	std::unique_ptr<VertexBuffer> _vertexBuffer;
	std::unique_ptr<IndexBuffer> _indexBuffer;
};
#endif //MESH_H_INCLUDED