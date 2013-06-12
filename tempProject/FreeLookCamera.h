//FreeLookCamera.h
#ifndef FREELOOKCAMERA_H_INCLUDED
#define FREELOOKCAMERA_H_INCLUDED

#include "Component.h"
#include "InputManager.h"

class FreeLookCamera : public Component
{
public:
	FreeLookCamera(GameObject* owner): Component(owner, ComponentUpdateStep::DefaultUpdate()){}
	virtual ~FreeLookCamera(){}

	virtual void Start()
	{
		cameraComponent = (Camera*)GetGameObject()->GetComponent(typeid(Camera));

		originalMousePosition = Vector2(1280 / 2, 720 / 2);
		InputManager::SetMousePosition(originalMousePosition);

		_leftRightRotation = 3.14f * 0.5f;
		_upDownRotation = 3.14f * 0.1f;
		_rotationSpeed = 0.3f;
		_moveSpeed = 30.0f;
	}

	virtual void Update(GameTime* gameTime)
	{
		ProcessCameraInput(gameTime);

		Vector3 cameraPosition = GetGameObject()->GetTransform().GetPosition();
		Matrix4x4 cameraRotation = Matrix4x4::GetRotationX(_upDownRotation) * Matrix4x4::GetRotationY(_leftRightRotation);
		Vector3 cameraOriginalTarget(0, 0, 1);
		Vector3 cameraRotatedTarget = Matrix4x4::Transform(cameraOriginalTarget, cameraRotation);
		Vector3 cameraFinalTarget = cameraPosition + cameraRotatedTarget;

		Vector3 cameraOriginalUpVector = Vector3::Up();
		Vector3 cameraRotatedUpVector = Matrix4x4::Transform(cameraOriginalUpVector, cameraRotation);

		cameraComponent->SetUpVector(cameraRotatedUpVector);
		cameraComponent->SetLookAt(cameraFinalTarget);
	}

private:
	Camera* cameraComponent;
	Vector2 originalMousePosition;
	float _leftRightRotation;
	float _upDownRotation;
	float _rotationSpeed;
	float _moveSpeed;

	void ProcessCameraInput(GameTime* gameTime)
	{
		//Mouse
		if(InputManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
		{
			Vector2 currentMousePosition = InputManager::GetMousePosition();
			if(currentMousePosition != originalMousePosition)
			{
				float xDifference = (currentMousePosition._x - originalMousePosition._x) * gameTime->GetElapsedGameTime();
				float yDifference = (currentMousePosition._y - originalMousePosition._y) * gameTime->GetElapsedGameTime();
				_leftRightRotation -= (_rotationSpeed * xDifference);
				_upDownRotation += (_rotationSpeed * yDifference);
				InputManager::SetMousePosition(originalMousePosition);
			}
		}

		//Keyboard
		Vector3 moveVector(0, 0, 0);
		if(InputManager::IsKeyPressed(GLFW_KEY_RIGHT) || InputManager::IsKeyPressed('D'))
		{
			moveVector += Vector3(-1, 0, 0);
		}
		if(InputManager::IsKeyPressed(GLFW_KEY_LEFT) || InputManager::IsKeyPressed('A'))
		{
			moveVector += Vector3(1, 0, 0);
		}
		if(InputManager::IsKeyPressed(GLFW_KEY_UP) || InputManager::IsKeyPressed('W'))
		{
			moveVector += Vector3(0, 0, 1);
		}
		if(InputManager::IsKeyPressed(GLFW_KEY_DOWN) || InputManager::IsKeyPressed('S'))
		{
			moveVector += Vector3(0, 0, -1);
		}
		if(InputManager::IsKeyPressed('Q'))
		{
			moveVector += Vector3(0, 1, 0);
		}
		if(InputManager::IsKeyPressed('Z'))
		{
			moveVector += Vector3(0, -1, 0);
		}

		//Add to camera position
		Matrix4x4 cameraRotation = Matrix4x4::GetRotationX(_upDownRotation) * Matrix4x4::GetRotationY(_leftRightRotation);
		Vector3 rotatedVector = Matrix4x4::Transform(moveVector, cameraRotation);
		Vector3 position = GetGameObject()->GetTransform().GetPosition();
		position += (rotatedVector * _moveSpeed) * gameTime->GetElapsedGameTime();
		GetGameObject()->GetTransform().SetPosition(position);
	}
};
#endif //FREELOOKCAMERA_H_INCLUDED