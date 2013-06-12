//RenderEngine.cpp
#include "RenderEngine.h"
#include "Component.h"
#include "Color.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Vector2.h"
#include "OpenGLVersion.h"
#include "GameTime.h"

RenderEngine::RenderEngine(): _thisWindow(OpenGLVersion::OpenGL4_3(), GLFWOpenGLProfile::CoreProfile()), _vertexArrayObject(0)
{

}
RenderEngine::~RenderEngine()
{
	Shutdown();
}
void RenderEngine::Initialize(Camera* cameraComponent)
{
	this->_mainCameraComponent = cameraComponent;

	if(!_thisWindow.IsInitialized() ||
		!_thisWindow.OpenWindowAndInitalizeGLEW(1280,720,8,8,8,8,24,8,false))
	{
		//FAILURE
	}

	//Set the aspect ratio
	_mainCameraComponent->SetAspectRatio(_thisWindow.GetWindowSize());

	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
}
void RenderEngine::Start()
{
	for(unsigned int i = 0; i < _renderingUpdateStep.size(); i++)
	{
		_renderingUpdateStep[i]->Start();
	}
}
void RenderEngine::Update(GameTime* gameTime)
{
	//Check if the window resized
	if(_thisWindow.DidWindowResize)
	{
		//Set the new aspect ratio of the camera
		_mainCameraComponent->SetAspectRatio(_thisWindow.GetWindowSize());
	}

	for(unsigned int i = 0; i < _renderingUpdateStep.size(); i++)
	{
		MeshRenderer* currentComponent = static_cast<MeshRenderer*>(_renderingUpdateStep[i]);
		currentComponent->PreDraw(_mainCameraComponent);
		currentComponent->Update(gameTime);//Draw
		currentComponent->PostDraw();
	}
}
void RenderEngine::Shutdown()
{
	if(glIsVertexArray(_vertexArrayObject))
	{
		glDeleteVertexArrays(1,&_vertexArrayObject);
	}
	_renderingUpdateStep.clear();
}
void RenderEngine::SetClearColor(const Color& color)
{
	glClearColor(color._r,color._g,color._b,color._a);
}
void RenderEngine::ClearBuffers()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
void RenderEngine::SwapBuffers()
{
	_thisWindow.SwapBuffers();
}
void RenderEngine::AddRenderingComponent(Component* component)
{
	_renderingUpdateStep.push_back(component);
}
const GLFWWindow& RenderEngine::GetWindow()const
{
	return _thisWindow;
}
Camera* RenderEngine::GetCameraComponent()const
{
	return _mainCameraComponent;
}