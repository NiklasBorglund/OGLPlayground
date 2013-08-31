//ShaderProgram.h
#ifndef SHADERPROGRAM_H_INCLUDED
#define SHADERPROGRAM_H_INCLUDED

#include <string>
#include <vector>

class ShaderType;
class GraphicsDevice;
class ShaderProgram
{
public:
	ShaderProgram(GraphicsDevice* graphicsDevice);
	ShaderProgram(GraphicsDevice* graphicsDevice, const char* vertexShaderData, const char* fragmentShaderData);
	ShaderProgram(GraphicsDevice* graphicsDevice, std::string vertexShaderData, std::string fragmentShaderData);
	~ShaderProgram();
	bool AddShaderToProgram(ShaderType shaderType, const char* shaderData);
	bool CreateAndLinkProgram();

	const unsigned int GetProgram()const;
	bool IsCompiledAndLinked()const;
	bool CompilerError()const;
	bool LinkerError()const;

private:
	GraphicsDevice* _graphicsDevice;
	bool _isCompiledAndLinked;
	bool _compilerError;
	bool _linkerError;
	unsigned int _program;
	std::vector<unsigned int> _shaderList;

	unsigned int CompileShader(ShaderType shaderType, const char* shaderData);
};

#endif //SHADERPROGRAM_H_INCLUDED