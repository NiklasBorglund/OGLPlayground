//CDLODNode.h
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#ifndef CDLODNODE_H_INCLUDED
#define CDLODNODE_H_INCLUDED

#include "CDLODSettings.h"
#include "CDLODSelection.h"
#include "BoundingBox.h"

class CDLODNode
{
public:
	CDLODNode();
	~CDLODNode();

	bool IsLeaf() const;

	void Create(int x, int y, int size, int level, const CreateDescription& createDescription, CDLODNode* allNodesBuffer, int& allNodesBufferLastIndex);
	CDLODSelectResult Select(CDLODSelection& selection, bool parentCompletelyInFrustum)const;

	int GetX()const;
	int GetY()const;
	int GetSize()const;
	int GetLevel()const;
	const unsigned int& GetMinHeight()const;
	const unsigned int& GetMaxHeight()const;

	void GetWorldMinMaxX(float& minX, float maxX, int rasterSizeX, const MapDimensions& mapDimensions)const;
	void GetWorldMinMaxY(float& minY, float maxY, int rasterSizeY, const MapDimensions& mapDimensions)const;
	void GetWorldMinMaxZ(float& minZ, float maxZ, const MapDimensions& mapDimensions)const;

	BoundingBox GetBoundingBox(int rasterSizeX, int rasterSizeY, const MapDimensions& mapDimensions)const;

private:
	int _x;
	int _y;
	int _size;
	int _level;
	unsigned int _minHeight;
	unsigned int _maxHeight;
	bool _isLeaf;

	CDLODNode* _topLeft;
	CDLODNode* _topRight;
	CDLODNode* _bottomLeft;
	CDLODNode* _bottomRight;
};

#endif //CDLODNODE_H_INCLUDED