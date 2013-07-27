//Quadtree.cpp
#include "Quadtree.h"
#include "Collision.h"

Quadtree::Quadtree(const BoundingBox& boundingBox, unsigned int nodeCapacity): _boundingBox(boundingBox), _nodeCapacity(nodeCapacity)
{
	_parent = NULL;
	_topLeft = NULL;
	_topRight = NULL;
	_bottomLeft = NULL;
	_bottomRight = NULL;
}
Quadtree::Quadtree(const Vector3& position, const Vector3& size, unsigned int nodeCapacity): _nodeCapacity(nodeCapacity)
{
	_boundingBox = BoundingBox(position, size);
	_parent = NULL;
	_topLeft = NULL;
	_topRight = NULL;
	_bottomLeft = NULL;
	_bottomRight = NULL;
	test = 0;
}
Quadtree::~Quadtree()
{
	if(!IsLeaf())
	{
		delete _topLeft;
		delete _topRight;
		delete _bottomLeft;
		delete _bottomRight;
	}
}

bool Quadtree::IsLeaf()const
{
	return (_topLeft == NULL);
}

bool Quadtree::Insert(Renderer* renderer)
{
	//Check if the bounding box of the tree contains the box of the renderer
	if(Collision::Contains(_boundingBox, renderer->GetScaledBoundingBox()) == CONTAINS)
	{
		test++;
		if(IsLeaf())
		{
			//If this node has the capacity, then just add the object
			if(_objects.size() < _nodeCapacity)
			{
				_objects.push_back(renderer);
				return true;
			}

			//If not, subdivide the tree
			Subdivide();
				
		}

		if(_topLeft->Insert(renderer)) { return true;}
		if(_topRight->Insert(renderer)) { return true;}
		if(_bottomLeft->Insert(renderer)) { return true;}
		if(_bottomRight->Insert(renderer)) { return true;}
	}
	return false;
}
void Quadtree::SetParent(Quadtree* parent)
{
	_parent = parent;
}
bool Quadtree::Select(std::vector<Renderer*>& selection, const BoundingFrustum& frustum, bool ignoreVisibilityCheck)
{
	//We can set this if we know that its parent is completely
	//within the frustum, if that is the case, we can just add the children
	CollisionType collisionType = ignoreVisibilityCheck ? CONTAINS : Collision::Contains(_boundingBox, frustum);

	if(collisionType == DISJOINT)
	{
		return true;
	}
	else
	{
		if(IsLeaf())
		{
			AddWholeNodeToSelection(selection);
			return true;
		}
		else
		{
			if(collisionType == CONTAINS)
			{
				ignoreVisibilityCheck = true;
			}

			_topLeft->Select(selection, frustum, ignoreVisibilityCheck);
			_topRight->Select(selection, frustum, ignoreVisibilityCheck);
			_bottomLeft->Select(selection, frustum, ignoreVisibilityCheck);
			_bottomRight->Select(selection, frustum, ignoreVisibilityCheck);
		}
	}

	return true;
}
void Quadtree::GetAllBoundingBoxes(std::vector<DebugBoundingBox>& boxes)
{
	boxes.push_back(DebugBoundingBox(_boundingBox, Color::Purple()));
	if(IsLeaf())
	{
		return;
	}

	_topLeft->GetAllBoundingBoxes(boxes);
	_topRight->GetAllBoundingBoxes(boxes);
	_bottomLeft->GetAllBoundingBoxes(boxes);
	_bottomRight->GetAllBoundingBoxes(boxes);
}
void Quadtree::Subdivide()
{
	Vector3 halfBoundSize = _boundingBox._halfSize * 0.5f;
	halfBoundSize._y = _boundingBox._halfSize._y;
	Vector3 pos = _boundingBox._center;
	if(halfBoundSize._x != 0 && halfBoundSize._z != 0)
	{

		Vector3 topLeftPosition = Vector3(pos._x - halfBoundSize._x, pos._y, pos._z + halfBoundSize._z);
		Vector3 topRightPosition =  Vector3(pos._x + halfBoundSize._x, pos._y, pos._z + halfBoundSize._z);
		Vector3 bottomLeftPosition =  Vector3(pos._x - halfBoundSize._x, pos._y, pos._z - halfBoundSize._z);
		Vector3 bottomRightPosition =  Vector3(pos._x + halfBoundSize._x, pos._y, pos._z - halfBoundSize._z);

		_topLeft = new Quadtree(topLeftPosition, halfBoundSize, _nodeCapacity);
		_topRight = new Quadtree(topRightPosition, halfBoundSize, _nodeCapacity);
		_bottomLeft = new Quadtree(bottomLeftPosition, halfBoundSize, _nodeCapacity);
		_bottomRight = new Quadtree(bottomRightPosition, halfBoundSize, _nodeCapacity);

		_topLeft->SetParent(this);
		_topRight->SetParent(this);
		_bottomLeft->SetParent(this);
		_bottomRight->SetParent(this);

		//Reassign the objects in the node to the children
		ReassignObjects();
		//_objects.clear();
	}
}

void Quadtree::ReassignObjects()
{
	//std::vector<Renderer*> leftOvers;
	for(unsigned int i = 0; i < _objects.size(); i++)
	{
		if(!_topLeft->Insert(_objects[i]))
		{
			if(!_topRight->Insert(_objects[i]))
			{
				if(!_bottomLeft->Insert(_objects[i])) 
				{
					if(!_bottomRight->Insert(_objects[i]))
					{
						//TODO::HANDLE CASE
					}
				}
			}
		}
	}
	_objects.clear();
}

void Quadtree::AddWholeNodeToSelection(std::vector<Renderer*>& selection)
{
	for(unsigned int i = 0; i < _objects.size(); i++)
	{
		selection.push_back(_objects[i]);
	}
}
