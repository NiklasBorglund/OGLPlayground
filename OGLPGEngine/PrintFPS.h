//PrintFPS.h
#ifndef PRINTFPS_H_INCLUDED
#define PRINTFPS_H_INCLUDED

#include "Component.h"
#include "FontRenderer.h"
#include "GameObject.h"

class PrintFPS : public Component
{
public:
	PrintFPS(GameObject* owner): Component(owner, ComponentUpdateStep::DefaultUpdate()){}
	virtual ~PrintFPS(){}

	virtual void Start()
	{
		_fontRenderer = (FontRenderer*)GetGameObject()->GetComponent(typeid(FontRenderer));
	}

	virtual void Update(GameTime* gameTime)
	{
		if(_fontRenderer != NULL)
		{
			_fps = "FPS: " + std::to_string(gameTime->GetFPS());
			_fontRenderer->SetText(_fps);
		}
	}
private:
	FontRenderer* _fontRenderer;
	std::string _fps;
};

#endif //PRINTFPS_H_INCLUDED