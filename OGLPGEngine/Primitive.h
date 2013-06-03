//Primitive.h
#ifndef PRIMITIVE_H_INCLUDED
#define PRIMITIVE_H_INCLUDED

#include "Mesh.h"
#include "VertexDeclarations.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

//Just random texcoords and normals for now
const VertexPosNormTex vertexDataCubeColorless[] = 
{
	VertexPosNormTex(Vector3(-1.0f, -1.0f, -1.0f),Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f,0.0f)),
	VertexPosNormTex(Vector3(-1.0f, -1.0f,  1.0f),Vector3(-1.0f, -1.0f, -1.0f), Vector2(1.0f,0.0f)),
	VertexPosNormTex(Vector3(-1.0f,  1.0f, -1.0f),Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f,1.0f)),
	VertexPosNormTex(Vector3(-1.0f,  1.0f,  1.0f),Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f,1.0f)),
	VertexPosNormTex(Vector3( 1.0f, -1.0f, -1.0f),Vector3(-1.0f, -1.0f, -1.0f), Vector2(1.0f,0.0f)),
	VertexPosNormTex(Vector3( 1.0f, -1.0f,  1.0f),Vector3(-1.0f, -1.0f, -1.0f), Vector2(1.0f,0.0f)),
	VertexPosNormTex(Vector3( 1.0f,  1.0f, -1.0f),Vector3(-1.0f, -1.0f, -1.0f), Vector2(1.0f,1.0f)),
	VertexPosNormTex(Vector3( 1.0f,  1.0f,  1.0f),Vector3(-1.0f, -1.0f, -1.0f),Vector2(1.0f,1.0f)),
};

const unsigned int indices[] =
{
			0,1,2, // -x
			1,3,2,
			4,6,5, // +x
			5,6,7,
			0,5,1, // -y
			0,4,5,
			2,7,6, // +y
			2,3,7,
			0,6,4, // -z
			0,2,6,
			1,7,3, // +z
			1,5,7,
};

class Primitive
{
public:
	static Mesh* CreateCube()
	{
		VertexBuffer* vertexBuffer = new VertexBuffer(BufferType::ArrayBuffer(), BufferUsage::StaticDraw(),sizeof(VertexPosNormTex), sizeof(vertexDataCubeColorless) / sizeof(VertexPosNormTex), (GLvoid*)vertexDataCubeColorless);
		vertexBuffer->AddVertexAttributeInformation(0,3,GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), 0);
		vertexBuffer->AddVertexAttributeInformation(1,3,GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), sizeof(Vector3));
		vertexBuffer->AddVertexAttributeInformation(2,2,GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), sizeof(Vector3) * 2);
		IndexBuffer* indexBuffer = new IndexBuffer( sizeof(float), sizeof(indices) / sizeof(float),GLIndexDataType::UnsignedInt(), (GLvoid*)indices);

		//The mesh takes over the ownership of the buffers
		return new Mesh(vertexBuffer, indexBuffer);
	}

private:
	Primitive(){}
	~Primitive(){}
};
#endif //PRIMITIVE_H_INCLUDED