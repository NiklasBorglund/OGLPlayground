//Renderer.h
#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <vector>

#include "Component.h"
#include "BoundingBox.h"
#include "GameObject.h"

class Camera;
class Renderer: public Component
{
public:
	Renderer(GameObject* owner, ComponentUpdateStep updateStep) : Component(owner, updateStep), _numberOfDrawCalls(0), _numberOfTriangles(0){}
	virtual ~Renderer(){}

	virtual void PreDraw(Camera* currentCameraComponent) = 0;
	virtual void Update(GameTime* gameTime) = 0; //<---Draw
	virtual void PostDraw() = 0;
	virtual void GetDebugBoundingBoxes(std::vector<DebugBoundingBox>& boxArray)
	{
		boxArray.push_back(DebugBoundingBox(GetScaledBoundingBox(), Color::Gray()));
	}

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
	const BoundingBox& GetScaledBoundingBox()
	{
		const Vector3& thisPosition = GetGameObject()->GetTransform().GetPosition();
		const Vector3& thisScale = GetGameObject()->GetTransform().GetScale();
		_scaledBoundingBox._center = thisPosition + (_originalBoundingBox._center * thisScale);
		_scaledBoundingBox._halfSize = _originalBoundingBox._halfSize * thisScale;
		return _scaledBoundingBox;
	}
	void SetOriginalBoundingBox(const BoundingBox& originalBoundingBox)
	{
		_originalBoundingBox = originalBoundingBox;
	}
	void SetOriginalBoundingBox(const Vector3& newPosition, const Vector3& newSize)
	{
		_originalBoundingBox._center = newPosition;
		_originalBoundingBox._halfSize = newSize;
	}

private:
	int _numberOfDrawCalls;
	int _numberOfTriangles;
	BoundingBox _scaledBoundingBox; //Scaled and positioned
	BoundingBox _originalBoundingBox;
};
#endif //RENDERER_H_INCLUDED