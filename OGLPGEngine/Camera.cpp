//Camera.cpp
#include "Camera.h"
#include "GameObject.h"

Camera::Camera(GameObject* owner): Component(owner, ComponentUpdateStep::DefaultUpdate()),
	_projectionMatrix(Matrix4x4::Identity()), _viewMatrix(Matrix4x4::Identity()),
	_nearClip(0.1f), _farClip(500.0f), _fovy(45.0f), _aspectRatio(1.77f), 
	_lookAt(Vector3::Zero()), _up(Vector3::Up()), _isChanged(true)
{}
Camera::~Camera()
{

}
void Camera::Update(GameTime* gameTime)
{
	if(this->_isChanged)
	{
		_projectionMatrix.SetProjectionMatrixRH(_nearClip, _farClip, _fovy, _aspectRatio);
		this->_isChanged = false;
	}

	//Update the viewMatrix
	_viewMatrix.SetLookAtRH(GetGameObject()->GetTransform().GetPosition(), _lookAt, _up);
}
const Matrix4x4& Camera::GetProjectionMatrix()const {return _projectionMatrix;}
const Matrix4x4& Camera::GetViewMatrix()const{return _viewMatrix;}
float Camera::GetNearClip()const{return _nearClip;}
float Camera::GetFarClip()const{return _farClip;}
float Camera::GetFOVY()const{return _fovy;}
float Camera::GetAspectRatio()const{return _aspectRatio;}
const Vector3& Camera::GetLookAt()const{return _lookAt;}
const Vector3& Camera::GetUpVector()const{return _up;}

void Camera::SetNearClip(float nearClip)
{
	this->_nearClip = nearClip;
	this->_isChanged = true;
}
void Camera::SetFarClip(float farClip)
{
	this->_farClip = farClip;
	this->_isChanged = true;
}
void Camera::SetFOVY(float fovy)
{
	this->_fovy = fovy;
	this->_isChanged = true;
}
void Camera::SetAspectRatio(float aspectRatio)
{
	this->_aspectRatio = aspectRatio;
	this->_isChanged = true;
}
void Camera::SetAspectRatio(const Vector2& windowSize)
{
	SetAspectRatio(windowSize._x / windowSize._y);
}
void Camera::SetLookAt(const Vector3& lookAt)
{
	this->_lookAt = lookAt;
}
void Camera::SetUpVector(const Vector3& up)
{
	this->_up = up;
}