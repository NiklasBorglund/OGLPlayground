//RenderEngine.h
#ifndef RENDERENGINE_H_INCLUDED
#define RENDERENGINE_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

#include "GLFWWindow.h"
#include <vector>

class Color;
class Component;
class Camera;
class GameTime;
class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();

	void Initialize(Camera* cameraComponent);
	void Start(); //will be run just before the first update
	void Update(GameTime* gameTime);
	void Shutdown();
	void SetClearColor(const Color& color);
	void ClearBuffers();
	void SwapBuffers();

	void AddRenderingComponent(Component* component);
    Camera* GetCameraComponent()const;

	const GLFWWindow& GetWindow()const;
private:
	GLFWWindow _thisWindow;
	GLuint _vertexArrayObject;
	std::vector<Component*> _renderingUpdateStep;

	Camera* _mainCameraComponent; 	//weak pointer to the main camera component
};

#endif //RENDERENGINE_H_INCLUDED