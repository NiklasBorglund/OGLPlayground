//Quadtree.h
#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include <vector>
#include "BoundingBox.h"
#include "BoundingFrustum.h"
#include "Renderer.h"
/*
struct SpatialRenderPart
{
	Renderer* _renderer;
};
*/
class Quadtree
{
public:
	Quadtree(const BoundingBox& boundingBox, unsigned int nodeCapacity = 4);
	Quadtree(const Vector3& position, const Vector3& size,unsigned int nodeCapacity = 4);
	~Quadtree();

	bool IsLeaf()const; //Is the tree a leaf? i.e no child nodes

	bool Insert(Renderer* renderer);
	void SetParent(Quadtree* parent);
	bool Select(std::vector<Renderer*>& selection, const BoundingFrustum& frustum, bool ignoreVisibilityCheck = false);
	void GetAllBoundingBoxes(std::vector<DebugBoundingBox>& boxes);

private:
	unsigned int _nodeCapacity;
	BoundingBox _boundingBox;

	//Parent node
	Quadtree* _parent;
	//Children
	Quadtree* _topLeft;
	Quadtree* _topRight;
	Quadtree* _bottomLeft;
	Quadtree* _bottomRight;
	int test;

	std::vector<Renderer*> _objects;

	void Subdivide();
	void ReassignObjects();
	void AddWholeNodeToSelection(std::vector<Renderer*>& selection);
};
#endif //QUADTREE_H_INCLUDED