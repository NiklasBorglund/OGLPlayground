//MeshRenderer.h
//Component
#ifndef MESHRENDERER_H_INCLUDED
#define MESHRENDERER_H_INCLUDED

#include "Renderer.h"

class Mesh;
class GameObject;
class Material;
class MeshRenderer : public Renderer
{
public:
	MeshRenderer(GameObject* owner, Mesh* mesh, Material* material, ComponentUpdateStep componentUpdateStep = ComponentUpdateStep::RenderUpdate());
	virtual ~MeshRenderer();

	virtual void PreDraw(Camera* currentCameraComponent, GraphicsDevice* graphicsDevice);
	virtual void Update(GameTime* gameTime, GraphicsDevice* graphicsDevice); //<---Draw
	virtual void PostDraw(GraphicsDevice* graphicsDevice);

private:
	Mesh* _mesh;
	Material* _material;
};
#endif //MESHRENDERER_H_INCLUDED