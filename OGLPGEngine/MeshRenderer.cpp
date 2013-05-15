//MeshRenderer.cpp
#include "MeshRenderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

MeshRenderer::MeshRenderer(GameObject* owner, Mesh* mesh, Material* material):
	Component(owner, ComponentUpdateStep::RenderUpdate()),_mesh(mesh), _material(material){}
MeshRenderer::~MeshRenderer(){}

void MeshRenderer::PreDraw(Camera* currentCameraComponent)
{
	_material->Start();
	_material->SetUniforms(currentCameraComponent);
}

void MeshRenderer::Update()
{
	if(_mesh != NULL)
	{
		VertexBuffer* vertexBuffer = _mesh->GetVertexBuffer();
		IndexBuffer* indexBuffer = _mesh->GetIndexBuffer();
		
		//Set the per object uniforms of the game object(for example - the world matrix)
		_material->SetObjectUniforms(GetGameObject());

		glBindBuffer(vertexBuffer->GetBufferType(), vertexBuffer->GetBuffer());
		//Draw the mesh
		unsigned int numberOfAttributeInformations = vertexBuffer->GetNumberOfAttributeInfos();
		for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
		{
			const VertexAttributeInformation& thisInfo = vertexBuffer->GetVertexAttributeInformation(i);
			glEnableVertexAttribArray(thisInfo.GetIndex());
			glVertexAttribPointer(thisInfo.GetIndex(), 
								  thisInfo.GetSize(), 
								  thisInfo.GetType(),
								  thisInfo.GetIsNormalized(), 
								  thisInfo.GetStride(), 
								  thisInfo.GetOffset());
		}

		//Bind the index buffer
		glBindBuffer(indexBuffer->GetBufferType(), indexBuffer->GetBuffer());
		//DRAW
		glDrawElements(GL_TRIANGLES,indexBuffer->GetNumberOfElements(), indexBuffer->GetIndexType(), (GLvoid*)0);


		for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
		{
			glDisableVertexAttribArray(vertexBuffer->GetVertexAttributeInformation(i).GetIndex());
		}
	}
	//else, 
}

void MeshRenderer::PostDraw()
{
	_material->End();
}