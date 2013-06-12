//GameManager.h
#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include <vector>
#include <memory>
#include "GameObject.h"
#include "GameTime.h"

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
	//TODO::find a nicer way to solve this
	void AddComponentToGameObject(GameObject* object, Component* componentToAdd);

	GameObject* CreateGameObjectsFromModel(std::string filePath);

	ResourceManager* GetResourceManager();
	GameObject* GetMainCameraObject()const;
private:
	GLuint _vertexArrayObject;
	std::vector<std::unique_ptr<GameObject>> _gameObjects;
	std::vector<Component*> _defaultUpdateStep;

	RenderEngine _renderEngine;
	ResourceManager _resourceManager;

	GameTime _gameTime;

	//Registers the component to the update loop
	void RegisterComponent(Component* componentToRegister);
};

#endif //GAMEMANAGER_H_INCLUDED