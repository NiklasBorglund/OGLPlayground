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
	//Run all the start
	for(unsigned int i = 0; i < _defaultUpdateStep.size(); i++)
	{
			_defaultUpdateStep[i]->Start();
	}
	_renderEngine.Start();

	int running = GL_TRUE;
	while(running)
	{
		_gameTime.StartFrame();

		//Clear the screen
		_renderEngine.ClearBuffers();

		for(unsigned int i = 0; i < _defaultUpdateStep.size(); i++)
		{
			_defaultUpdateStep[i]->Update(&_gameTime);
		}

		//Render the objects
		_renderEngine.Update(&_gameTime);

		//Swap the render buffers
		_renderEngine.SwapBuffers();

		_gameTime.EndFrame();
		//std::cout << "FPS:" << _gameTime.GetFPS() << std::endl;
		//std::cout << "FrameCounts:" << _gameTime.GetFrameCount() << std::endl;

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
			RegisterComponent(componentList[i]);
		}
	}
}
void GameManager::AddComponentToGameObject(GameObject* object, Component* componentToAdd)
{
	if(object != NULL && componentToAdd != NULL)
	{
		object->AddComponent(componentToAdd);
		RegisterComponent(componentToAdd);
	}
}
GameObject* GameManager::CreateGameObjectsFromModel(std::string filePath)
{
	std::vector<Mesh*> model = _resourceManager.GetModelFromFile(filePath);

	//Create all the necessary materials
	for(unsigned int i = 0; i < model.size(); i++)
	{
		std::string texturePath = FileUtility::LocalFileDirectory() + model[i]->GetDefaultDiffuseTextureName();
		if(!_resourceManager.CheckIfMaterialExist(texturePath))
		{
			_resourceManager.StoreAndInitMaterial(texturePath, 
			new Diffuse(_resourceManager.GetShaderProgram("Diffuse", "../data/Diffuse.vert", "../data/Diffuse.frag"),
			_resourceManager.GetTexture2D(texturePath)));
		}
	}

	GameObject* previousMesh = NULL;
	GameObject* rootObject = NULL;
	for(unsigned int i = 0; i < model.size(); i++)
	{
		GameObject* meshObject = new GameObject();

		//Correct the transforms
		if(previousMesh != NULL)
		{
			meshObject->GetTransform().SetParent(&previousMesh->GetTransform());
		}
		else
		{
			rootObject = meshObject;
		}

		std::string texturePath = FileUtility::LocalFileDirectory() + model[i]->GetDefaultDiffuseTextureName();
		meshObject->AddComponent(new MeshRenderer(meshObject, model[i], _resourceManager.GetMaterial(texturePath)));

		AddGameObject(meshObject);
		previousMesh = meshObject;
	}

	return rootObject;
}

ResourceManager* GameManager::GetResourceManager()
{
	return &_resourceManager;
}
GameObject* GameManager::GetMainCameraObject()const
{
	return _renderEngine.GetCameraComponent()->GetGameObject();
}

void GameManager::RegisterComponent(Component* componentToRegister)
{
	if(componentToRegister->GetUpdateStep() == UPDATE_DEFAULT)
	{
		//Add a weak pointer to the update step
		_defaultUpdateStep.push_back(componentToRegister);
	}
	else if(componentToRegister->GetUpdateStep() == UPDATE_RENDER)
	{
		_renderEngine.AddRenderingComponent(componentToRegister);
	}
}