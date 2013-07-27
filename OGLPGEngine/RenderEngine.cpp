//RenderEngine.cpp
#include "RenderEngine.h"
#include "Renderer.h"
#include "Color.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Vector2.h"
#include "OpenGLVersion.h"
#include "GameTime.h"

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
void RenderEngine::Initialize(Camera* cameraComponent, ResourceManager* resourceManager)
{
	this->_mainCameraComponent = cameraComponent;
	this->_resourceManager = resourceManager;

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

	//Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );

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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
	}

	std::vector<Renderer*> selection;
	_quadtree.Select(selection,_mainCameraComponent->GetFrustum());
	for(unsigned int i = 0; i < selection.size(); i++)
	{
		Renderer* currentComponent = selection[i];
		currentComponent->PreDraw(_mainCameraComponent);
		currentComponent->Update(gameTime);//Draw
		currentComponent->PostDraw();
		triangles += currentComponent->GetNumberOfTriangles();
		drawCalls += currentComponent->GetNumberOfDrawCalls();

		if(_drawDebugObjects)
		{
			currentComponent->GetDebugBoundingBoxes(_debugBoxes);
		}
	}

	if(_drawWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
	}

	DrawDebugObjects();

	selection.clear();
	_drawCalls = drawCalls;
	_trianglesDrawn = triangles;
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

	debugVertices = std::unique_ptr<VertexBuffer>(new VertexBuffer(8, vertices, vertices->GetVertexSize()));
	debugVertices->AddVertexAttributeInformation(0,3,GL_FLOAT, GL_FALSE, vertices->GetVertexSize(), 0);
	debugIndices = std::unique_ptr<IndexBuffer>(new IndexBuffer(16, indices));

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
		debugMaterial->Start();
		debugMaterial->SetUniforms(_mainCameraComponent);
		debugVertices->BindBuffer();
		debugIndices->BindBuffer();
		unsigned int numberOfAttributeInformations = debugVertices->GetNumberOfAttributeInfos();
		for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
		{
			const VertexAttributeInformation& thisInfo = debugVertices->GetVertexAttributeInformation(i);
			glEnableVertexAttribArray(thisInfo.GetIndex());
			glVertexAttribPointer(thisInfo.GetIndex(), 
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
			glDisableVertexAttribArray(debugVertices->GetVertexAttributeInformation(i).GetIndex());
		}
		debugIndices->UnbindBuffer();
		debugVertices->UnbindBuffer();
		debugMaterial->End();
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
	debugMaterial->SetObjectUniforms(debugObject.get());

	//Draw the mesh
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (GLvoid*)(4*sizeof(GLuint)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, (GLvoid*)(8*sizeof(GLuint)));
}