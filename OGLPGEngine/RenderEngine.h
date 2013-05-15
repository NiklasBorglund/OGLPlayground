//RenderEngine.h
#ifndef RENDERENGINE_H_INCLUDED
#define RENDERENGINE_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

class Color;
class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();

	void Initialize();
	void Update();
	void Shutdown();
	void SetClearColor(const Color& color);

private:
	GLuint _vertexArrayObject;
};

#endif //RENDERENGINE_H_INCLUDED