//Renderer.h
#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "Component.h"

class Camera;
class Renderer: public Component
{
public:
	Renderer(GameObject* owner, ComponentUpdateStep updateStep) : Component(owner, updateStep), _numberOfDrawCalls(0), _numberOfTriangles(0){}
	virtual ~Renderer(){}

	virtual void PreDraw(Camera* currentCameraComponent) = 0;
	virtual void Update(GameTime* gameTime) = 0; //<---Draw
	virtual void PostDraw() = 0;

	void SetNumberOfDrawCalls(int drawCalls)
	{
		_numberOfDrawCalls = drawCalls;
	}
	void SetNumberOfTriangles(int trianglesDrawn)
	{
		_numberOfTriangles = trianglesDrawn;
	}
	int GetNumberOfTriangles()const
	{
		return _numberOfTriangles;
	}
	int GetNumberOfDrawCalls()const
	{
		return _numberOfDrawCalls;
	}

private:
	int _numberOfDrawCalls;
	int _numberOfTriangles;
};
#endif //RENDERER_H_INCLUDED