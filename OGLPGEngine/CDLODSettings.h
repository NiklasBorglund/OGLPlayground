//CDLODSettings.h
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#ifndef CDLODSETTINGS_H_INCLUDED
#define CDLODSETTINGS_H_INCLUDED

#include "Vector3.h"

struct MapDimensions
{
	Vector3 _min;
	Vector3 _size;

	float MaxX()const
	{
		return _min._x + _size._x;
	}
	float MaxY()const
	{
		return _min._y + _size._y;
	}
	float MaxZ()const
	{
		return _min._z + _size._z;
	}
};

class IHeightMapSource
{
public:
	virtual int GetSizeX() = 0;
	virtual int GetSizeY() = 0;

	virtual unsigned short GetHeightAt(int x, int y) = 0;
	virtual void  GetAreaMinMaxHeight( int x, int y, int sizeX, int sizeY, unsigned int& minHeight, unsigned int& maxHeight) = 0;
};

struct CDLODSettings
{
	static const int MaxLevelCount = 6;
	static const int DefaultLeafNodeSize = 8;
	static const int DefaultRenderGridResolution = 32;
	int _levelCount;
	int _leafNodeSize;
	int _renderGridResolution;

	void SetDefault()
	{
		_levelCount = MaxLevelCount;
		_leafNodeSize = DefaultLeafNodeSize;
		_renderGridResolution = DefaultRenderGridResolution;
	}

	int GetGridDimensions()const
	{
		return _leafNodeSize * _renderGridResolution;
	}
};

struct CreateDescription
{
	CDLODSettings _settings;
	MapDimensions _mapDimensions;
	IHeightMapSource* _heightMap;
};

#endif //CDLODSETTINGS_H_INCLUDED