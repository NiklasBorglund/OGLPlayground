//main.cpp

#include "GameManager.h"
#include "Diffuse.h"
#include "RotateObject.h"
#include "MeshRenderer.h"
#include "FileUtility.h"
#include "TerrainHeightMap.h"
#include "FreeLookCamera.h"
#include <string>
#include <memory>


int main()
{
	GameManager newManager;

	newManager.Initialize();

	//Load and create objects
	ResourceManager* resourceManager = newManager.GetResourceManager();

	//Create a new Material to use for the cubes
	/*
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
	*/

	
	//Loads the meshes from the model file into a
	//simple gameobject hierarchy and returns the root game object
	//Returns null if the model wasn't found
	/*
	GameObject* dwarfObject = newManager.CreateGameObjectsFromModel("data/dwarf2.b3d");
	if(dwarfObject != NULL)
	{
		dwarfObject->GetTransform().SetScale(0.05f,0.05f,0.05f);
		dwarfObject->GetTransform().SetPosition(-3.0f,0.0f,0.0f);
		newManager.AddComponentToGameObject(dwarfObject, new RotateObject(dwarfObject));
	}

	GameObject* spiderObject = newManager.CreateGameObjectsFromModel("data/spider.obj");
	if(spiderObject != NULL)
	{
		spiderObject->GetTransform().SetScale(0.01f,0.01f,0.01f);
		spiderObject->GetTransform().SetPosition(0.0f,1.0f,0.0f);
	}

	GameObject* dwarfObject2 = newManager.CreateGameObjectsFromModel("data/dwarf2.b3d");
	if(dwarfObject2 != NULL)
	{
		dwarfObject2->GetTransform().SetScale(0.05f,0.05f,0.05f);
		dwarfObject2->GetTransform().SetPosition(3.0f,0.0f,0.0f);
		newManager.AddComponentToGameObject(dwarfObject2, new RotateObject(dwarfObject2));
	}
	*/
	
	

	resourceManager->StoreAndInitMaterial("terrainMaterial", 
										new Diffuse(resourceManager->GetShaderProgram("Diffuse", "../data/Diffuse.vert", "../data/Diffuse.frag"),
										resourceManager->GetTexture2D("../data/test.bmp")));
	TerrainHeightMap newTerrain;
	newTerrain.CreateHeightMap(resourceManager->GetTexture2D("data/heightmap1.bmp"), 64);

	//Test
	int numberOfTerrainPatches = newTerrain.GetNumberOfPatches();
	for(int i = 0; i < numberOfTerrainPatches; i++)
	{
		GameObject* terrainObject = new GameObject();
		terrainObject->AddComponent(new MeshRenderer(terrainObject,newTerrain.GetTerrainMeshes()[i], resourceManager->GetMaterial("terrainMaterial")));
		newManager.AddGameObject(terrainObject);
	}

	//Add a movement script to the camera
	GameObject* cameraObject = newManager.GetMainCameraObject();
	newManager.AddComponentToGameObject(cameraObject, new FreeLookCamera(cameraObject));

	newManager.Update();
	newManager.Shutdown();
}