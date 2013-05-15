//GameObject.h
#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <vector>
#include "Transform.h"
#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Transform& GetTransform();
	Component* AddComponent(Component* component);
	const std::vector<Component*>& GetComponents()const;
	void Update();
private:
	Transform _transform;
	std::vector<Component*> _components;
};
#endif //GAMEOBJECT_H_INCLUDED