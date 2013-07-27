//CDLODQuadTree.h
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#ifndef CDLODQUADTREE_H_INCLUDED
#define CDLODQUADTREE_H_INCLUDED

#include "CDLODSettings.h"
#include "Vector2.h"

class CDLODNode;
class CDLODSelection;
class CDLODQuadTree
{
public:
	CDLODQuadTree();
	~CDLODQuadTree();

	bool Create(const CreateDescription& createDescription);
	void Select(CDLODSelection& selection)const;
	int GetRasterSizeX()const;
	int GetRasterSizeY()const;

	void Clean();

private:
	CreateDescription _createDescription;
	int _rasterSizeX;
	int _rasterSizeY;
	Vector2 _leafNodeWorldSize;
	float _LODLevelNodeDiagonalSizes[CDLODSettings::MaxLevelCount];
	int _topNodeSize;
	int _topNodeCountX;
	int _topNodeCountY;
	int _allNodesCount;
	CDLODNode* _allNodesBuffer;
	CDLODNode*** _topLevelNodes;
};
#endif //CDLODQUADTREE_H_INCLUDED