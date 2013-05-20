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
#include "Texture2D.h"
#include "Vector2.h"
#include "ResourceManager.h"
#include "RenderEngine.h"


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

	ResourceManager* GetResourceManager();
private:
	GLFWWindow _thisWindow;
	GLuint _vertexArrayObject;
	std::vector<std::unique_ptr<GameObject>> _gameObjects;
	std::vector<Component*> _defaultUpdateStep;
	std::vector<Component*> _renderingUpdateStep;

	//weak pointer to the main camera component
	Camera* _mainCameraComponent;

	RenderEngine _renderEngine;
	ResourceManager _resourceManager;
};

#endif //GAMEMANAGER_H_INCLUDED