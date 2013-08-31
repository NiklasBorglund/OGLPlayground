//MeshRenderer.cpp
#include "MeshRenderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "GraphicsDevice.h"

MeshRenderer::MeshRenderer(GameObject* owner, Mesh* mesh, Material* material, ComponentUpdateStep componentUpdateStep):
	Renderer(owner, componentUpdateStep),_mesh(mesh), _material(material)
{
	SetOriginalBoundingBox(mesh->GetBoundingBox());
}
MeshRenderer::~MeshRenderer(){}

void MeshRenderer::PreDraw(Camera* currentCameraComponent,GraphicsDevice* graphicsDevice)
{
	_material->Start(graphicsDevice);
	_material->SetUniforms(graphicsDevice, currentCameraComponent);
}

void MeshRenderer::Update(GameTime* gameTime,GraphicsDevice* graphicsDevice)
{
	int drawCalls = 0;
	int triangles = 0;
	if(_mesh != NULL)
	{
		VertexBuffer* vertexBuffer = _mesh->GetVertexBuffer();
		IndexBuffer* indexBuffer = _mesh->GetIndexBuffer();
		
		//Set the per object uniforms of the game object(for example - the world matrix)
		_material->SetObjectUniforms(graphicsDevice, GetGameObject());

		vertexBuffer->BindBuffer();
		//Draw the mesh
		unsigned int numberOfAttributeInformations = vertexBuffer->GetNumberOfAttributeInfos();
		for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
		{
			const VertexAttributeInformation& thisInfo = vertexBuffer->GetVertexAttributeInformation(i);
			graphicsDevice->EnableVertexAttribute(thisInfo.GetIndex());
			graphicsDevice->SetVertexAttribute(thisInfo.GetIndex(), 
							  thisInfo.GetSize(), 
							  thisInfo.GetType(),
							  thisInfo.GetIsNormalized(), 
							  thisInfo.GetStride(), 
							  thisInfo.GetOffset());
		}

		//Bind the index buffer
		indexBuffer->BindBuffer();
		//DRAW
		graphicsDevice->DrawElements(GraphicsPrimitiveType::Triangles(), indexBuffer->GetNumberOfElements(), indexBuffer->GetIndexDataType(), (void*)0);
		drawCalls++;
		triangles += indexBuffer->GetNumberOfElements() / 3;

		for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
		{
			graphicsDevice->DisableVertexAttribute(vertexBuffer->GetVertexAttributeInformation(i).GetIndex());
		}
		indexBuffer->UnbindBuffer();
		vertexBuffer->UnbindBuffer();
	}
	SetNumberOfDrawCalls(drawCalls);
	SetNumberOfTriangles(triangles);
}

void MeshRenderer::PostDraw(GraphicsDevice* graphicsDevice)
{
	_material->End(graphicsDevice);
}