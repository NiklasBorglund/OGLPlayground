//Texture2D.cpp
#include "Texture2D.h"
#include "SOIL.h"
#include "GraphicsDevice.h"

Texture2D::Texture2D(GraphicsDevice* graphicsDevice): _graphicsDevice(graphicsDevice)
{

	//Generate the texture
	_graphicsDevice->GenerateTextures(1, &_texture);
	BindTexture();

	_graphicsDevice->SetTextureParameter(TextureType::Texture2D(), TextureParameterType::TextureWrapS(), TextureParameterValue::ClampToEdge());
	_graphicsDevice->SetTextureParameter(TextureType::Texture2D(), TextureParameterType::TextureWrapT(), TextureParameterValue::ClampToEdge());
	_graphicsDevice->SetTextureParameter(TextureType::Texture2D(), TextureParameterType::TextureMinFilter(), TextureParameterValue::Linear());
	_graphicsDevice->SetTextureParameter(TextureType::Texture2D(), TextureParameterType::TextureMagFilter(), TextureParameterValue::Linear());

	_graphicsDevice->SetPixelStorageType(PixelStorageType::UnpackAligment(), 1);
	UnbindTexture();
}
Texture2D::Texture2D(std::string filePath):_name(filePath)
{
	Initialize(filePath, TextureParameterValue::Linear(), TextureParameterValue::Linear(), false);
}
Texture2D::Texture2D(std::string filePath, TextureParameterValue minFilter, TextureParameterValue magFilter, bool generateMipMaps):_name(filePath)
{
	Initialize(filePath, minFilter, magFilter, generateMipMaps);
}
Texture2D::~Texture2D()
{
	if(_graphicsDevice->IsTexture(_texture))
	{
		_graphicsDevice->DeleteTextures(1, &_texture);
	}
}
void Texture2D::Initialize(std::string filePath, TextureParameterValue minFilter, TextureParameterValue magFilter, bool generateMipMaps)
{
	//Really basic image loading
	unsigned char* textureData = SOIL_load_image(_name.c_str(), &_width, &_height, &_channels, SOIL_LOAD_AUTO);
	if(textureData)
	{
		if(!_graphicsDevice->IsTexture(_texture))
		{
			_graphicsDevice->GenerateTextures(1, &_texture);
		}

		//Bind it to the context
		BindTexture();

		ColorFormat format = _channels == 4 ? ColorFormat::RGBA() : ColorFormat::RGB();

		if(generateMipMaps)
		{
			_graphicsDevice->GenerateMipMap(TextureType::Texture2D());
		}

		_graphicsDevice->SetTextureParameter(TextureType::Texture2D(), TextureParameterType::TextureMinFilter(), minFilter);
		_graphicsDevice->SetTextureParameter(TextureType::Texture2D(), TextureParameterType::TextureMagFilter(), magFilter);

		_graphicsDevice->SetTextureData(TextureType::Texture2D(), 0, format,_width, _height,0, format, GraphicsDataType::UnsignedByte(), textureData);

		//clean up
		SOIL_free_image_data(textureData);
		UnbindTexture();
	}
	//else.. failure to load
}

GLuint Texture2D::GetTexture()const
{
	return _texture;
}
const std::string& Texture2D::GetName()const
{
	return _name;
}
int Texture2D::GetWidth()const
{
	return _width;
}
int Texture2D::GetHeight()const
{
	return _height;
}
int Texture2D::GetChannels()const
{
	return _channels;
}
void Texture2D::BindTexture()
{
	_graphicsDevice->BindTexture(TextureType::Texture2D(), _texture);
}
void Texture2D::UnbindTexture()
{
	_graphicsDevice->BindTexture(TextureType::Texture2D(), 0);
}
//Make sure the texture is bound
void Texture2D::SetTextureData(GLint level, ColorFormat internalFormat, int width, int height, int border, 
					ColorFormat format, GraphicsDataType type, const void* pixels)
{
	_width = width;
	_height = height;
	_graphicsDevice->SetTextureData(TextureType::Texture2D(), level, internalFormat,_width, _height,border, format, type, pixels);
}
std::vector<Color> Texture2D::GetImageData()
{
	std::vector<Color> imageData;
	GLuint* image = new GLuint[_width * _height];
	BindTexture();
	_graphicsDevice->GetTextureImage(TextureType::Texture2D(), 0, ColorFormat::RGBA(), GraphicsDataType::UnsignedInt_8_8_8_8(), image);
	UnbindTexture();
	for(int i = 0; i < (_width * _height); i++)
	{
		GLuint value = image[i];
		GLubyte r = (value & 0xFF000000) >> 24;
		GLubyte g = (value & 0x00FF0000) >> 16;
		GLubyte b = (value & 0x0000FF00) >> 8;
		GLubyte a = (value & 0x000000FF);
		imageData.push_back(Color(r,g,b,a));
	}
	delete [] image;
	return imageData;
}
std::vector<GLubyte> Texture2D::GetImageDataRedColor()
{
	std::vector<GLubyte> imageData;
	GLuint* image = new GLuint[_width * _height];
	BindTexture();
	_graphicsDevice->GetTextureImage(TextureType::Texture2D(), 0, ColorFormat::RGBA(), GraphicsDataType::UnsignedInt_8_8_8_8(), image);
	UnbindTexture();
	for(int i = 0; i < (_width * _height); i++)
	{
		imageData.push_back(((image[i] & 0xFF000000) >> 24));
	}
	delete [] image;
	return imageData;
}