//main.cpp

#include "GameManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "Diffuse.h"
#include "RotateObject.h"
#include "MeshRenderer.h"
#include <memory>

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

int main()
{
	GameManager newManager;

	newManager.Initialize();

	//Load and create objects
	ResourceManager* resourceManager = newManager.GetResourceManager();

	VertexBuffer* vertexBuffer = new VertexBuffer(BufferType::ArrayBuffer(), BufferUsage::StaticDraw(),sizeof(VertexPosTex), sizeof(vertexDataCubeColorless) / sizeof(VertexPosTex), (GLvoid*)vertexDataCubeColorless);
	vertexBuffer->AddVertexAttributeInformation(0,3,GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), 0);
	vertexBuffer->AddVertexAttributeInformation(1,2,GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), sizeof(Vector3));
	IndexBuffer* indexBuffer = new IndexBuffer( sizeof(float), sizeof(indices) / sizeof(float),GLIndexDataType::UnsignedInt(), (GLvoid*)indices);

	//The mesh takes over the ownership of the buffers
	std::unique_ptr<Mesh> _thisMesh(new Mesh(vertexBuffer, indexBuffer));

	std::unique_ptr<Material> _thisMaterial(new Diffuse(resourceManager->GetShaderProgram("Diffuse", "../data/Diffuse.vert", "../data/Diffuse.frag"),
														  resourceManager->GetTexture2D("../data/test.bmp")));
	_thisMaterial->Initialize();

	//Add random objects
	for(int x = -2; x < 2; x++)
	{
		for(int y = -2; y < 2; y++)
		{
			GameObject* cubeObject = new GameObject();
			cubeObject->GetTransform().SetScale(0.5f,0.5f,0.5f);
			cubeObject->GetTransform().SetPosition((float)x * 1.5f,(float)y * 1.5f,0);
			cubeObject->AddComponent(new RotateObject(cubeObject));
			cubeObject->AddComponent(new MeshRenderer(cubeObject,_thisMesh.get(), _thisMaterial.get()));
			newManager.AddGameObject(cubeObject);
		}
	}

	newManager.Update();
	newManager.Shutdown();
}