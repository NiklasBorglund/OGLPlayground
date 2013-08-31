//RenderEngine2D.cpp
#include "RenderEngine2D.h"
#include "Renderer.h"
#include "GLFWWindow.h"
#include "Camera.h"
#include "GraphicsDevice.h"

RenderEngine2D::RenderEngine2D():  _drawCalls(0), _trianglesDrawn(0)
{
}
RenderEngine2D::~RenderEngine2D()
{
	Shutdown();
}
void RenderEngine2D::Initialize(Camera* camera2DComponent, GLFWWindow* thisWindow, GraphicsDevice* graphicsDevice)
{
	_camera2DComponent = camera2DComponent;
	_thisWindow = thisWindow;
	_graphicsDevice = graphicsDevice;
}
void RenderEngine2D::Start()
{
	for(unsigned int i = 0; i < _renderingUpdateStep.size(); i++)
	{
		_renderingUpdateStep[i]->Start();
	}
}
void RenderEngine2D::Update(GameTime* gameTime)
{
	//Check if the window resized
	if(_thisWindow->DidWindowResize)
	{
		//Set the new aspect ratio of the camera
		_camera2DComponent->SetAspectRatio(_thisWindow->GetWindowSize());
	}
	int triangles = 0;
	int drawCalls = 0;
	for(unsigned int i = 0; i < _renderingUpdateStep.size(); i++)
	{	
		Renderer* currentComponent = _renderingUpdateStep[i];
		currentComponent->PreDraw(_camera2DComponent, _graphicsDevice);
		currentComponent->Update(gameTime, _graphicsDevice);//Draw
		currentComponent->PostDraw(_graphicsDevice);
		triangles += currentComponent->GetNumberOfTriangles();
		drawCalls += currentComponent->GetNumberOfDrawCalls();
	}
	_drawCalls = drawCalls;
	_trianglesDrawn = triangles;
}
void RenderEngine2D::Shutdown()
{
	_renderingUpdateStep.clear();
}
void RenderEngine2D::AddRenderingComponent(Renderer* renderComponent)
{
	_renderingUpdateStep.push_back(renderComponent);
}
int RenderEngine2D::GetDrawCalls()const
{
	return _drawCalls;
}
int RenderEngine2D::GetTriangleCount()const
{
	return _trianglesDrawn;
}