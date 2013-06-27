//FontRenderer.h
#ifndef FONTRENDERER_H_INCLUDED
#define FONTRENDERER_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>

#include <memory>
#include <string>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Texture2D.h"

class GameObject;
class Material;
class Font;
class FontRenderer: public Renderer
{
public:
	FontRenderer(GameObject* owner, Material* material, Font* font,
		std::string text, ComponentUpdateStep componentUpdateStep = ComponentUpdateStep::Render2DUpdate());
	virtual ~FontRenderer();

	virtual void PreDraw(Camera* currentCameraComponent);
	virtual void Update(GameTime* gameTime); //<---Draw
	virtual void PostDraw();

	void SetText(std::string text);
private:
	Material* _material;
	Font* _font;
	std::unique_ptr<VertexBuffer> _vertexBuffer;
	std::unique_ptr<Texture2D> _texture;
	std::string _text;
};
#endif //FONTRENDERER_H_INCLUDED