//RenderEngine.cpp
#include "RenderEngine.h"
#include "Renderer.h"
#include "Color.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Vector2.h"
#include "OpenGLVersion.h"
#include "GameTime.h"
#include "GraphicsDevice.h"

//Debugging
#include "VertexDeclarations.h"
#include "ResourceManager.h"

#include "InputManager.h"

RenderEngine::RenderEngine(): _thisWindow(OpenGLVersion::OpenGL4_3(), GLFWOpenGLProfile::CoreProfile()),
	_vertexArrayObject(0), _drawCalls(0), _trianglesDrawn(0), _quadtree(Vector3(512, 512, 512), Vector3(512, 512, 512))
{

}
RenderEngine::~RenderEngine()
{
	Shutdown();
}
void RenderEngine::Initialize(Camera* cameraComponent, ResourceManager* resourceManager, GraphicsDevice* graphicsDevice)
{
	this->_mainCameraComponent = cameraComponent;
	this->_resourceManager = resourceManager;
	this->_graphicsDevice = _graphicsDevice;

	if(!_thisWindow.IsInitialized() ||
		!_thisWindow.OpenWindowAndInitalizeGLEW(1280,720,8,8,8,8,24,8,false))
	{
		//FAILURE
	}

	//Set the aspect ratio
	_mainCameraComponent->SetAspectRatio(_thisWindow.GetWindowSize());

	_graphicsDevice->GenerateVertexArrays(1, &_vertexArrayObject);
	_graphicsDevice->BindVertexArray(_vertexArrayObject);

	graphicsDevice->EnableGraphicsMode(GraphicsMode::CullFace());
	graphicsDevice->SetCullMode(CullMode::Back());
	graphicsDevice->SetFrontFace(true);
	graphicsDevice->EnableGraphicsMode(GraphicsMode::DepthTest());


	//Set up debug drawing components (visible bounding boxes etc)
	SetupDebugDrawingComponents();

	_drawDebugObjects = false;
	_previousKeyPressed = false;
	_drawWireframe = false;
	_previousWFKeyPressed = false;
}
void RenderEngine::Start()
{
	for(unsigned int i = 0; i < _renderingUpdateStep.size(); i++)
	{
		_renderingUpdateStep[i]->Start();
	}

	//Get the tree boxes
	_quadtree.GetAllBoundingBoxes(quadtreeBoxes);
}
void RenderEngine::Update(GameTime* gameTime)
{
	//Check if the window resized
	if(_thisWindow.DidWindowResize)
	{
		//Set the new aspect ratio of the camera
		_mainCameraComponent->SetAspectRatio(_thisWindow.GetWindowSize());
	}

	int triangles = 0;
	int drawCalls = 0;

	CheckInput();

	if(_drawWireframe)
	{
		_graphicsDevice->SetPolygonMode(PolygonMode::Line());
	}

	std::vector<Renderer*> selection;
	_quadtree.Select(selection,_mainCameraComponent->GetFrustum());
	for(unsigned int i = 0; i < selection.size(); i++)
	{
		Renderer* currentComponent = selection[i];
		currentComponent->PreDraw(_mainCameraComponent, _graphicsDevice);
		currentComponent->Update(gameTime, _graphicsDevice);//Draw
		currentComponent->PostDraw(_graphicsDevice);
		triangles += currentComponent->GetNumberOfTriangles();
		drawCalls += currentComponent->GetNumberOfDrawCalls();

		if(_drawDebugObjects)
		{
			currentComponent->GetDebugBoundingBoxes(_debugBoxes);
		}
	}

	if(_drawWireframe)
	{
		_graphicsDevice->SetPolygonMode(PolygonMode::Fill());
	}

	DrawDebugObjects();

	selection.clear();
	_drawCalls = drawCalls;
	_trianglesDrawn = triangles;
}
void RenderEngine::Shutdown()
{
	if(_graphicsDevice->IsVertexArray(_vertexArrayObject))
	{
		_graphicsDevice->DeleteVertexArrays(1, &_vertexArrayObject);
	}
	_renderingUpdateStep.clear();
}
void RenderEngine::SetClearColor(const Color& color)
{
	_graphicsDevice->SetClearColor(color);
}
void RenderEngine::ClearBuffers()
{
	_graphicsDevice->ClearBuffers(true, true, false);
}
void RenderEngine::SwapBuffers()
{
	_thisWindow.SwapBuffers();
}
void RenderEngine::AddRenderingComponent(Renderer* renderComponent)
{
	_renderingUpdateStep.push_back(renderComponent);

	//TREE TEST
	_quadtree.Insert(renderComponent);
}
const GLFWWindow& RenderEngine::GetWindow()const
{
	return _thisWindow;
}
GLFWWindow* RenderEngine::GetWindowPointer()
{
	return &_thisWindow;
}
Camera* RenderEngine::GetCameraComponent()const
{
	return _mainCameraComponent;
}
int RenderEngine::GetDrawCalls()const
{
	return _drawCalls;
}
int RenderEngine::GetTriangleCount()const
{
	return _trianglesDrawn;
}

void RenderEngine::CheckInput()
{
	if(InputManager::IsKeyPressed('B'))
	{
		if(!_previousKeyPressed)
		{
			_drawDebugObjects = !_drawDebugObjects;
			_previousKeyPressed = true;
		}
	}
	else
	{
		_previousKeyPressed = false;
	}

	if(InputManager::IsKeyPressed('N'))
	{
		if(!_previousWFKeyPressed)
		{
			_drawWireframe = !_drawWireframe;
			_previousWFKeyPressed = true;
		}
	}
	else
	{
		_previousWFKeyPressed = false;
	}
}

