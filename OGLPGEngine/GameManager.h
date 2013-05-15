//GameManager.h
#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include <vector>
#include <memory>
#include "GLFWWindow.h"
#include "GameObject.h"

//Temp
#include "Material.h"
#include "Mesh.h"
#include "Vector2.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "RenderEngine.h"

struct VertexPosTex
{
	VertexPosTex(Vector3 position, Vector2 texCoord):_position(position), _texCoord(texCoord){}
	Vector3 _position;
	Vector2 _texCoord;
};

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

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Initialize();
	void Update();
	void Shutdown();
	//Takes the ownership of the object 
	void AddGameObject(GameObject* gameObject);

private:
	GLFWWindow _thisWindow;
	GLuint _vertexArrayObject;
	std::vector<std::unique_ptr<GameObject>> _gameObjects;
	std::vector<Component*> _defaultUpdateStep;
	std::vector<Component*> _renderingUpdateStep;

	//Temp Objects (need their own managers)
	std::unique_ptr<Material> _thisMaterial;
	std::unique_ptr<Mesh> _thisMesh;
	//weak pointer to the main camera component
	Camera* _mainCameraComponent;

	RenderEngine _renderEngine;
	ResourceManager _resourceManager;
};

#endif //GAMEMANAGER_H_INCLUDED