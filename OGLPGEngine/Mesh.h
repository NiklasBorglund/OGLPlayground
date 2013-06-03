//Mesh.h
#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <string>
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

	std::string GetDefaultDiffuseTextureName()const;
	void SetDefaultDiffuseTextureName(std::string defaultDiffuseTextureName);

private:
	std::unique_ptr<VertexBuffer> _vertexBuffer;
	std::unique_ptr<IndexBuffer> _indexBuffer;
	std::string _defaultDiffuseTextureName;
};
#endif //MESH_H_INCLUDED