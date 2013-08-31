//HeightMapSourceImage.h
//A heighmap from an image source
#ifndef HEIGHTMAPSOURCEIMAGE_H_INCLUDED
#define HEIGHTMAPSOURCEIMAGE_H_INCLUDED

#include "CDLODSettings.h"
#include "Texture2D.h"

class HeightMapSourceImage : public IHeightMapSource
{
public:
	HeightMapSourceImage(Texture2D* heightMapImage): _heightmapImage(heightMapImage)
	{
		_heightData = _heightmapImage->GetImageDataRedColor();
	}
	virtual int GetSizeX()
	{
		return _heightmapImage->GetWidth();
	}
	virtual int GetSizeY()
	{
		return _heightmapImage->GetHeight();
	}
	virtual unsigned short GetHeightAt(int x, int y)
	{
		return (unsigned short)((_heightData[x + y * GetSizeX()]) * 0.2f);
	}
	virtual void  GetAreaMinMaxHeight( int x, int y, int sizeX, int sizeY, unsigned int& minHeight, unsigned int& maxHeight)
	{
		minHeight = 65535;
		maxHeight = 0;

		int width = GetSizeX();
		int height = GetSizeY();
		for(int ry = 0; y < GetSizeY(); y++)
		{
			for(int rx = 0; x < GetSizeX(); x++)
			{
				unsigned int height = (unsigned int)(_heightData[(x + rx) + (y + ry) * width] * 0.2f);
				minHeight = std::min(minHeight, height);
				maxHeight = std::max(maxHeight, height);
			}
		}
	}
private:
	Texture2D* _heightmapImage;
	std::vector<unsigned char> _heightData;

};
#endif //HEIGHTMAPSOURCEIMAGE_H_INCLUDED