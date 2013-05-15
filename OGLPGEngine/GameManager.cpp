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

GameManager::GameManager(): _thisWindow(OpenGLVersion::OpenGL4_3(), GLFWOpenGLProfile::CoreProfile()){}
GameManager::~GameManager()
{
	_renderingUpdateStep.clear();
	_defaultUpdateStep.clear();
	_gameObjects.clear();
}

void GameManager::Initialize()
{
	if(!_thisWindow.IsInitialized() ||
		!_thisWindow.OpenWindowAndInitalizeGLEW(1280,720,8,8,8,8,24,8,false))
	{
		//FAILURE
	}

	//Create the main camera object
	Vector2 windowSize = _thisWindow.GetWindowSize();
	GameObject* mainCamera = new GameObject();
	mainCamera->GetTransform().SetPosition(0,2,-5);
	_mainCameraComponent = (Camera*)mainCamera->AddComponent(new Camera(mainCamera));
	_mainCameraComponent->SetAspectRatio((windowSize._x / windowSize._y));

	AddGameObject(mainCamera); //Takes over the ownership of the game object

	//Initialize the renderer
	_renderEngine.Initialize();
	_renderEngine.SetClearColor(Color::CornflowerBlue());
}

void GameManager::Update()
{
	int running = GL_TRUE;
	while(running)
	{
		//Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		for(unsigned int i = 0; i < _defaultUpdateStep.size(); i++)
		{
			_defaultUpdateStep[i]->Update();
		}

		for(unsigned int i = 0; i < _renderingUpdateStep.size(); i++)
		{
			MeshRenderer* currentComponent = static_cast<MeshRenderer*>(_renderingUpdateStep[i]);
			currentComponent->PreDraw(_mainCameraComponent);
			currentComponent->Update();//Draw
			currentComponent->PostDraw();
		}

		//Swap the render buffers
		_thisWindow.SwapBuffers();

		running = !glfwGetKey( GLFW_KEY_ESC ) && _thisWindow.IsWindowOpen();
	}
}
void GameManager::Shutdown()
{

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
				_renderingUpdateStep.push_back(currentComponent);
			}
			currentComponent = NULL;
		}
	}
}

ResourceManager* GameManager::GetResourceManager()
{
	return &_resourceManager;
}