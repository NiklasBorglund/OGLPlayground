//FileUtility.h
#ifndef FILEUTILITY_H_INCLUDED
#define FILEUTILITY_H_INCLUDED

#include "Uncopyable.h"
#include <fstream>
#include <string>
#include <iostream>

class FileUtility : private Uncopyable
{
public:
	static inline const char* const LocalFileDirectory()
	{
		return "data/";
	}
	static inline const char* const GlobalFileDirectory()
	{
		return "../data/";
	}

	static std::string ReadContentsFromFile(const char* filePath)
	{
		std::ifstream myReadFile;
		std::string fileContents;
		myReadFile.open(filePath);
		if(myReadFile.is_open())
		{
			myReadFile.seekg(0, std::ios::end);
			fileContents.resize((unsigned int)myReadFile.tellg());
			myReadFile.seekg(0, std::ios::beg);
			myReadFile.read(&fileContents[0], fileContents.size());
			myReadFile.close();
		}
		return fileContents;
	}
	static std::string ReadContentsFromFile(std::string filePath)
	{
		return ReadContentsFromFile(filePath.c_str());
	}
	static std::string ReadFileFromDataFolder(std::string fileName)
	{
		return ReadContentsFromFile((std::string)LocalFileDirectory() + fileName);
	}
	static std::string GetFileNameFromPath(std::string filePath)
	{
		std::string fileName = filePath.substr(filePath.find_last_of("\\") + 1 );
		fileName = fileName.substr(fileName.find_last_of("/") + 1 );
		return fileName;
	}

private:
	FileUtility(){}
	~FileUtility(){}
};
#endif //FILEUTILITY_H_INCLUDED