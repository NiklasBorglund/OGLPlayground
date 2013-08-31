//GameManager.cpp
#include "GameManager.h"
#include "OpenGLVersion.h"

//Temp
#include "FileUtility.h"
#include "Vector2.h"
#include "Camera.h"
#include "Diffuse.h"
#include "FontMaterial.h"
#include "MeshRenderer.h"
#include "FontRenderer.h"
#include "Color.h"

//Debug
#include "PrintFPS.h"
#include "PrintAvgFPS.h"
#include "Print3DDrawCalls.h"
#include "Print3DTriangles.h"
#include "Print2DDrawCalls.h"
#include "Print2DTriangles.h"

GameManager::GameManager(){}
GameManager::~GameManager()
{
	_defaultUpdateStep.clear();
	_gameObjects.clear();
}

void GameManager::Initialize()
{
	//Initialize the resource manager
	_resourceManager.Initialize(&_graphicsDevice);

	//Create the main camera object
	GameObject* mainCamera = new GameObject();
	mainCamera->GetTransform().SetPosition(-20,15,30);
	Camera* cameraComponent = (Camera*)mainCamera->AddComponent(new Camera(mainCamera, CameraType::Perspective()));

	AddGameObject(mainCamera); //Takes over the ownership of the game object

	//Initialize the renderer
	_renderEngine.Initialize(cameraComponent, &_resourceManager, &_graphicsDevice);
	_renderEngine.SetClearColor(Color::CornflowerBlue());

	//Create the 2D camera
	GameObject* camera2D = new GameObject();
	//camera2D->GetTransform().SetPosition(Vector3(0.0f,0.0f,-0.1f));
	Camera* camera2DComponent = (Camera*)camera2D->AddComponent(new Camera(camera2D, CameraType::Orthographic()));
	camera2DComponent->SetNearClip(-1.0f);
	camera2DComponent->SetFarClip(1.0f);
	AddGameObject(camera2D); //Takes over the ownership of the game object
	//Initialize the 2D renderer
	_renderEngine2D.Initialize(camera2DComponent, _renderEngine.GetWindowPointer(), &_graphicsDevice);

	LoadDebugComponents();
}

void GameManager::Update()
{
	//Run all the start
	for(unsigned int i = 0; i < _defaultUpdateStep.size(); i++)
	{
			_defaultUpdateStep[i]->Start();
	}
	_renderEngine.Start();
	_renderEngine2D.Start();

	int running = true;
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

		//Render the 2D objects
		_renderEngine2D.Update(&_gameTime);

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
	_renderEngine2D.Shutdown();
	_resourceManager.Shutdown();
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
GraphicsDevice* GameManager::GetGraphicsDevice()
{
	return &_graphicsDevice;
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
		_renderEngine.AddRenderingComponent(static_cast<Renderer*>(componentToRegister));
	}
	else if(componentToRegister->GetUpdateStep() == UPDATE_RENDER2D)
	{
		_renderEngine2D.AddRenderingComponent(static_cast<Renderer*>(componentToRegister));
	}
}
void GameManager::LoadDebugComponents()
{
	Font* debugFont = _resourceManager.GetFont("../data/fonts/SourceSansPro-Bold.otf");
	debugFont->SetFontSize(12);
	_resourceManager.StoreAndInitMaterial("FontMaterial", 
										new FontMaterial(_resourceManager.GetShaderProgram("Font2D", "../data/FontMaterial.vert", "../data/FontMaterial.frag"),
										Color::Yellow()));

	GameObject* FPS = new GameObject();
	FPS->GetTransform().SetPosition(Vector3(10,16,0));
	FPS->AddComponent(new FontRenderer(FPS,_resourceManager.GetMaterial("FontMaterial"), debugFont, "FPS:", GetGraphicsDevice()));
	FPS->AddComponent(new PrintFPS(FPS));
	AddGameObject(FPS);


	GameObject* avgFPS = new GameObject();
	avgFPS->GetTransform().SetPosition(Vector3(10,32,0));
	avgFPS->AddComponent(new FontRenderer(avgFPS,_resourceManager.GetMaterial("FontMaterial"), debugFont, "Avg FPS:", GetGraphicsDevice()));
	avgFPS->AddComponent(new PrintAvgFPS(avgFPS));
	AddGameObject(avgFPS);

    GameObject* drawCall3D = new GameObject();
	drawCall3D->GetTransform().SetPosition(Vector3(10,48,0));
	drawCall3D->AddComponent(new FontRenderer(drawCall3D,_resourceManager.GetMaterial("FontMaterial"), debugFont, "Draw Calls(3D):", GetGraphicsDevice()));
	drawCall3D->AddComponent(new Print3DDrawCalls(drawCall3D, &_renderEngine));
	AddGameObject(drawCall3D);

	GameObject* drawCall2D = new GameObject();
	drawCall2D->GetTransform().SetPosition(Vector3(10,64,0));
	drawCall2D->AddComponent(new FontRenderer(drawCall2D,_resourceManager.GetMaterial("FontMaterial"), debugFont, "Draw Calls(2D):", GetGraphicsDevice()));
	drawCall2D->AddComponent(new Print2DDrawCalls(drawCall2D, &_renderEngine2D));
	AddGameObject(drawCall2D);

	GameObject* triCount3D = new GameObject();
	triCount3D->GetTransform().SetPosition(Vector3(10,80,0));
	triCount3D->AddComponent(new FontRenderer(triCount3D,_resourceManager.GetMaterial("FontMaterial"), debugFont, "Triangles(3D):", GetGraphicsDevice()));
	triCount3D->AddComponent(new Print3DTriangles(triCount3D, &_renderEngine));
	AddGameObject(triCount3D);

	GameObject* triCount2D = new GameObject();
	triCount2D->GetTransform().SetPosition(Vector3(10,96,0));
	triCount2D->AddComponent(new FontRenderer(triCount2D,_resourceManager.GetMaterial("FontMaterial"), debugFont, "Triangles(2D):", GetGraphicsDevice()));
	triCount2D->AddComponent(new Print2DTriangles(triCount2D, &_renderEngine2D));
	AddGameObject(triCount2D);

	GameObject* drawDebugObjects = new GameObject();
	drawDebugObjects->GetTransform().SetPosition(Vector3(10,704,0));
	drawDebugObjects->AddComponent(new FontRenderer(drawDebugObjects,_resourceManager.GetMaterial("FontMaterial"), debugFont, 
		"Press 'B' to toggle bounding boxes", GetGraphicsDevice()));
	AddGameObject(drawDebugObjects);

	GameObject* drawWireframe = new GameObject();
	drawWireframe->GetTransform().SetPosition(Vector3(10,688,0));
	drawWireframe->AddComponent(new FontRenderer(drawWireframe,_resourceManager.GetMaterial("FontMaterial"), debugFont, 
		"Press 'N' to toggle wireframe", GetGraphicsDevice()));
	AddGameObject(drawWireframe);
}