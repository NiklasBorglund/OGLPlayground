//Transform.cpp
#include "Transform.h"

Transform::Transform(): _scale(1.0f), _rotation(0.0f), _position(0.0f), _worldMatrix(Matrix4x4::Identity()), _didChange(false)
{}
Transform::~Transform(){}

const Vector3& Transform::GetScale()const{return this->_scale;}
const Vector3& Transform::GetRotation()const{return this->_rotation;}
const Vector3& Transform::GetPosition()const{return this->_position;}
const Matrix4x4& Transform::GetWorldMatrix()
{
	if(this->_didChange)
	{
		_worldMatrix.SetScale(_scale);
		_worldMatrix *= (Matrix4x4::GetRotationZ(_rotation._z) * Matrix4x4::GetRotationY(_rotation._y) * Matrix4x4::GetRotationX(_rotation._x));
		_worldMatrix *= Matrix4x4::GetTranslationMatrix(_position._x, _position._y, _position._z);
		this->_didChange = false;
	}
	return this->_worldMatrix;
}
void Transform::SetScale(float x, float y, float z)
{
	_scale._x = x;
	_scale._y = y;
	_scale._z = z;
	this->_didChange = true;
}
void Transform::SetRotation(float x, float y, float z)
{
	_rotation._x = x;
	_rotation._y = y;
	_rotation._z = z;
	this->_didChange = true;
}
void Transform::SetPosition(float x, float y, float z)
{
	_position._x = x;
	_position._y = y;
	_position._z = z;
	this->_didChange = true;
}