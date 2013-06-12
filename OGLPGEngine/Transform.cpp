//Transform.cpp
#include "Transform.h"

Transform::Transform(): _scaleMatrix(Matrix4x4::Identity()), _positionMatrix(Matrix4x4::Identity()),
						_rotationMatrix(Matrix4x4::Identity()),_worldMatrix(Matrix4x4::Identity()),
						_rotation(Quaternion::Identity()), _positionVector(0.0f),_scaleVector(0.0f),
						_up(0.0f), _right(0.0f), _forward(0.0f), _didChange(false)
{}
Transform::~Transform(){}

const Vector3& Transform::GetScale()
{
	_scaleVector._x = _scaleMatrix._11;
	_scaleVector._y = _scaleMatrix._22;
	_scaleVector._z = _scaleMatrix._33;
	return _scaleVector;
}
const Vector3 Transform::GetRotationEuler()const{return this->_rotation.ToEuler();}
const Vector3& Transform::GetPosition()
{
	_positionVector._x = _positionMatrix._41;
	_positionVector._y = _positionMatrix._42;
	_positionVector._z = _positionMatrix._43;
	return _positionVector;
}
const Matrix4x4& Transform::GetWorldMatrix()
{
	CalculateWorldMatrix();
	return this->_worldMatrix;
}
const Vector3& Transform::GetForward()
{
	CalculateWorldMatrix();
	_forward._x = _worldMatrix._31;
	_forward._y = _worldMatrix._32;
	_forward._z = _worldMatrix._33;
	return _forward;
}
const Vector3& Transform::GetRight()
{
	CalculateWorldMatrix();
	_right._x = _worldMatrix._11;
	_right._y = _worldMatrix._12;
	_right._z = _worldMatrix._13;
	return _right;
}
const Vector3& Transform::GetUp()
{
	CalculateWorldMatrix();
	_up._x = _worldMatrix._21;
	_up._y = _worldMatrix._22;
	_up._z = _worldMatrix._23;
	return _up;
}
void Transform::SetScale(float x, float y, float z)
{
	_scaleMatrix._11 = x;
	_scaleMatrix._22 = y;
	_scaleMatrix._33 = z;
	this->_didChange = true;
}
void Transform::SetRotationEuler(float x, float y, float z)
{
	_rotation.SetFromEuler(x,y,z);
	this->_didChange = true;
}
void Transform::SetRotationEuler(const Vector3& eulerAngles)
{
	_rotation.SetFromEuler(eulerAngles);
	this->_didChange = true;
}
void Transform::SetRotation(const Quaternion& rotation)
{
	this->_rotation = rotation;
	this->_didChange = true;
}
void Transform::SetPosition(float x, float y, float z)
{
	_positionMatrix._41 = x;
	_positionMatrix._42 = y;
	_positionMatrix._43 = z;
	this->_didChange = true;
}
void Transform::SetPosition(const Vector3& position)
{
	SetPosition(position._x, position._y, position._z);
}
void Transform::SetParent(Transform* parent)
{
	this->_parent = parent;
	this->_didChange;
}
void Transform::Rotate(const Vector3& axis, const float angleInRadians)
{
	_rotation = Quaternion::CreateFromAxisAngle(axis,angleInRadians) * _rotation;
	this->_didChange = true;
}
void Transform::CalculateWorldMatrix()
{
	if(this->_didChange || _parent != NULL)
	{
		_rotationMatrix.SetFromQuaternion(_rotation);
		_worldMatrix = _scaleMatrix;
		_worldMatrix *= _rotationMatrix;
		_worldMatrix *= _positionMatrix;

		if(_parent != NULL)
		{
			_worldMatrix = _parent->GetWorldMatrix() * _worldMatrix;
		}

		this->_didChange = false;
	}
}