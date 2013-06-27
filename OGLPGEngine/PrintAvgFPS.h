//PrintAvgFPS.h
#ifndef PRINTAVGFPS_H_INCLUDED
#define PRINTAVGFPS_H_INCLUDED

#include "Component.h"
#include "FontRenderer.h"
#include "GameObject.h"

class PrintAvgFPS : public Component
{
public:
	PrintAvgFPS(GameObject* owner): Component(owner, ComponentUpdateStep::DefaultUpdate()){}
	virtual ~PrintAvgFPS(){}

	virtual void Start()
	{
		_fontRenderer = (FontRenderer*)GetGameObject()->GetComponent(typeid(FontRenderer));
	}

	virtual void Update(GameTime* gameTime)
	{
		if(_fontRenderer != NULL)
		{
			_avgFPS = "Avg. FPS: " + std::to_string((int)gameTime->GetAverageFPS());
			_fontRenderer->SetText(_avgFPS);
		}
	}
private:
	FontRenderer* _fontRenderer;
	std::string _avgFPS;
};

#endif //PRINTAVGFPS_H_INCLUDED