//CDLODNode.cpp
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#include "CDLODNode.h"

#include "Collision.h"
#include <algorithm>

CDLODNode::CDLODNode(): _isLeaf(false) 
{
	this->_topLeft = NULL;
	this->_topRight = NULL;
	this->_bottomLeft = NULL;
	this->_bottomRight = NULL;
}
CDLODNode::~CDLODNode()
{
	if(_topLeft != NULL)
	{
		delete _topLeft;
	}
	if(_topRight != NULL)
	{
		delete _topRight;
	}
	if(_bottomLeft != NULL)
	{
		delete _bottomLeft;
	}
	if(_bottomRight != NULL)
	{
		delete _bottomRight;
	}
}

bool CDLODNode::IsLeaf() const
{
	return _isLeaf;
}

int CDLODNode::GetX()const
{
	return _x;
}
int CDLODNode::GetY()const
{
	return _y;
}
int CDLODNode::GetSize()const
{
	return _size;
}
int CDLODNode::GetLevel()const
{
	return _level;
}
const unsigned int& CDLODNode::GetMinHeight()const
{
	return _minHeight;
}
const unsigned int& CDLODNode::GetMaxHeight()const
{
	return _maxHeight;
}
void CDLODNode::GetWorldMinMaxX(float& minX, float maxX, int rasterSizeX, const MapDimensions& mapDimensions)const
{
	minX   = mapDimensions._min._x + this->_x * mapDimensions._size._x / (float)(rasterSizeX-1);
	maxX   = mapDimensions._min._x + (this->_x + this->_size) * mapDimensions._size._x / (float)(rasterSizeX-1);
}
void CDLODNode::GetWorldMinMaxY(float& minY, float maxY, int rasterSizeY, const MapDimensions& mapDimensions)const
{
	minY   = mapDimensions._min._z + this->_y * mapDimensions._size._z / (float)(rasterSizeY-1);
	maxY   = mapDimensions._min._z + (this->_y + this->_size) * mapDimensions._size._z / (float)(rasterSizeY-1);
}
void CDLODNode::GetWorldMinMaxZ(float& minZ, float maxZ, const MapDimensions& mapDimensions)const
{
	minZ   = mapDimensions._min._y + this->_minHeight;// * mapDimensions._size._y / 65535.0f;
	maxZ   = mapDimensions._min._y + this->_maxHeight;// * mapDimensions._size._y / 65535.0f;
}
void CDLODNode::Create(int x, int y, int size, int level, const CreateDescription& createDescription, CDLODNode* allNodesBuffer, int& allNodesBufferLastIndex)
{
	this->_x = x;
	this->_y = y;
	this->_size = size;
	this->_level = level;

	int heightMapSizeX = createDescription._heightMap->GetSizeX();
	int heightMapSizeY = createDescription._heightMap->GetSizeY();
	
	//Check if this is a leaf node
	if(_size == createDescription._settings._leafNodeSize)
	{
		this->_isLeaf = true;
		//Find the minimum and maximum heights for this terrain patch
		int limitX = std::min(heightMapSizeX, x + size + 1);
		int limitY = std::min(heightMapSizeY, y + size + 1);
		createDescription._heightMap->GetAreaMinMaxHeight(x, y, limitX - x, limitY - y, this->_minHeight, this->_maxHeight);
	}
	else //Create children
	{
		int childSize = size / 2;

		//topLeft
		this->_topLeft = &allNodesBuffer[allNodesBufferLastIndex++];
		this->_topLeft->Create(x, y, childSize, level +1, createDescription, allNodesBuffer, allNodesBufferLastIndex);
		this->_minHeight = this->_topLeft->GetMinHeight();
		this->_maxHeight = this->_topLeft->GetMaxHeight();

		//topRight
		if((x + childSize) < heightMapSizeX)
		{
			this->_topRight = &allNodesBuffer[allNodesBufferLastIndex++];
			this->_topRight->Create(x + childSize, y, childSize, level +1, createDescription, allNodesBuffer, allNodesBufferLastIndex);
			this->_minHeight = std::min(this->_minHeight, this->_topRight->GetMinHeight());
			this->_maxHeight = std::max(this->_maxHeight, this->_topRight->GetMaxHeight());
		}

		//bottomLeft
		if((y + childSize) < heightMapSizeY)
		{
			this->_bottomLeft = &allNodesBuffer[allNodesBufferLastIndex++];
			this->_bottomLeft->Create(x, y + childSize, childSize, level +1, createDescription, allNodesBuffer, allNodesBufferLastIndex);
			this->_minHeight = std::min(this->_minHeight, this->_bottomLeft->GetMinHeight());
			this->_maxHeight = std::max(this->_maxHeight, this->_bottomLeft->GetMaxHeight());
		}

		//bottomRight
		if(((x + childSize) < heightMapSizeX) && ((y + childSize) < heightMapSizeY))
		{
			this->_bottomRight = &allNodesBuffer[allNodesBufferLastIndex++];
			this->_bottomRight->Create(x + childSize, y + childSize, childSize, level +1, createDescription, allNodesBuffer, allNodesBufferLastIndex);
			this->_minHeight = std::min(this->_minHeight, this->_bottomRight->GetMinHeight());
			this->_maxHeight = std::max(this->_maxHeight, this->_bottomRight->GetMaxHeight());
		}
	}
}

