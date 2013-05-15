//Material.h
#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <memory>

class GameObject;
class ShaderProgram;
class Camera;
class Material
{
public:
	Material(ShaderProgram* shaderProgram);
	virtual ~Material();

	virtual void Initialize() = 0;
	virtual void Start() = 0;
	virtual void SetUniforms(Camera* thisCamera) = 0;
	virtual void SetObjectUniforms(GameObject* object) = 0;
	virtual void End() = 0;

	const ShaderProgram* Material::GetShaderProgram();
private:
	ShaderProgram* _shaderProgram;
};
#endif //MATERIAL_H_INCLUDED