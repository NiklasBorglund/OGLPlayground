//Transform.h
#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "Vector3.h"
#include "Matrix4x4.h"

class Transform
{
public:
	Transform();
	~Transform();

	const Vector3& GetScale()const;
	const Vector3& GetRotation()const;
	const Vector3& GetPosition()const;
	const Matrix4x4& GetWorldMatrix();
	void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetPosition(float x, float y, float z);
private:
	Vector3 _scale;
	Vector3 _rotation; //Todo:: Research and implement Quaternion
	Vector3 _position;
	Matrix4x4 _worldMatrix;
	bool _didChange;
};
#endif //TRANSFORM_H_INCLUDED