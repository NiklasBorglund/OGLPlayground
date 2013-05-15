//RotateObject.h
//Test component
#ifndef ROTATEOBJECT_H_INCLUDED
#define ROTATEOBJECT_H_INCLUDED

#include "Component.h"
class RotateObject: public Component
{
public:
	RotateObject(GameObject* owner): Component(owner, ComponentUpdateStep::DefaultUpdate()), _rotation(0.0f){}
	virtual ~RotateObject(){}

	virtual void Update()
	{
		_rotation += 0.01f;
		Vector3 rotation = GetGameObject()->GetTransform().GetRotation();
		rotation._x = _rotation;
		GetGameObject()->GetTransform().SetRotation(rotation._x, rotation._y, rotation._z);
	}

private:
	float _rotation;
};

#endif //ROTATEOBJECT_H_INCLUDED