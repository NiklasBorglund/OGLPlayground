//Print3DDrawCalls.h
#ifndef PRINT3DDRAWCALLS_H_INCLUDED
#define PRINT3DDRAWCALLS_H_INCLUDED

#include "Component.h"
#include "FontRenderer.h"
#include "GameObject.h"
#include "RenderEngine.h"

class Print3DDrawCalls : public Component
{
public:
	Print3DDrawCalls(GameObject* owner, RenderEngine* renderer): Component(owner, ComponentUpdateStep::DefaultUpdate()), _renderer(renderer){}
	virtual ~Print3DDrawCalls(){}

	virtual void Start()
	{
		_fontRenderer = (FontRenderer*)GetGameObject()->GetComponent(typeid(FontRenderer));
	}

	virtual void Update(GameTime* gameTime)
	{
		if(_fontRenderer != NULL && _renderer != NULL)
		{
			_drawCalls = "Draw Calls(3D): " + std::to_string(_renderer->GetDrawCalls());
			_fontRenderer->SetText(_drawCalls);
		}
	}
private:
	FontRenderer* _fontRenderer;
	RenderEngine* _renderer;
	std::string _drawCalls;
};

#endif //PRINT3DDRAWCALLS_H_INCLUDED