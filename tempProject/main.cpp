//main.cpp

#include "GameManager.h"
#include "Diffuse.h"
#include "RotateObject.h"
#include "MeshRenderer.h"
#include <memory>


int main()
{
	GameManager newManager;

	newManager.Initialize();

	//Load and create objects
	ResourceManager* resourceManager = newManager.GetResourceManager();

	//Create a new Material to use for the cubes
	resourceManager->StoreAndInitMaterial("cubeMaterial", 
										new Diffuse(resourceManager->GetShaderProgram("Diffuse", "../data/Diffuse.vert", "../data/Diffuse.frag"),
										resourceManager->GetTexture2D("../data/test.bmp")));

	//Add random objects
	for(int x = -2; x < 2; x++)
	{
		for(int y = -2; y < 2; y++)
		{
			GameObject* cubeObject = new GameObject();
			cubeObject->GetTransform().SetScale(0.5f,0.5f,0.5f);
			cubeObject->GetTransform().SetPosition((float)x * 1.5f,(float)y * 1.5f,0);
			cubeObject->AddComponent(new RotateObject(cubeObject));
			cubeObject->AddComponent(new MeshRenderer(cubeObject,resourceManager->GetPrimitive(CUBE_PRIMITIVE), resourceManager->GetMaterial("cubeMaterial")));
			newManager.AddGameObject(cubeObject);
		}
	}

	newManager.Update();
	newManager.Shutdown();
}