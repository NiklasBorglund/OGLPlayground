//Print3DTriangles.h
#ifndef PRINT3DTRIANGLES_H_INCLUDED
#define PRINT3DTRIANGLES_H_INCLUDED

#include "Component.h"
#include "FontRenderer.h"
#include "GameObject.h"
#include "RenderEngine.h"

class Print3DTriangles : public Component
{
public:
	Print3DTriangles(GameObject* owner, RenderEngine* renderer): Component(owner, ComponentUpdateStep::DefaultUpdate()), _renderer(renderer){}
	virtual ~Print3DTriangles(){}

	virtual void Start()
	{
		_fontRenderer = (FontRenderer*)GetGameObject()->GetComponent(typeid(FontRenderer));
	}

	virtual void Update(GameTime* gameTime)
	{
		if(_fontRenderer != NULL && _renderer != NULL)
		{
			_triangles = "Triangles(3D): " + std::to_string(_renderer->GetTriangleCount());
			_fontRenderer->SetText(_triangles);
		}
	}
private:
	FontRenderer* _fontRenderer;
	RenderEngine* _renderer;
	std::string _triangles;
};

#endif //PRINT3DTRIANGLES_H_INCLUDED