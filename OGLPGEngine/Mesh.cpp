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
void Mesh::SetBoundingBox(const BoundingBox& boundingBox)
{
	_boundingBox = boundingBox;
}
void Mesh::SetBoundingBox(const Vector3& position, const Vector3& size)
{
	SetBoundingBox(BoundingBox(position, size));
}
const BoundingBox& Mesh::GetBoundingBox()
{
	return _boundingBox;
}