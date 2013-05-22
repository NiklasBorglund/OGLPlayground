//RotateObject.h
//Test component
#ifndef ROTATEOBJECT_H_INCLUDED
#define ROTATEOBJECT_H_INCLUDED

#include "Component.h"
class RotateObject: public Component
{
public:
	RotateObject(GameObject* owner): Component(owner, ComponentUpdateStep::DefaultUpdate()), _rotation(0.01f){}
	virtual ~RotateObject(){}

	virtual void Update()
	{
		GetGameObject()->GetTransform().Rotate(Vector3::Up(), _rotation);
		GetGameObject()->GetTransform().Rotate(Vector3::Right(), _rotation);
		GetGameObject()->GetTransform().Rotate(Vector3::Forward(), _rotation);
	}

private:
	float _rotation;
};

#endif //ROTATEOBJECT_H_INCLUDED