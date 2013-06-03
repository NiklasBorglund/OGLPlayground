//Mesh.cpp
#include "Mesh.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

Mesh::Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer): _vertexBuffer(vertexBuffer), _indexBuffer(indexBuffer)
{}
Mesh::~Mesh(){}

std::string Mesh::GetDefaultDiffuseTextureName()const
{
	return _defaultDiffuseTextureName;
}
void Mesh::SetDefaultDiffuseTextureName(std::string defaultDiffuseTextureName)
{
	_defaultDiffuseTextureName = defaultDiffuseTextureName;
}

IndexBuffer* Mesh::GetIndexBuffer()
{
	return _indexBuffer.get();
}
VertexBuffer* Mesh::GetVertexBuffer()
{
	return _vertexBuffer.get();
}