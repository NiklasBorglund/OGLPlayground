//ShaderProgram.h
#ifndef SHADERPROGRAM_H_INCLUDED
#define SHADERPROGRAM_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>
#include <string>
#include <vector>

class ShaderType
{
public:
	static ShaderType VertexShader(){return ShaderType(GL_VERTEX_SHADER);};
	static ShaderType FragmentShader(){return ShaderType(GL_FRAGMENT_SHADER);};
	static ShaderType GeometryShader(){return ShaderType(GL_GEOMETRY_SHADER);};
	static ShaderType TesselationControlShader(){return ShaderType(GL_TESS_CONTROL_SHADER);};
	static ShaderType TesselationEvaluationShader(){return ShaderType(GL_TESS_EVALUATION_SHADER);};

	GLenum GetShaderType() const
	{
		return this->_shaderType;
	}
private:
	explicit ShaderType(GLenum shaderType):_shaderType(shaderType){};
	GLenum _shaderType;
};

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const char* vertexShaderData, const char* fragmentShaderData);
	ShaderProgram(std::string vertexShaderData, std::string fragmentShaderData);
	~ShaderProgram();
	bool AddShaderToProgram(ShaderType shaderType, const char* shaderData);
	bool CreateAndLinkProgram();

	const GLuint GetProgram()const;
	bool IsCompiledAndLinked()const;
	bool CompilerError()const;
	bool LinkerError()const;

private:
	bool _isCompiledAndLinked;
	bool _compilerError;
	bool _linkerError;
	GLuint _program;
	std::vector<GLuint> _shaderList;

	GLuint CompileShader(GLenum shaderType, const char* shaderData);
	void CheckShaderCompileStatus(GLuint shader, GLenum shaderType);
	void CheckProgramLinkerStatus();
};

#endif //SHADERPROGRAM_H_INCLUDED