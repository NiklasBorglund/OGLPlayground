//Component.h
#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <memory>

enum UpdateStep
{
	UPDATE_DEFAULT = 1,
	UPDATE_RENDER = 2,
};

class ComponentUpdateStep
{
public:
	static ComponentUpdateStep DefaultUpdate(){return ComponentUpdateStep(UPDATE_DEFAULT);}
	static ComponentUpdateStep RenderUpdate(){return ComponentUpdateStep(UPDATE_RENDER);}

	const UpdateStep GetUpdateStep() const
	{
		return _updateStep;
	}
private:
	explicit ComponentUpdateStep(UpdateStep updateStep):_updateStep(updateStep){}
	UpdateStep _updateStep;
};

class GameObject;
class Component
{
public:
	Component(GameObject* owner, ComponentUpdateStep updateStep);
	virtual ~Component();

	virtual void Start();
	virtual void Update();
	virtual void Shutdown();

	GameObject* GetGameObject()const;
	const UpdateStep GetUpdateStep()const;
private:
	GameObject* _owner;
	UpdateStep _updateStep;
};

#endif //COMPONENT_H_INCLUDED