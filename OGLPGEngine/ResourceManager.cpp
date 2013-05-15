//ResourceManager.cpp
#include "ResourceManager.h"
#include "FileUtility.h"

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	_textures.clear();
	_shaderPrograms.clear();
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