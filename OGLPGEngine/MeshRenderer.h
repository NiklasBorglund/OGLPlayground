//MeshRenderer.h
//Component
#ifndef MESHRENDERER_H_INCLUDED
#define MESHRENDERER_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>

#include "Renderer.h"

class Mesh;
class GameObject;
class Material;
class MeshRenderer : public Renderer
{
public:
	MeshRenderer(GameObject* owner, Mesh* mesh, Material* material, ComponentUpdateStep componentUpdateStep = ComponentUpdateStep::RenderUpdate());
	virtual ~MeshRenderer();

	virtual void PreDraw(Camera* currentCameraComponent);
	virtual void Update(GameTime* gameTime); //<---Draw
	virtual void PostDraw();

private:
	Mesh* _mesh;
	Material* _material;
};
#endif //MESHRENDERER_H_INCLUDED