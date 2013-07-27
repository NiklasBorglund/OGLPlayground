//RenderEngine.h
#ifndef RENDERENGINE_H_INCLUDED
#define RENDERENGINE_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

#include "GLFWWindow.h"
#include <vector>
#include "Quadtree.h"

//Debugging
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "DebugMaterial.h"

class Color;
class Renderer;
class Camera;
class GameTime;
class ResourceManager;
class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();

	void Initialize(Camera* cameraComponent, ResourceManager* resourceManager);
	void Start(); //will be run just before the first update
	void Update(GameTime* gameTime);
	void Shutdown();
	void SetClearColor(const Color& color);
	void ClearBuffers();
	void SwapBuffers();

	void AddRenderingComponent(Renderer* renderComponent);
    Camera* GetCameraComponent()const;

	const GLFWWindow& GetWindow()const;
	GLFWWindow* GetWindowPointer();

	int GetDrawCalls()const;
	int GetTriangleCount()const;
private:
	GLFWWindow _thisWindow;
	GLuint _vertexArrayObject;
	std::vector<Renderer*> _renderingUpdateStep;
	int _drawCalls;
	int _trianglesDrawn;

	Quadtree _quadtree;
	Camera* _mainCameraComponent; 	//weak pointer to the main camera component

	//Input 
	//TODO::Fix better input handling
	bool _previousKeyPressed;
	bool _drawWireframe;
	bool _previousWFKeyPressed;
	void CheckInput();

	//Debug components
	ResourceManager* _resourceManager;
	std::unique_ptr<VertexBuffer> debugVertices;
	std::unique_ptr<IndexBuffer> debugIndices;
	DebugMaterial* debugMaterial;
	Color quadtreeColor;
	Color boxColor;
	std::unique_ptr<GameObject> debugObject;
	std::vector<DebugBoundingBox> quadtreeBoxes;
	std::vector<DebugBoundingBox> _debugBoxes;
	bool _drawDebugObjects;

	void SetupDebugDrawingComponents();
	void DrawDebugObjects();
	void DrawBoundingBox(Renderer* object);
	void DrawBoundingBox(const DebugBoundingBox& box);
	void DrawBoundingBox();
};

#endif //RENDERENGINE_H_INCLUDED