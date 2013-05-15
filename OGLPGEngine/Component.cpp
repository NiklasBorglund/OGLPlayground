//Component.cpp
#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* owner, ComponentUpdateStep updateStep): _owner(owner), _updateStep(updateStep.GetUpdateStep()){}
Component::~Component(){}

void Component::Start(){}
void Component::Update(){}
void Component::Shutdown(){}

GameObject* Component::GetGameObject()const
{
	return this->_owner;
}
const UpdateStep Component::GetUpdateStep()const
{
	return _updateStep;
}