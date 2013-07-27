//Plane.h
#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include "Vector3.h"

class Plane
{
public:
	Vector3 _origin;
	Vector3 _normal;
	float _distance;

	Plane(): _origin(Vector3::Zero()), _normal(Vector3::Zero()), _distance(0.0f)
	{}
	Plane(const Vector3& origin, const Vector3& normal): _origin(origin), _normal(normal)
	{
		_distance = -(Vector3::Dot(_normal, _origin));
	}
	~Plane(){}

	bool IsFrontFacingTo(const Vector3& direction)const
	{
		return (Vector3::Dot(_normal, direction) <= 0);
	}
	float SignedDistanceTo(const Vector3& point)const
	{
		float result = (Vector3::Dot(point,_normal)) + _distance;
		return result;
	}
};
#endif //PLANE_H_INCLUDED