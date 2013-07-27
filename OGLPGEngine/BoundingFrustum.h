//BoundingFrustum.h
#ifndef BOUNDINGFRUSTUM_H_INCLUDED
#define BOUNDINGFRUSTUM_H_INCLUDED

#include "Plane.h"
#include "Matrix4x4.h"

class BoundingFrustum
{
public:
	Plane _planes[6];

	BoundingFrustum(){}
	BoundingFrustum(const Matrix4x4& matrix)
	{
		CalculateFromMatrix(matrix);
	}
	~BoundingFrustum(){}

	void CalculateFromMatrix(const Matrix4x4& matrix)
	{
		//Left
		_planes[0]._normal._x = matrix._14 + matrix._11; 
		_planes[0]._normal._y = matrix._24 + matrix._21; 
		_planes[0]._normal._z = matrix._34 + matrix._31; 
		_planes[0]._distance = matrix._44 + matrix._41;

		//Right 
		_planes[1]._normal._x = matrix._14 - matrix._11; 
		_planes[1]._normal._y = matrix._24 - matrix._21; 
		_planes[1]._normal._z = matrix._34 - matrix._31; 
		_planes[1]._distance = matrix._44 - matrix._41;

		//Top 
		_planes[2]._normal._x = matrix._14 - matrix._12; 
		_planes[2]._normal._y = matrix._24 - matrix._22; 
		_planes[2]._normal._z = matrix._34 - matrix._32; 
		_planes[2]._distance = matrix._44 - matrix._42;

		//Bottom
		_planes[3]._normal._x = matrix._14 + matrix._12; 
		_planes[3]._normal._y = matrix._24 + matrix._22; 
		_planes[3]._normal._z = matrix._34 + matrix._32; 
		_planes[3]._distance = matrix._44 + matrix._42;

		//Near
		_planes[4]._normal._x = matrix._13; 
		_planes[4]._normal._y = matrix._23; 
		_planes[4]._normal._z = matrix._33; 
		_planes[4]._distance = matrix._43;

		//Far
		_planes[5]._normal._x = matrix._14 - matrix._13; 
		_planes[5]._normal._y = matrix._24 - matrix._23; 
		_planes[5]._normal._z = matrix._34 - matrix._33; 
		_planes[5]._distance = matrix._44 - matrix._43;
	}
};
#endif //BOUNDINGFRUSTUM_H_INCLUDED