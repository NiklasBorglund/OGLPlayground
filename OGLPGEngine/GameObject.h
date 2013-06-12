//GameObject.h
#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <vector>
#include "Transform.h"
#include "Component.h"
#include <typeinfo>
#include <typeindex>

class GameObject
{
public:
	GameObject();
	~GameObject();

	Transform& GetTransform();
	Component* AddComponent(Component* component);

	const std::vector<Component*>& GetComponents()const;

	Component* GetComponent(std::type_index type)
	{ 
		for(unsigned int i = 0; i < _components.size(); i++)
		{
			//std::type_index thisType = typeid(*_components[i]);
			Component* thisComponent = _components[i];
			if(type == typeid(*thisComponent))
			{
				return thisComponent;
			}
		}
		return NULL;
	}
private:
	Transform _transform;
	std::vector<Component*> _components;
};
#endif //GAMEOBJECT_H_INCLUDED