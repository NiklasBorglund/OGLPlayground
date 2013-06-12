//MeshRenderer.h
//Component
#ifndef MESHRENDERER_H_INCLUDED
#define MESHRENDERER_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>

#include <memory>
#include "Component.h"

class Mesh;
class GameObject;
class Material;
class Camera;
class MeshRenderer : public Component
{
public:
	MeshRenderer(GameObject* owner, Mesh* mesh, Material* _material);
	virtual ~MeshRenderer();

	void PreDraw(Camera* currentCameraComponent);
	virtual void Update(GameTime* gameTime); //<---Draw
	void PostDraw();

private:
	Mesh* _mesh;
	Material* _material;
};
#endif //MESHRENDERER_H_INCLUDED