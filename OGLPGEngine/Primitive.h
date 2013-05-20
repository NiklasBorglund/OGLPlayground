//Primitive.h
#ifndef PRIMITIVE_H_INCLUDED
#define PRIMITIVE_H_INCLUDED

#include "Mesh.h"
#include "VertexDeclarations.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

const VertexPosTex vertexDataCubeColorless[] = 
{
	VertexPosTex(Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f,0.0f)),
	VertexPosTex(Vector3(-1.0f, -1.0f,  1.0f), Vector2(1.0f,0.0f)),
	VertexPosTex(Vector3(-1.0f,  1.0f, -1.0f), Vector2(0.0f,1.0f)),
	VertexPosTex(Vector3(-1.0f,  1.0f,  1.0f), Vector2(0.0f,1.0f)),
	VertexPosTex(Vector3( 1.0f, -1.0f, -1.0f), Vector2(1.0f,0.0f)),
	VertexPosTex(Vector3( 1.0f, -1.0f,  1.0f), Vector2(1.0f,0.0f)),
	VertexPosTex(Vector3( 1.0f,  1.0f, -1.0f), Vector2(1.0f,1.0f)),
	VertexPosTex(Vector3( 1.0f,  1.0f,  1.0f), Vector2(1.0f,1.0f)),
};


const unsigned int indices[] =
{
			0,2,1, // -x
			1,2,3,
			4,5,6, // +x
			5,7,6,
			0,1,5, // -y
			0,5,4,
			2,6,7, // +y
			2,7,3,
			0,4,6, // -z
			0,6,2,
			1,3,7, // +z
			1,7,5,
};

class Primitive
{
public:
	static Mesh* CreateCube()
	{
		VertexBuffer* vertexBuffer = new VertexBuffer(BufferType::ArrayBuffer(), BufferUsage::StaticDraw(),sizeof(VertexPosTex), sizeof(vertexDataCubeColorless) / sizeof(VertexPosTex), (GLvoid*)vertexDataCubeColorless);
		vertexBuffer->AddVertexAttributeInformation(0,3,GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), 0);
		vertexBuffer->AddVertexAttributeInformation(1,2,GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), sizeof(Vector3));
		IndexBuffer* indexBuffer = new IndexBuffer( sizeof(float), sizeof(indices) / sizeof(float),GLIndexDataType::UnsignedInt(), (GLvoid*)indices);

		//The mesh takes over the ownership of the buffers
		return new Mesh(vertexBuffer, indexBuffer);
	}

private:
	Primitive(){}
	~Primitive(){}
};
#endif //PRIMITIVE_H_INCLUDED