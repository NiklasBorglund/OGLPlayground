//RenderEngine.cpp
#include "RenderEngine.h"

#include "Color.h"

RenderEngine::RenderEngine(): _vertexArrayObject(0)
{

}
RenderEngine::~RenderEngine()
{

}
void RenderEngine::Initialize()
{
	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
}
void RenderEngine::Update()
{
}
void RenderEngine::Shutdown()
{
	if(glIsVertexArray(_vertexArrayObject))
	{
		glDeleteVertexArrays(1,&_vertexArrayObject);
	}
}

void RenderEngine::SetClearColor(const Color& color)
{
	glClearColor(color._r,color._g,color._b,color._a);
}