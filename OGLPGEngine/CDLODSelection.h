//CDLODSelection.h
//http://www.vertexasylum.com/downloads/cdlod/cdlod_latest.pdf
#ifndef CDLODSELECTION_H_INCLUDED
#define CDLODSELECTION_H_INCLUDED

#include "CDLODSettings.h"
#include "Vector4.h"

enum CDLODSelectResult
{
     IT_Undefined,
     IT_OutOfFrustum,
     IT_OutOfRange,
     IT_Selected,
};

class CDLODNode;
class BoundingBox;
struct CDLODSelectedNode
{
	unsigned int _x;
	unsigned int _y;
	unsigned int _size;
	unsigned int _minHeight;
	unsigned int _maxHeight;
	unsigned int _level;
	float _minDistanceToCamera;
	bool _topLeft;
	bool _topRight;
	bool _bottomLeft;
	bool _bottomRight;

	CDLODSelectedNode();
	CDLODSelectedNode(const CDLODNode* node, int level, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight);

	BoundingBox GetBoundingBox(int rasterSizeX, int rasterSizeY, const MapDimensions& mapDimensions)const;
};

class BoundingFrustum;
class Camera;
class CDLODSelection
{
public:
	CDLODSelection(int maxNodeSelectionCount, Camera* cameraComponent, 
		float visibilityDistance, float LODDistanceRatio, float morphStartRatio, bool sortByDistance);
	~CDLODSelection();

	void SortSelectedNodesByDistance();

	bool IsVisibleDistanceTooSmall()const;
	bool ShouldSortByDistance()const;
	const BoundingFrustum* GetCameraFrustum()const;
	const Vector3& GetObserverPosition()const;
	float GetVisibilityRangeAt(int level)const;
	int GetStopAtLevel()const;
	int GetMaxNodeSelectionCount()const;
	int GetSelectionCount()const;
	CDLODSelectedNode* GetSelectionBuffer();
	float GetMorphStartRange(int level)const;
	float GetMorphEndRange(int level)const;
	float GetMorphStartRatio()const;
	const CreateDescription* GetCreateDescription()const;
	float GetVisibilityDistance()const;
	float GetLODDistanceRatio()const;
	unsigned int GetMaxSelectedLODLevel()const;
	unsigned int GetMinSelectedLODLevel()const;
	Vector4 GetMorphConsts(int level)const;

	void SetSelectionCount(int selectionCount);
	void SetIsVisibleDistanceTooSmall(bool isVisibleDistanceTooSmall);
	void SetVisibilityRangeAt(int level, float visibilityRange);
	void SetVisibilityDistance(float visibilityDistance);
	void SetMorphEndValueAt(int level, float morphEndValue);
	void SetMorphStartValueAt(int level, float morphStartValue);
	void SetMinSelectedLODLevel(int minSelectedLODLevel);
	void SetMaxSelectedLODLevel(int maxSelectedLODLevel);
	void SetCreateDescription(CreateDescription* createDescription);
	void SetStopAtLevel(int stopAtLevel);

private:
	//Input
	Camera* _cameraComponent;
	CDLODSelectedNode* _selectionBuffer;
	int _maxNodeSelectionCount;
	float _visibilityDistance;
	float _LODDistanceRatio;
	float _morphStartRatio;
	bool _sortByDistance;
	int _stopAtLevel;
	CreateDescription* _createDescription;

	//Output
	float _visibilityRanges[CDLODSettings::MaxLevelCount];
	float _morphEnd[CDLODSettings::MaxLevelCount];
	float _morphStart[CDLODSettings::MaxLevelCount];
	int _selectionCount;
	bool _isVisibleDistanceTooSmall;
	unsigned int _minSelectedLODLevel;
	unsigned int _maxSelectedLODLevel;
};


#endif //CDLODSELECTION_H_INCLUDED