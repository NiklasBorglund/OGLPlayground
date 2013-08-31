//RenderEngine2D.h
#ifndef RENDERENGINE2D_H_INCLUDED
#define RENDERENGINE2D_H_INCLUDED

#include <vector>

class GameTime;
class Renderer;
class Camera;
class GLFWWindow;
class GraphicsDevice;
class RenderEngine2D
{
public:
	RenderEngine2D();
	~RenderEngine2D();

	void Initialize(Camera* camera2DComponent, GLFWWindow* thisWindow, GraphicsDevice* graphicsDevice);

	void Start();
	void Update(GameTime* gameTime);
	void Shutdown();

	void AddRenderingComponent(Renderer* renderComponent);

	int GetDrawCalls()const;
	int GetTriangleCount()const;

private:
	std::vector<Renderer*> _renderingUpdateStep;
	int _drawCalls;
	int _trianglesDrawn;
	GraphicsDevice* _graphicsDevice;

	//Weak pointers to the window and the 2D camera
	GLFWWindow* _thisWindow;
	Camera* _camera2DComponent;
};
#endif //RENDERENGINE2D_H_INCLUDED