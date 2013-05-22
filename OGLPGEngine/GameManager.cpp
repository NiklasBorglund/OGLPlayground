//GameManager.cpp
#include "GameManager.h"
#include "OpenGLVersion.h"

//Temp
#include "FileUtility.h"
#include "Vector2.h"
#include "Camera.h"
#include "Diffuse.h"
#include "MeshRenderer.h"
#include "Color.h"

GameManager::GameManager(){}
GameManager::~GameManager()
{
	_defaultUpdateStep.clear();
	_gameObjects.clear();
}

void GameManager::Initialize()
{

	//Create the main camera object
	GameObject* mainCamera = new GameObject();
	mainCamera->GetTransform().SetPosition(0,2,-5);
	Camera* cameraComponent = (Camera*)mainCamera->AddComponent(new Camera(mainCamera));

	AddGameObject(mainCamera); //Takes over the ownership of the game object

	//Initialize the renderer
	_renderEngine.Initialize(cameraComponent);
	_renderEngine.SetClearColor(Color::CornflowerBlue());
}

void GameManager::Update()
{
	int running = GL_TRUE;
	while(running)
	{
		//Clear the screen
		_renderEngine.ClearBuffers();

		for(unsigned int i = 0; i < _defaultUpdateStep.size(); i++)
		{
			_defaultUpdateStep[i]->Update();
		}

		//Render the objects
		_renderEngine.Update();

		//Swap the render buffers
		_renderEngine.SwapBuffers();

		running = !glfwGetKey( GLFW_KEY_ESC ) && _renderEngine.GetWindow().IsWindowOpen();
	}
}
void GameManager::Shutdown()
{
	_renderEngine.Shutdown();
}
void GameManager::AddGameObject(GameObject* gameObject)
{
	if(gameObject != NULL)
	{
		_gameObjects.push_back(std::unique_ptr<GameObject>(gameObject));

		const std::vector<Component*>& componentList = gameObject->GetComponents();
		for(unsigned int i = 0; i < componentList.size(); i++)
		{
			Component* currentComponent = componentList[i];
			if(currentComponent->GetUpdateStep() == UPDATE_DEFAULT)
			{
				//Add a weak pointer to the update step
				_defaultUpdateStep.push_back(currentComponent);
			}
			else if(currentComponent->GetUpdateStep() == UPDATE_RENDER)
			{
				_renderEngine.AddRenderingComponent(currentComponent);
			}
		}
	}
}

ResourceManager* GameManager::GetResourceManager()
{
	return &_resourceManager;
}