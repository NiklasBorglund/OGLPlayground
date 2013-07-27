//Mesh.h
#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <string>
#include <memory>
#include "BoundingBox.h"

class IndexBuffer;
class VertexBuffer;
class Mesh
{
public:
	Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer);
	~Mesh();

	IndexBuffer* GetIndexBuffer();
	VertexBuffer* GetVertexBuffer();

	std::string GetDefaultDiffuseTextureName()const;
	void SetDefaultDiffuseTextureName(std::string defaultDiffuseTextureName);

	void SetBoundingBox(const BoundingBox& boundingBox);
	void SetBoundingBox(const Vector3& position, const Vector3& size);
	const BoundingBox& GetBoundingBox();

private:
	std::unique_ptr<VertexBuffer> _vertexBuffer;
	std::unique_ptr<IndexBuffer> _indexBuffer;
	std::string _defaultDiffuseTextureName;
	BoundingBox _boundingBox;
};
#endif //MESH_H_INCLUDED