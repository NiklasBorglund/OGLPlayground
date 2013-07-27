//BoundingSphere.h
#ifndef BOUNDINGSPHERE_H_INCLUDED
#define BOUNDINGSPHERE_H_INCLUDED

#include "Vector3.h"

class BoundingSphere
{
public:
	Vector3 _position;
	float _radius;

	BoundingSphere(): _position(Vector3::Zero()), _radius(0.0f)
	{}
	BoundingSphere(const Vector3& position, float radius): _position(position), _radius(radius)
	{}
	~BoundingSphere(){}
};
#endif //BOUNDINGSPHERE_H_INCLUDED