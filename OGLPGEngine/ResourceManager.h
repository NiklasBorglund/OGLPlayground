//ResourceManager.h
// a simple resource manager
#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <memory>
#include <string>
#include <map>

#include "Texture2D.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Material.h"

enum PrimitiveType
{
	CUBE_PRIMITIVE = 1,
};

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Texture2D* GetTexture2D(std::string filePath);
	ShaderProgram* GetShaderProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
	Mesh* GetPrimitive(PrimitiveType primitiveType);
	std::vector<Mesh*> GetModelFromFile(std::string filePath);

	/* Store & Init the material and give the ownership to the resourceManager*/
	void StoreAndInitMaterial(std::string name, Material* _material);
	bool CheckIfMaterialExist(std::string name);
	Material* GetMaterial(std::string name);
	void AddMesh(std::string meshName, Mesh* mesh);
	Mesh* GetMesh(std::string name);

private:
	std::map<std::string, std::unique_ptr<Texture2D>> _textures;
	std::map<std::string, std::unique_ptr<ShaderProgram>> _shaderPrograms;
	std::map<std::string, std::unique_ptr<Mesh>> _meshes;
	std::map<std::string, std::unique_ptr<Material>> _materials;
	std::map<std::string, std::vector<Mesh*>> _models;
	std::map<std::string, std::vector<Mesh*>> _terrain;
};
#endif //RESOURCEMANAGER_H_INCLUDED