CDLODSelectResult CDLODNode::Select(CDLODSelection& selection, bool parentCompletelyInFrustum)const
{
	BoundingBox boundingBox = GetBoundingBox(selection.GetCreateDescription()->_heightMap->GetSizeX(),
						 selection.GetCreateDescription()->_heightMap->GetSizeY(),
						 selection.GetCreateDescription()->_mapDimensions);
	CollisionType frustumCollision = (parentCompletelyInFrustum) ? (CONTAINS): Collision::Contains(boundingBox, *selection.GetCameraFrustum());
	if(frustumCollision == DISJOINT)
	{
		//We are outside the view of the camera frustum
		return IT_OutOfFrustum;
	}

	float distanceLimit = selection.GetVisibilityRangeAt(this->GetLevel());
	if(!Collision::Intersects(boundingBox, selection.GetObserverPosition(), distanceLimit * distanceLimit))
	{
		//We are outside the visible range
		return IT_OutOfRange;
	}

	//Check the child nodes
	CDLODSelectResult topLeftSelectResult = IT_Undefined;
	CDLODSelectResult topRightSelectResult = IT_Undefined;
	CDLODSelectResult bottomLeftSelectResult = IT_Undefined;
	CDLODSelectResult bottomRightSelectResult = IT_Undefined;

	if(this->GetLevel() != selection.GetStopAtLevel()) //Check if we should stop
	{
		float nextDistanceLimit = selection.GetVisibilityRangeAt((this->GetLevel() + 1));
		if(Collision::Intersects(boundingBox, selection.GetObserverPosition(), nextDistanceLimit * nextDistanceLimit))
		{
			bool weAreCompletelyInFrustum = (frustumCollision == CONTAINS);
			if(_topLeft != NULL)
			{
				topLeftSelectResult = this->_topLeft->Select(selection, weAreCompletelyInFrustum);
			}
			if(_topRight != NULL)
			{
				topRightSelectResult = this->_topRight->Select(selection, weAreCompletelyInFrustum);
			}
			if(_bottomLeft != NULL)
			{
				bottomLeftSelectResult = this->_bottomLeft->Select(selection, weAreCompletelyInFrustum);
			}
			if(_bottomRight != NULL)
			{
				bottomRightSelectResult = this->_bottomRight->Select(selection, weAreCompletelyInFrustum);
			}
		}
	}

	// Don't want to select any child nodes that are invisible or selected;
   bool removeTopLeft = (topLeftSelectResult == IT_OutOfFrustum) || (topLeftSelectResult == IT_Selected);
   bool removeTopRight = (topRightSelectResult == IT_OutOfFrustum) || (topRightSelectResult == IT_Selected);
   bool removeBottomLeft = (bottomLeftSelectResult == IT_OutOfFrustum) || (bottomLeftSelectResult == IT_Selected);
   bool removeBottomRight = (bottomRightSelectResult == IT_OutOfFrustum) || (bottomRightSelectResult == IT_Selected);

   if(!(removeTopLeft && removeTopRight && removeBottomLeft && removeBottomRight) && (selection.GetSelectionCount() < selection.GetMaxNodeSelectionCount()))
   {
	   int LODLevel = selection.GetStopAtLevel() - this->GetLevel();
	   selection.GetSelectionBuffer()[selection.GetSelectionCount()] = 
		   CDLODSelectedNode(this, LODLevel, !removeTopLeft, !removeTopRight, !removeBottomLeft, !removeBottomRight);
	   selection.SetSelectionCount(selection.GetSelectionCount() +1);

	   if(this->GetLevel() != 0)
	   {
		   float maxDistanceFromCamera = sqrtf(boundingBox.GetMaxDistanceFromPointSquared(selection.GetObserverPosition()));
		   float morphStartRange = selection.GetMorphStartRange(selection.GetStopAtLevel() - this->GetLevel() +1);
		   if(maxDistanceFromCamera > morphStartRange)
		   {
			   selection.SetIsVisibleDistanceTooSmall(true);
		   }
	   }

	   return IT_Selected;
   }

   //Return selected if any of the children are selected, otherwise all of them are out of frustum
   if((topLeftSelectResult == IT_Selected) ||(topRightSelectResult == IT_Selected) ||
	   (bottomLeftSelectResult == IT_Selected) ||(bottomRightSelectResult == IT_Selected))
   {
	   return IT_Selected;
   }

   return IT_OutOfFrustum;
}

BoundingBox CDLODNode::GetBoundingBox(int rasterSizeX, int rasterSizeY, const MapDimensions& mapDimensions)const
{
	Vector3 min;
	Vector3 max;
	/*
	GetWorldMinMaxX(min._x, max._x, rasterSizeX, mapDimensions);
	GetWorldMinMaxY(min._z, max._z, rasterSizeY, mapDimensions);
	GetWorldMinMaxZ(min._y, max._y, mapDimensions);
	*/
	min._x = mapDimensions._min._x + this->_x * mapDimensions._size._x / (float)(rasterSizeX-1);
	max._x = mapDimensions._min._x + (this->_x + this->_size) * mapDimensions._size._x / (float)(rasterSizeX-1);
	min._z = mapDimensions._min._z + this->_y * mapDimensions._size._z / (float)(rasterSizeY-1);
	max._z = mapDimensions._min._z + (this->_y + this->_size) * mapDimensions._size._z / (float)(rasterSizeY-1);
	min._y = mapDimensions._min._y + this->_minHeight;// * mapDimensions._size._y / 65535.0f;
	max._y = mapDimensions._min._y + this->_maxHeight;// * mapDimensions._size._y / 65535.0f;
	return BoundingBox(((min + max) * 0.5f),((max - min) * 0.5f));
}