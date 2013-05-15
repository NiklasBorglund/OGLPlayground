//Mesh.cpp
#include "Mesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

Mesh::Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer): _vertexBuffer(vertexBuffer), _indexBuffer(indexBuffer)
{}
Mesh::~Mesh(){}

IndexBuffer* Mesh::GetIndexBuffer()
{
	return _indexBuffer.get();
}
VertexBuffer* Mesh::GetVertexBuffer()
{
	return _vertexBuffer.get();
}