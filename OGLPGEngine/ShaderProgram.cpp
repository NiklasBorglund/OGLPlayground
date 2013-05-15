//ShaderProgram.cpp
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(): _isCompiledAndLinked(false), _compilerError(false), _linkerError(false), _program(0)
{
}
ShaderProgram::ShaderProgram(const char* vertexShaderData, const char* fragmentShaderData): _isCompiledAndLinked(false), _compilerError(false), _linkerError(false), _program(0)
{
	AddShaderToProgram(ShaderType::VertexShader(), vertexShaderData);
	AddShaderToProgram(ShaderType::FragmentShader(), fragmentShaderData);
}
ShaderProgram::ShaderProgram(std::string vertexShaderData, std::string fragmentShaderData): _isCompiledAndLinked(false), _compilerError(false), _linkerError(false), _program(0)
{
	AddShaderToProgram(ShaderType::VertexShader(), vertexShaderData.c_str());
	AddShaderToProgram(ShaderType::FragmentShader(), fragmentShaderData.c_str());
}
ShaderProgram::~ShaderProgram()
{
	if(_shaderList.size() > 0)
	{
		for(unsigned int i = 0; i < _shaderList.size(); i++)
		{
			glDeleteShader(_shaderList[i]);
		}
		_shaderList.clear();
	}
	if(glIsProgram(_program))
	{
		glDeleteProgram(_program);
	}
}

bool ShaderProgram::AddShaderToProgram(ShaderType shaderType, const char* shaderData)
{
	GLuint compiledShader = CompileShader(shaderType.GetShaderType(), shaderData);

	//Check if the compilation was a success
	bool success = !CompilerError();

	if(!success)
	{
		//Delete the created shader
		glDeleteShader(compiledShader);
	}
	else
	{
		//Add it to the list that will be linked to the program
		_shaderList.push_back(compiledShader);
	}
	return success;
}
bool ShaderProgram::CreateAndLinkProgram()
{
	//create the program
	_program = glCreateProgram();

	//loop through all the compiled shaders and attach them to the program
	for(unsigned int i = 0; i < _shaderList.size(); i++)
	{
		glAttachShader(_program, _shaderList[i]);
	}

	//Link the program
	glLinkProgram(_program);

	//Check the linker status
	CheckProgramLinkerStatus();

	//Detach all the shaders from the program(we don't need them anymore)
	for(unsigned int i = 0; i < _shaderList.size(); i++)
	{
		glDetachShader(_program, _shaderList[i]);
	}

	//clear the shader list
	_shaderList.clear();

	bool success = !LinkerError();
	if(!success)
	{
		glDeleteProgram(_program);
	}
	else
	{
		this->_isCompiledAndLinked = true;
	}
	return success;
}
const GLuint ShaderProgram::GetProgram()const
{
	return this->_program;
}

bool ShaderProgram::IsCompiledAndLinked()const {return this->_isCompiledAndLinked;}
bool ShaderProgram::CompilerError()const {return this->_compilerError;}
bool ShaderProgram::LinkerError()const {return this->_linkerError;}

GLuint ShaderProgram::CompileShader(GLenum shaderType, const char* shaderData)
{
	//create the shader
	GLuint thisShader = glCreateShader(shaderType);
	
	//set the shader source
	glShaderSource(thisShader, 1, &shaderData, NULL);

	//Compile the shader
	glCompileShader(thisShader);

	//Check for errors
	CheckShaderCompileStatus(thisShader, shaderType);

	return thisShader;
}

void ShaderProgram::CheckShaderCompileStatus(GLuint shader, GLenum shaderType)
{
	GLint status;
	//Get the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		//Set the compiler error boolean
		this->_compilerError = true;

		//Get the error message and print it to output
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		//for easier readability and debugging
		const char *strShaderType = NULL;
		switch(shaderType)
		{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			case GL_TESS_CONTROL_SHADER: strShaderType = "tesselation control"; break;
			case GL_TESS_EVALUATION_SHADER: strShaderType = "tesselation evaluation"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}
}
void ShaderProgram::CheckProgramLinkerStatus()
{
	GLint status;
	glGetProgramiv (_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		this->_linkerError = true;

		GLint infoLogLength;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(_program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}