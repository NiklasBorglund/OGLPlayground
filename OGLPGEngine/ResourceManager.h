//ResourceManager.h
// a simple resource manager
#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <memory>
#include <string>
#include <map>

#include "Texture2D.h"
#include "ShaderProgram.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Texture2D* GetTexture2D(std::string filePath);
	ShaderProgram* GetShaderProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
private:
	std::map<std::string, std::unique_ptr<Texture2D>> _textures;
	std::map<std::string, std::unique_ptr<ShaderProgram>> _shaderPrograms;
};
#endif //RESOURCEMANAGER_H_INCLUDED