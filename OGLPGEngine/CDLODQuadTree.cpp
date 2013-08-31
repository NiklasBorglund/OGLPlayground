//CDLODQuadTree.cpp
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#include "CDLODQuadTree.h"
#include "CDLODNode.h"
#include <cassert>
#include <algorithm>

CDLODQuadTree::CDLODQuadTree()
{
	_allNodesBuffer = NULL;
	_topLevelNodes = NULL;
}
CDLODQuadTree::~CDLODQuadTree()
{
	Clean();
}
void CDLODQuadTree::Clean()
{
	if(_allNodesBuffer != NULL)
	{
		//TODO::FIX problem
		//delete[] _allNodesBuffer;
	}
	_allNodesBuffer = NULL;

	if(_topLevelNodes != NULL)
	{
		for(int y = 0; y < _topNodeCountY; y++)
		{
			delete [] _topLevelNodes[y];
		}

		delete [] _topLevelNodes;
		_topLevelNodes = NULL;
	}
}
bool CDLODQuadTree::Create(const CreateDescription& createDescription)
{
	Clean();
	this->_createDescription = createDescription;
	this->_rasterSizeX = createDescription._heightMap->GetSizeX();
	this->_rasterSizeY = createDescription._heightMap->GetSizeY();

	if(createDescription._settings._levelCount > CDLODSettings::MaxLevelCount)
	{
		//error in settings
		assert(false);
		return false;
	}

	//Determine how many nodes we will use, and the size of the root node
	_leafNodeWorldSize._x = createDescription._settings._leafNodeSize * createDescription._mapDimensions._size._x / _rasterSizeX;
	_leafNodeWorldSize._y = createDescription._settings._leafNodeSize * createDescription._mapDimensions._size._y / _rasterSizeY;
	_LODLevelNodeDiagonalSizes[0] = sqrtf(_leafNodeWorldSize._x * _leafNodeWorldSize._x + _leafNodeWorldSize._y * _leafNodeWorldSize._y);

	int totalNodeCount = 0;

	_topNodeSize = createDescription._settings._leafNodeSize;
	for(int i = 0; i < createDescription._settings._levelCount; i++)
	{
		if(i != 0)
		{
			_topNodeSize *= 2;
			_LODLevelNodeDiagonalSizes[i] = 2 * _LODLevelNodeDiagonalSizes[i-1];
		}
		int nodeCountX = (_rasterSizeX - 1) / _topNodeSize + 1;
		int nodeCountY = (_rasterSizeY - 1) / _topNodeSize + 1;
		totalNodeCount += (nodeCountX) * (nodeCountY);
	}

	//Initialize the tree memory, create tree nodes, and extract the min/max heights
	//Initialize buffer with all the nodes
	_allNodesBuffer = new CDLODNode[totalNodeCount];
	int nodeCounter = 0;
	_topNodeCountX = (_rasterSizeX - 1) / _topNodeSize + 1;
	_topNodeCountY = (_rasterSizeY - 1) / _topNodeSize + 1;
	_topLevelNodes = new CDLODNode**[_topNodeCountY];
	for(int y = 0; y < _topNodeCountY; y++)
	{
		_topLevelNodes[y] = new CDLODNode*[_topNodeCountX];
		for(int x = 0; x < _topNodeCountX; x++)
		{
			_topLevelNodes[y][x] = &_allNodesBuffer[nodeCounter];
			nodeCounter++;

			_topLevelNodes[y][x]->Create(x * _topNodeSize, y * _topNodeSize, _topNodeSize,
				0, _createDescription, _allNodesBuffer, nodeCounter);
		}
	}

	_allNodesCount = nodeCounter;
	assert(nodeCounter == totalNodeCount); //If they don't match, something is wrong

	return true;
}
void CDLODQuadTree::Select(CDLODSelection& selection)const
{
	int layerCount = selection.GetCreateDescription()->_settings._levelCount;

	float LODNear = 0;
	float LODFar = selection.GetVisibilityDistance();
	float detailBalance = selection.GetLODDistanceRatio();

	float total = 0;
	float currentDetailBalance = 1.0f;

	selection.SetIsVisibleDistanceTooSmall(false);

	for(int i = 0; i < layerCount; i++)
	{
		total += currentDetailBalance;
		currentDetailBalance *= detailBalance;
	}

	float section = (LODFar - LODNear) / total;

	float previousPosition = LODNear;
	currentDetailBalance = 1.0f;
	for(int i = 0; i < layerCount; i++)
	{
		selection.SetVisibilityRangeAt((layerCount - i - 1), (previousPosition + section * currentDetailBalance));
		previousPosition = selection.GetVisibilityRangeAt((layerCount - i - 1));
		currentDetailBalance *= detailBalance;
	}

	previousPosition = LODNear;
	for(int i = 0; i < layerCount; i++)
	{
		int index = layerCount - i - 1;
		selection.SetMorphEndValueAt(i, selection.GetVisibilityRangeAt(index));
		selection.SetMorphStartValueAt(i, previousPosition + (selection.GetMorphEndRange(i) - previousPosition) * selection.GetMorphStartRatio());

		previousPosition = selection.GetMorphStartRange(i);
	}
	//TODO:: TEMP
	/*
	float _morphStart[CDLODSettings::MaxLevelCount];
	float _morphEnd[CDLODSettings::MaxLevelCount];
	for(int i = 0; i < layerCount; i++)
	{
		_morphStart[i] = selection.GetMorphStartRange(i);
		_morphEnd[i] = selection.GetMorphEndRange(i);
	}
	for(int i = 0; i < layerCount; i++)
	{
		selection.SetMorphStartValueAt(i, _morphEnd[i]);
		selection.SetMorphEndValueAt(i, _morphStart[i]);
	}
	*/

	//Select the nodes
	for(int y = 0; y < _topNodeCountY; y++)
	{
		for(int x = 0; x < _topNodeCountX; x++)
		{
			_topLevelNodes[y][x]->Select(selection, false);
		}
	}

	selection.SetMinSelectedLODLevel(0);
	selection.SetMaxSelectedLODLevel(CDLODSettings::MaxLevelCount);

	CDLODSelectedNode* selectionBuffer = selection.GetSelectionBuffer();
	for(int i = 0; i < selection.GetSelectionCount(); i++)
	{
		BoundingBox boundingBox = selectionBuffer[i].GetBoundingBox(_rasterSizeX, _rasterSizeY, _createDescription._mapDimensions);

		if(selection.ShouldSortByDistance())
		{
			selectionBuffer[i]._minDistanceToCamera = sqrtf(boundingBox.GetMinDistanceFromPointSquared(selection.GetObserverPosition()));
		}
		else
		{
			selectionBuffer[i]._minDistanceToCamera = 0.0f;
		}

		selection.SetMinSelectedLODLevel(std::min(selection.GetMinSelectedLODLevel(), selectionBuffer[i]._level));
		selection.SetMaxSelectedLODLevel(std::max(selection.GetMaxSelectedLODLevel(), selectionBuffer[i]._level));
	}

	if(selection.ShouldSortByDistance())
	{
		selection.SortSelectedNodesByDistance();
	}
	//TODO: REMOVE
	int hej = 0;
}
int CDLODQuadTree::GetRasterSizeX()const
{
	return _rasterSizeX;
}
int CDLODQuadTree::GetRasterSizeY()const
{
	return _rasterSizeY;
}
