//Texture2D.h
#ifndef TEXTURE2D_H_INCLUDED
#define TEXTURE2D_H_INCLUDED

#include <string>
#include <vector>

#include "Color.h"

class GraphicsDevice;
class TextureParameterValue;
class ColorFormat;
class GraphicsDataType;
class Texture2D
{
public:
	Texture2D(GraphicsDevice* graphicsDevice);
	Texture2D(std::string filePath);
	Texture2D(std::string filePath, TextureParameterValue minFilter, TextureParameterValue magFilter, bool generateMipMaps);
	~Texture2D();

	unsigned int GetTexture()const;
	const std::string& GetName()const;
	int GetWidth()const;
	int GetHeight()const;
	int GetChannels()const;
	void BindTexture();
	void UnbindTexture();
	//Make sure the texture is bound
	void SetTextureData(int level, ColorFormat internalFormat, int width, int height, int border, 
					ColorFormat format, GraphicsDataType type, const void* pixels);
	std::vector<Color> GetImageData();
	std::vector<unsigned char> GetImageDataRedColor(); //Gets a list of all the red color values

private:
	GraphicsDevice* _graphicsDevice;
	unsigned int _texture;
	std::string _name;
	int _width;
	int _height;
	int _channels;

	void Initialize(std::string filePath, TextureParameterValue minFilter, TextureParameterValue magFilter, bool generateMipMaps);

};
#endif //TEXTURE2D_H_INCLUDED