void RenderEngine::SetupDebugDrawingComponents()
{
	VertexPosContainer* vertices = new VertexPosContainer(8);
	vertices->GetVertex(0)._position = Vector3(-0.5f,-0.5f,-0.5f);
	vertices->GetVertex(1)._position = Vector3(0.5f,-0.5f,-0.5f);
	vertices->GetVertex(2)._position = Vector3(0.5f,0.5f,-0.5f);
	vertices->GetVertex(3)._position = Vector3(-0.5f,0.5f,-0.5f);
	vertices->GetVertex(4)._position = Vector3(-0.5f,-0.5f,0.5f);
	vertices->GetVertex(5)._position = Vector3(0.5f,-0.5f,0.5f);
	vertices->GetVertex(6)._position = Vector3(0.5f,0.5f,0.5f);
	vertices->GetVertex(7)._position = Vector3(-0.5f,0.5f,0.5f);

	GLuint* indices = new GLuint[16];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	indices[4] = 4;
	indices[5] = 5;
	indices[6] = 6;
	indices[7] = 7;

	indices[8] = 0;
	indices[9] = 4;
	indices[10] = 1;
	indices[11] = 5;
	indices[12] = 2;
	indices[13] = 6;
	indices[14] = 3;
	indices[15] = 7;

	debugVertices = std::unique_ptr<VertexBuffer>(new VertexBuffer(_graphicsDevice, 8, vertices, vertices->GetVertexSize()));
	debugVertices->AddVertexAttributeInformation(0,3,GraphicsDataType::Float(), false, vertices->GetVertexSize(), 0);
	debugIndices = std::unique_ptr<IndexBuffer>(new IndexBuffer(_graphicsDevice, 16, indices));

	_resourceManager->StoreAndInitMaterial("debugMaterial", 
		new DebugMaterial(_resourceManager->GetShaderProgram("DEBUG", "../data/Debug.vert", "../data/Debug.frag")));
	debugMaterial = (DebugMaterial*)_resourceManager->GetMaterial("debugMaterial");

	debugObject = std::unique_ptr<GameObject>(new GameObject());

	boxColor = Color::Blue();
	quadtreeColor = Color::White();
}
void RenderEngine::DrawDebugObjects()
{
	if(_drawDebugObjects)
	{
		//DRAW DEBUG OBJECTS
		debugMaterial->Start(_graphicsDevice);
		debugMaterial->SetUniforms(_graphicsDevice, _mainCameraComponent);
		debugVertices->BindBuffer();
		debugIndices->BindBuffer();
		unsigned int numberOfAttributeInformations = debugVertices->GetNumberOfAttributeInfos();
		for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
		{
			const VertexAttributeInformation& thisInfo = debugVertices->GetVertexAttributeInformation(i);
			_graphicsDevice->EnableVertexAttribute(thisInfo.GetIndex());
			_graphicsDevice->SetVertexAttribute(thisInfo.GetIndex(), 
							  thisInfo.GetSize(), 
							  thisInfo.GetType(),
							  thisInfo.GetIsNormalized(), 
							  thisInfo.GetStride(), 
							  thisInfo.GetOffset());
		}

		for(unsigned int i = 0; i < _debugBoxes.size(); i++)
		{
			DrawBoundingBox(_debugBoxes[i]);
		}
		for(unsigned int i = 0; i < quadtreeBoxes.size(); i++)
		{
			DrawBoundingBox(quadtreeBoxes[i]);
		}
		for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
		{
			_graphicsDevice->DisableVertexAttribute(debugVertices->GetVertexAttributeInformation(i).GetIndex());
		}
		debugIndices->UnbindBuffer();
		debugVertices->UnbindBuffer();
		debugMaterial->End(_graphicsDevice);
		_debugBoxes.clear();
	}
}
void RenderEngine::DrawBoundingBox(const DebugBoundingBox& box)
{
	debugMaterial->SetColor(box._color);
	debugObject->GetTransform().SetScale(box._boundingBox._halfSize * 2);
	debugObject->GetTransform().SetPosition(box._boundingBox._center);
	DrawBoundingBox();
}
void RenderEngine::DrawBoundingBox(Renderer* object)
{
	debugMaterial->SetColor(Color::Gray());
	debugObject->GetTransform().SetScale(object->GetScaledBoundingBox()._halfSize * 2);
	debugObject->GetTransform().SetPosition(object->GetScaledBoundingBox()._center);

	DrawBoundingBox();
}
void RenderEngine::DrawBoundingBox()
{
	debugMaterial->SetObjectUniforms(_graphicsDevice, debugObject.get());

	//Draw the mesh
	_graphicsDevice->DrawElements(GraphicsPrimitiveType::LineLoop(), 4, GraphicsDataType::UnsignedInt(), 0);
	_graphicsDevice->DrawElements(GraphicsPrimitiveType::LineLoop(), 4, GraphicsDataType::UnsignedInt(), (void*)(4*sizeof(unsigned int)));
	_graphicsDevice->DrawElements(GraphicsPrimitiveType::Lines(), 8, GraphicsDataType::UnsignedInt(), (void*)(8*sizeof(unsigned int)));
}