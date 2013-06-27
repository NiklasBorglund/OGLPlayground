//Camera.h
//Component
#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Component.h"
#include "Matrix4x4.h"
#include "Vector2.h"

enum CameraTypeEnum
{
	CAMERA_PERSPECTIVE = 1,
	CAMERA_ORTHOGRAPHIC = 2,
};

class CameraType
{
public:
	static CameraType Perspective(){return CameraType(CAMERA_PERSPECTIVE);}
	static CameraType Orthographic(){return CameraType(CAMERA_ORTHOGRAPHIC);}

	const CameraTypeEnum GetCameraType() const
	{
		return _cameraType;
	}
private:
	explicit CameraType(CameraTypeEnum cameraType):_cameraType(cameraType){}
	CameraTypeEnum _cameraType;
};

class Camera: public Component
{
public:
	Camera(GameObject* owner, CameraType cameraType);
	virtual ~Camera();

	virtual void Update(GameTime* gameTime);

	const Matrix4x4& GetProjectionMatrix()const;
	const Matrix4x4& GetViewMatrix()const;
	float GetNearClip()const;
	float GetFarClip()const;
	float GetFOVY()const;
	float GetAspectRatio()const;
	const Vector3& GetLookAt()const;
	const Vector3& GetUpVector()const;
	bool IsChanged()const; //Did any of the projection matrix values change?

	void SetNearClip(float nearClip);
	void SetFarClip(float farClip);
	void SetFOVY(float fovy);
	void SetAspectRatio(float aspectRatio);
	void SetAspectRatio(const Vector2& windowSize);
	void SetLookAt(const Vector3& lookAt);
	void SetUpVector(const Vector3& up);
private:
	Matrix4x4 _projectionMatrix;
	Matrix4x4 _viewMatrix;
	float _nearClip;
	float _farClip;
	float _fovy;
	float _aspectRatio;
	Vector2 _windowSize;
	Vector3 _lookAt;
	Vector3 _up;
	CameraTypeEnum _cameraType;
	bool _isChanged;
};

#endif //CAMERA_H_INCLUDED