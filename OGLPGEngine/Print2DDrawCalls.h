//Print2DDrawCalls.h
#ifndef PRINT2DDRAWCALLS_H_INCLUDED
#define PRINT2DDRAWCALLS_H_INCLUDED

#include "Component.h"
#include "FontRenderer.h"
#include "GameObject.h"
#include "RenderEngine2D.h"

class Print2DDrawCalls : public Component
{
public:
	Print2DDrawCalls(GameObject* owner, RenderEngine2D* renderer): Component(owner, ComponentUpdateStep::DefaultUpdate()), _renderer(renderer){}
	virtual ~Print2DDrawCalls(){}

	virtual void Start()
	{
		_fontRenderer = (FontRenderer*)GetGameObject()->GetComponent(typeid(FontRenderer));
	}

	virtual void Update(GameTime* gameTime)
	{
		if(_fontRenderer != NULL && _renderer != NULL)
		{
			_drawCalls = "Draw Calls(2D): " + std::to_string(_renderer->GetDrawCalls());
			_fontRenderer->SetText(_drawCalls);
		}
	}
private:
	FontRenderer* _fontRenderer;
	RenderEngine2D* _renderer;
	std::string _drawCalls;
};

#endif //PRINT2DDRAWCALLS_H_INCLUDED