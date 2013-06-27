//main.cpp

#include "GameManager.h"
#include "Diffuse.h"
#include "Diffuse2D.h"
#include "RotateObject.h"
#include "MeshRenderer.h"
#include "FileUtility.h"
#include "TerrainHeightMap.h"
#include "FreeLookCamera.h"
#include "FontRenderer.h"
#include "FontMaterial.h"
#include <string>
#include <memory>


int main()
{
	GameManager newManager;

	newManager.Initialize();

	//Load and create objects
	ResourceManager* resourceManager = newManager.GetResourceManager();

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
	*/
	
	
	resourceManager->StoreAndInitMaterial("terrainMaterial", 
										new Diffuse(resourceManager->GetShaderProgram("Diffuse", "../data/Diffuse.vert", "../data/Diffuse.frag"),
										resourceManager->GetTexture2D("../data/test.bmp")));

	TerrainHeightMap newTerrain;
	newTerrain.CreateHeightMap(resourceManager->GetTexture2D("data/heightmap1.bmp"), 128);

	//Test
	int numberOfTerrainPatches = newTerrain.GetNumberOfPatches();
	for(int i = 0; i < numberOfTerrainPatches; i++)
	{
		GameObject* terrainObject = new GameObject();
		terrainObject->AddComponent(new MeshRenderer(terrainObject,newTerrain.GetTerrainMeshes()[i], resourceManager->GetMaterial("terrainMaterial")));
		newManager.AddGameObject(terrainObject);
	}

	
	//TEST 2D OBJECT & Material
	/*
	resourceManager->StoreAndInitMaterial("2DMaterial", 
										new Diffuse2D(resourceManager->GetShaderProgram("Diffuse2D", "../data/Diffuse2D.vert", "../data/Diffuse2D.frag"),
										resourceManager->GetTexture2D("../data/test.bmp")));
	GameObject* cubeObject = new GameObject();
	cubeObject->GetTransform().SetScale(128,128,1);
	cubeObject->GetTransform().SetPosition(Vector3(500,300,0));
	cubeObject->AddComponent(new MeshRenderer(cubeObject,resourceManager->GetPrimitive(PLANE_PRIMITIVE),
	resourceManager->GetMaterial("2DMaterial"), ComponentUpdateStep::Render2DUpdate()));
	newManager.AddGameObject(cubeObject);
	*/
	

	//Add a movement script to the camera
	GameObject* cameraObject = newManager.GetMainCameraObject();
	newManager.AddComponentToGameObject(cameraObject, new FreeLookCamera(cameraObject));

	newManager.Update();
	newManager.Shutdown();
}