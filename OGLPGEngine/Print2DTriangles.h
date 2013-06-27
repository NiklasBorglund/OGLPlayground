//Print2DTriangles.h
#ifndef PRINT2DTRIANGLES_H_INCLUDED
#define PRINT2DTRIANGLES_H_INCLUDED

#include "Component.h"
#include "FontRenderer.h"
#include "GameObject.h"
#include "RenderEngine2D.h"

class Print2DTriangles : public Component
{
public:
	Print2DTriangles(GameObject* owner, RenderEngine2D* renderer): Component(owner, ComponentUpdateStep::DefaultUpdate()), _renderer(renderer){}
	virtual ~Print2DTriangles(){}

	virtual void Start()
	{
		_fontRenderer = (FontRenderer*)GetGameObject()->GetComponent(typeid(FontRenderer));
	}

	virtual void Update(GameTime* gameTime)
	{
		if(_fontRenderer != NULL && _renderer != NULL)
		{
			_triangles = "Triangles(2D): " + std::to_string(_renderer->GetTriangleCount());
			_fontRenderer->SetText(_triangles);
		}
	}
private:
	FontRenderer* _fontRenderer;
	RenderEngine2D* _renderer;
	std::string _triangles;
};

#endif //PRINT2DTRIANGLES_H_INCLUDED