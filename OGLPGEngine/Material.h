//Material.h
#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <memory>

class GameObject;
class ShaderProgram;
class Camera;
class GraphicsDevice;
class Material
{
public:
	Material(ShaderProgram* shaderProgram);
	virtual ~Material();

	virtual void Initialize(GraphicsDevice* graphicsDevice) = 0;
	virtual void Start(GraphicsDevice* graphicsDevice) = 0;
	virtual void SetUniforms(GraphicsDevice* graphicsDevice, Camera* thisCamera) = 0;
	virtual void SetObjectUniforms(GraphicsDevice* graphicsDevice, GameObject* object) = 0;
	virtual void End(GraphicsDevice* graphicsDevice) = 0;

	const ShaderProgram* Material::GetShaderProgram();
private:
	ShaderProgram* _shaderProgram;
};
#endif //MATERIAL_H_INCLUDED