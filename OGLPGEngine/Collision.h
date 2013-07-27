//Collision.h
//Helper class for collision checks
#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "BoundingBox.h"
#include "BoundingFrustum.h"
#include <math.h>

enum CollisionType
{
	CONTAINS = 1,
	INTERSECTS = 2,
	DISJOINT = 3,
};

class Collision
{
public:
	static inline CollisionType Contains(const BoundingBox& boxA, const BoundingBox& boxB)
	{
		float bottomA = boxA._center._y - boxA._halfSize._y;
		float topA = boxA._center._y + boxA._halfSize._y;
		float leftA = boxA._center._x - boxA._halfSize._x;
		float rightA = boxA._center._x + boxA._halfSize._x;
		float nearA = boxA._center._z - boxA._halfSize._z;
		float farA = boxA._center._z + boxA._halfSize._z;

		float bottomB = boxB._center._y - boxB._halfSize._y;
		float topB = boxB._center._y + boxB._halfSize._y;
		float leftB = boxB._center._x - boxB._halfSize._x;
		float rightB = boxB._center._x + boxB._halfSize._x;
		float nearB = boxB._center._z - boxB._halfSize._z;
		float farB = boxB._center._z + boxB._halfSize._z;

		if (topA > bottomB && bottomA < topB && leftA < rightB && rightA > leftB && farA > nearB && nearA < farB)
		{
			if (topA >= topB && bottomA <= bottomB && leftA <= leftB && rightA >= rightB && nearA <= nearB && farA >= farB)
			{
				return CONTAINS;
			}
			return INTERSECTS;
		}
		return DISJOINT;
	}
	static inline CollisionType Contains(const BoundingBox& box, const BoundingFrustum& frustum)
	{
		CollisionType result = CONTAINS;
		for(int i = 0; i < 6; i++)
		{
			//is the positive vertex outside
			if(frustum._planes[i].SignedDistanceTo(box.GetVertexPositive(frustum._planes[i]._normal)) < 0)
			{
				return DISJOINT;
			}

			if(frustum._planes[i].SignedDistanceTo(box.GetVertexNegative(frustum._planes[i]._normal)) < 0)
			{
				return INTERSECTS;
			}
		}
		return result;
	}
	//box - sphere
	static inline bool Intersects(const BoundingBox& box, const Vector3& sphereCenter, float sphereRadiusSquared)
	{
		return box.GetMinDistanceFromPointSquared(sphereCenter) <= sphereRadiusSquared;
	}
private:
	Collision();
	~Collision();
};
#endif //COLLISION_H_INCLUDED