//MoveObject.cpp
#include "MoveObject.h"
#include "InputManager.h"
#include "Vector3.h"
#include "GameObject.h"

MoveObject::MoveObject(GameObject* owner): Component(owner, ComponentUpdateStep::DefaultUpdate()){}
MoveObject::~MoveObject(){}

void MoveObject::Update()
{
	if(InputManager::IsKeyPressed(GLFW_KEY_RIGHT))
	{
		Vector3 position = GetGameObject()->GetTransform().GetPosition();
		position._x += 0.01f;
		GetGameObject()->GetTransform().SetPosition(position);
	}
}