//Transform.h
#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

class Transform
{
public:
	Transform();
	~Transform();

	const Vector3& GetScale();
	const Vector3 GetRotationEuler()const;
	const Vector3& GetPosition();
	const Matrix4x4& GetWorldMatrix();
	const Vector3& GetForward();
	const Vector3& GetRight();
	const Vector3& GetUp();
	void SetScale(float x, float y, float z);
	void SetScale(const Vector3& scale);
	void SetRotationEuler(float x, float y, float z);
	void SetRotationEuler(const Vector3& eulerAngles);
	void SetRotation(const Quaternion& rotation);
	void SetPosition(float x, float y, float z);
	void SetPosition(const Vector3& position);
	void SetParent(Transform* parent);
	
	void Rotate(const Vector3& axis, const float angleInRadians);
private:
	Matrix4x4 _scaleMatrix;
	Matrix4x4 _positionMatrix;
	Matrix4x4 _rotationMatrix;
	Matrix4x4 _worldMatrix;
	Quaternion _rotation; 
	Vector3 _positionVector;
	Vector3 _scaleVector;
	Transform* _parent;
	Vector3 _up;
	Vector3 _right;
	Vector3 _forward;
	bool _didChange;

	void CalculateWorldMatrix();
};
#endif //TRANSFORM_H_INCLUDED