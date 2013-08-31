//CDLODSelection.cpp
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#include "CDLODSelection.h"
#include "CDLODNode.h"
#include "Camera.h"
#include "GameObject.h"

//sorting function
int CompareCloserFirst(const void* arg1, const void* arg2)
{
	const CDLODSelectedNode* a = (const CDLODSelectedNode*)arg1;
	const CDLODSelectedNode* b = (const CDLODSelectedNode*)arg2;

	return a->_minDistanceToCamera < b->_minDistanceToCamera;
}

//CDLODSelectedNode
CDLODSelectedNode::CDLODSelectedNode(){}
CDLODSelectedNode::CDLODSelectedNode(const CDLODNode* node, int level, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight):
	_level(level), _topLeft(topLeft), _topRight(topRight), _bottomLeft(bottomLeft), _bottomRight(bottomRight)
{
	this->_x = node->GetX();
	this->_y = node->GetY();
	this->_size = node->GetSize();
	this->_minHeight = node->GetMinHeight();
	this->_maxHeight = node->GetMaxHeight();
}
BoundingBox CDLODSelectedNode::GetBoundingBox(int rasterSizeX, int rasterSizeY, const MapDimensions& mapDimensions)const
{
	Vector3 min;
	Vector3 max;
	min._x = mapDimensions._min._x + this->_x * mapDimensions._size._x / (float)(rasterSizeX-1);
	max._x = mapDimensions._min._x + (this->_x + this->_size) * mapDimensions._size._x / (float)(rasterSizeX-1);
	min._z = mapDimensions._min._z + this->_y * mapDimensions._size._z / (float)(rasterSizeY-1);
	max._z = mapDimensions._min._z + (this->_y + this->_size) * mapDimensions._size._z / (float)(rasterSizeY-1);
	min._y = mapDimensions._min._y + this->_minHeight;// * mapDimensions._size._y / 65535.0f;
	max._y = mapDimensions._min._y + this->_maxHeight;// * mapDimensions._size._y / 65535.0f;



	return BoundingBox(((min + max) * 0.5f),((max - min) * 0.5f));
}

//CDLODSelection
CDLODSelection::CDLODSelection(int maxNodeSelectionCount, Camera* cameraComponent, 
							   float visibilityDistance, float LODDistanceRatio, float morphStartRatio, bool sortByDistance): 
								_cameraComponent(cameraComponent), _maxNodeSelectionCount(maxNodeSelectionCount), 
								_visibilityDistance(visibilityDistance), _LODDistanceRatio(LODDistanceRatio),
								_morphStartRatio(morphStartRatio), _sortByDistance(sortByDistance)
{
	_selectionBuffer = new CDLODSelectedNode[maxNodeSelectionCount];
	_selectionCount = 0;
	_isVisibleDistanceTooSmall = false;
	_minSelectedLODLevel = 0;
	_maxSelectedLODLevel = 0;
	_stopAtLevel = 8;
}
CDLODSelection::~CDLODSelection()
{
	if(_selectionBuffer != NULL)
	{
		delete [] _selectionBuffer;
	}
}

void CDLODSelection::SortSelectedNodesByDistance()
{
	qsort(_selectionBuffer, _selectionCount, sizeof(*_selectionBuffer), CompareCloserFirst);
}

bool CDLODSelection::IsVisibleDistanceTooSmall()const
{
	return _isVisibleDistanceTooSmall;
}
bool CDLODSelection::ShouldSortByDistance()const
{
	return _sortByDistance;
}
const BoundingFrustum* CDLODSelection::GetCameraFrustum()const
{
	return &_cameraComponent->GetFrustum();
}
const Vector3& CDLODSelection::GetObserverPosition()const
{
	return _cameraComponent->GetGameObject()->GetTransform().GetPosition();
}
float CDLODSelection::GetVisibilityRangeAt(int level)const
{
	return _visibilityRanges[level];
}
int CDLODSelection::GetStopAtLevel()const
{
	return _stopAtLevel;
}
int CDLODSelection::GetMaxNodeSelectionCount()const
{
	return _maxNodeSelectionCount;
}
int CDLODSelection::GetSelectionCount()const
{
	return _selectionCount;
}
void CDLODSelection::SetSelectionCount(int selectionCount)
{
	_selectionCount = selectionCount;
}
CDLODSelectedNode* CDLODSelection::GetSelectionBuffer()
{
	return _selectionBuffer;
}
float CDLODSelection::GetMorphStartRange(int level)const
{
	return _morphStart[level];
}
float CDLODSelection::GetMorphEndRange(int level)const
{
	return _morphEnd[level];
}
float CDLODSelection::GetMorphStartRatio()const
{
	return _morphStartRatio;
}
void CDLODSelection::SetIsVisibleDistanceTooSmall(bool isVisibleDistanceTooSmall)
{
	_isVisibleDistanceTooSmall = isVisibleDistanceTooSmall;
}
const CreateDescription* CDLODSelection::GetCreateDescription()const
{
	return _createDescription;
}
float CDLODSelection::GetVisibilityDistance()const
{
	return _visibilityDistance;
}
float CDLODSelection::GetLODDistanceRatio()const
{
	return _LODDistanceRatio;
}
unsigned int CDLODSelection::GetMaxSelectedLODLevel()const
{
	return _maxSelectedLODLevel;
}
unsigned int CDLODSelection::GetMinSelectedLODLevel()const
{
	return _minSelectedLODLevel;
}
void CDLODSelection::SetVisibilityRangeAt(int level, float visibilityRange)
{
	_visibilityRanges[level] = visibilityRange;
}
void CDLODSelection::SetVisibilityDistance(float visibilityDistance)
{
	_visibilityDistance = visibilityDistance;
}
void CDLODSelection::SetMorphEndValueAt(int level, float morphEndValue)
{
	_morphEnd[level] = morphEndValue;
}
void CDLODSelection::SetMorphStartValueAt(int level, float morphStartValue)
{
	_morphStart[level] = morphStartValue;
}
void CDLODSelection::SetMinSelectedLODLevel(int minSelectedLODLevel)
{
	_minSelectedLODLevel = minSelectedLODLevel;
}
void CDLODSelection::SetMaxSelectedLODLevel(int maxSelectedLODLevel)
{
	_maxSelectedLODLevel = maxSelectedLODLevel;
}
void CDLODSelection::SetCreateDescription(CreateDescription* createDescription)
{
	_createDescription = createDescription;
}
void CDLODSelection::SetStopAtLevel(int stopAtLevel)
{
	_stopAtLevel = stopAtLevel;
}
Vector4 CDLODSelection::GetMorphConsts(int level)const
{
	float start = _morphStart[level];
	float end = _morphEnd[level];

	end = end + (start - end) * 0.01f; //lerp

	return Vector4(
		start, 
		1.0f / (end- start), 
		end / (end-start),  
		1.0f / (end- start));
}