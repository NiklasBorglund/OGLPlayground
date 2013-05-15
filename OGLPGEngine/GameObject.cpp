//GameObject.cpp
#include "GameObject.h"

GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}
Transform& GameObject::GetTransform()
{
	return this->_transform;
}
Component* GameObject::AddComponent(Component* component)
{
	if(component != NULL)
	{
		_components.push_back(component);
	}
	return component;
}
const std::vector<Component*>& GameObject::GetComponents()const
{
	return _components;
}
void GameObject::Update()
{
	for(unsigned int i = 0; i < _components.size(); i++)
	{
		_components[i]->Update();
	}
}