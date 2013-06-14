//Texture2D.h
#ifndef TEXTURE2D_H_INCLUDED
#define TEXTURE2D_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

#include <string>
#include <vector>

#include "Color.h"
class Texture2D
{
public:
	Texture2D(std::string filePath);
	Texture2D(std::string filePath, GLenum minFilter, GLenum magFilter, bool generateMipMaps);
	~Texture2D();

	GLuint GetTexture()const;
	const std::string& GetName()const;
	int GetWidth()const;
	int GetHeight()const;
	int GetChannels()const;
	std::vector<Color> GetImageData();
	std::vector<GLubyte> GetImageDataRedColor(); //Gets a list of all the red color values

private:
	GLuint _texture;
	std::string _name;
	int _width;
	int _height;
	int _channels;

	void Initialize(std::string filePath, GLenum minFilter, GLenum magFilter, bool generateMipMaps);

};
#endif //TEXTURE2D_H_INCLUDED