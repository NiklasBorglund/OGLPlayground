//BoundingBox.h
//AABB
#ifndef BOUNDINGBOX_H_INCLUDED
#define BOUNDINGBOX_H_INCLUDED

#include "Vector3.h"
#include "Color.h"
#include <algorithm>

class BoundingBox
{
public:
	Vector3 _center;
	Vector3 _halfSize;

	BoundingBox(): _center(Vector3::Zero()), _halfSize(Vector3::Zero()){}
	BoundingBox(const Vector3& center, const Vector3& halfSize): _center(center), _halfSize(halfSize){}
	~BoundingBox(){}

	Vector3 Min()const
	{
		return _center - _halfSize;
	}
	Vector3 Max()const
	{
		return _center + _halfSize;
	}

	Vector3 GetVertexPositive(const Vector3& normal)const
	{
		Vector3 positive = Min();
		Vector3 max = Max();
		if(normal._x >= 0)
		{
			positive._x = max._x;
		}
		if(normal._y >= 0)
		{
			positive._y = max._y;
		}
		if(normal._z >= 0)
		{
			positive._z = max._z;
		}
		return positive;
	}
	Vector3 GetVertexNegative(const Vector3& normal)const
	{
		Vector3 negative = Max();
		Vector3 min = Min();
		if(normal._x >= 0)
		{
			negative._x = min._x;
		}
		if(normal._y >= 0)
		{
			negative._y = min._y;
		}
		if(normal._z >= 0)
		{
			negative._z = min._z;
		}
		return negative;
	}

	float GetMinDistanceFromPointSquared(const Vector3& point)const
	{
		Vector3 min = Min();
		Vector3 max = Max();
		float distance = 0.0f;

		if(point._x < min._x)
		{
			float d = point._x - min._x;
			distance += d * d;
		}
		else if(point._x  > max._x)
		{
			float d = point._x - max._x;
			distance += d * d;
		}

		if(point._y  < min._y)
		{
			float d = point._y - min._y;
			distance += d * d;
		}
		else if(point._y  > max._y)
		{
			float d = point._y - max._y;
			distance += d * d;
		}

		if(point._z  < min._z)
		{
			float d = point._z - min._z;
			distance += d * d;
		}
		else if(point._z  > max._z)
		{
			float d = point._z - max._z;
			distance += d * d;
		}

		return distance;
	}
	float GetMaxDistanceFromPointSquared(const Vector3& point) const
	{
		float distance = 0.0f;
		float k;
		Vector3 min = Min();
		Vector3 max = Max();

		k = std::max(fabsf(point._x - min._x), fabsf(point._x - max._x));
		distance += k * k;

		k = std::max(fabsf(point._y - min._y), fabsf(point._y - max._y));
		distance += k * k;

		k = std::max(fabsf(point._z - min._z), fabsf(point._z - max._z));
		distance += k * k;

		return distance;
	}
};

//For bounding box drawing
struct DebugBoundingBox
{
	BoundingBox _boundingBox;
	Color _color;
	DebugBoundingBox(const BoundingBox& boundingBox, const Color& color)
	{
		_boundingBox = boundingBox;
		_color = color;
	}
};

#endif //BOUNDINGBOX_H_INCLUDED