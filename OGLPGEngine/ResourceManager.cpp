//ResourceManager.cpp
#include "ResourceManager.h"
#include "FileUtility.h"
#include "Primitive.h"

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	_materials.clear();
	_meshes.clear();
	_shaderPrograms.clear();
	_textures.clear();
}
Texture2D* ResourceManager::GetTexture2D(std::string filePath)
{
	std::map<std::string, std::unique_ptr<Texture2D>>::iterator it = _textures.find(filePath);
	if(it != _textures.end())
	{
		return it->second.get();
	}
	Texture2D* newTexture = new Texture2D(filePath);
	_textures.insert(std::pair<std::string, std::unique_ptr<Texture2D>>(filePath, std::unique_ptr<Texture2D>(newTexture)));
	return newTexture;
}
ShaderProgram* ResourceManager::GetShaderProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath)
{
	std::map<std::string, std::unique_ptr<ShaderProgram>>::iterator it = _shaderPrograms.find(name);
	if(it != _shaderPrograms.end())
	{
		return it->second.get();
	}
	ShaderProgram* newProgram = new ShaderProgram(FileUtility::ReadContentsFromFile(vertexShaderPath),
												  FileUtility::ReadContentsFromFile(fragmentShaderPath));
	_shaderPrograms.insert(std::pair<std::string, std::unique_ptr<ShaderProgram>>(name, std::unique_ptr<ShaderProgram>(newProgram)));

	newProgram->CreateAndLinkProgram();

	return newProgram;
}
Mesh* ResourceManager::GetPrimitive(PrimitiveType primitiveType)
{
	Mesh* thisMesh = NULL;
	std::string meshName;
	switch(primitiveType)
	{
	case CUBE_PRIMITIVE:
		{
			meshName = "cube_primitive";
			thisMesh = GetMesh(meshName);
			break;
		}
	default:
		{
			//Default in creating/getting a cube
			meshName = "cube_primitive";
			thisMesh = GetMesh(meshName);
			break;
		}
	}

	if(thisMesh == NULL)
	{
		switch(primitiveType)
		{
		case CUBE_PRIMITIVE:
			{
				thisMesh = Primitive::CreateCube();
				break;
			}
		default:
			{
				//Default in creating/getting a cube
				thisMesh = Primitive::CreateCube();
				break;
			}
		}
		_meshes.insert(std::pair<std::string, std::unique_ptr<Mesh>>(meshName, std::unique_ptr<Mesh>(thisMesh)));
	}

	return thisMesh;
}
/* Store & Init the material and give the ownership to the resourceManager*/
void ResourceManager::StoreAndInitMaterial(std::string name, Material* material)
{
	if(material != NULL)
	{
		//TODO::Check for duplicate names before insertion
		_materials.insert(std::pair<std::string, std::unique_ptr<Material>>(name, std::unique_ptr<Material>(material)));
		material->Initialize();
	}
}
Material* ResourceManager::GetMaterial(std::string name)
{
	std::map<std::string, std::unique_ptr<Material>>::iterator it = _materials.find(name);
	if(it != _materials.end())
	{
		return it->second.get();
	}
	return NULL;
}

//Private methods
Mesh* ResourceManager::GetMesh(std::string name)
{
	std::map<std::string, std::unique_ptr<Mesh>>::iterator it = _meshes.find(name);
	if(it != _meshes.end())
	{
		return it->second.get();
	}
	return NULL;
}