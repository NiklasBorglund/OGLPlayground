//ShaderProgram.cpp
#include "ShaderProgram.h"
#include "GraphicsDevice.h"

ShaderProgram::ShaderProgram(GraphicsDevice* graphicsDevice): _graphicsDevice(graphicsDevice), _isCompiledAndLinked(false), _compilerError(false), _linkerError(false), _program(0)
{
}
ShaderProgram::ShaderProgram(GraphicsDevice* graphicsDevice,const char* vertexShaderData, const char* fragmentShaderData): _graphicsDevice(graphicsDevice),_isCompiledAndLinked(false), _compilerError(false), _linkerError(false), _program(0)
{
	AddShaderToProgram(ShaderType::VertexShader(), vertexShaderData);
	AddShaderToProgram(ShaderType::FragmentShader(), fragmentShaderData);
}
ShaderProgram::ShaderProgram(GraphicsDevice* graphicsDevice,std::string vertexShaderData, std::string fragmentShaderData):_graphicsDevice(graphicsDevice), _isCompiledAndLinked(false), _compilerError(false), _linkerError(false), _program(0)
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
			_graphicsDevice->DeleteShader(_shaderList[i]);
		}
		_shaderList.clear();
	}
	if(_graphicsDevice->IsShaderProgram(_program))
	{
		_graphicsDevice->DeleteProgram(_program);
	}
}

bool ShaderProgram::AddShaderToProgram(ShaderType shaderType, const char* shaderData)
{
	unsigned int compiledShader = CompileShader(shaderType, shaderData);

	//Check if the compilation was a success
	bool success = !CompilerError();

	if(!success)
	{
		//Delete the created shader
		_graphicsDevice->DeleteShader(compiledShader);
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
	_program = _graphicsDevice->CreateProgram();

	//loop through all the compiled shaders and attach them to the program
	for(unsigned int i = 0; i < _shaderList.size(); i++)
	{
		_graphicsDevice->AttachShaderToProgram(_program, _shaderList[i]);
	}

	//Link the program
	_graphicsDevice->LinkProgram(_program);

	//Check the linker status
	if(!_graphicsDevice->CheckProgramLinkerStatus(_program))
	{
		this->_linkerError = true;
	}

	//Detach all the shaders from the program(we don't need them anymore)
	for(unsigned int i = 0; i < _shaderList.size(); i++)
	{
		_graphicsDevice->DetachShaderFromProgram(_program, _shaderList[i]);
	}

	//clear the shader list
	_shaderList.clear();

	bool success = !LinkerError();
	if(!success)
	{
		_graphicsDevice->DeleteProgram(_program);
	}
	else
	{
		this->_isCompiledAndLinked = true;
	}
	return success;
}
const unsigned int ShaderProgram::GetProgram()const
{
	return this->_program;
}

bool ShaderProgram::IsCompiledAndLinked()const {return this->_isCompiledAndLinked;}
bool ShaderProgram::CompilerError()const {return this->_compilerError;}
bool ShaderProgram::LinkerError()const {return this->_linkerError;}

unsigned int ShaderProgram::CompileShader(ShaderType shaderType, const char* shaderData)
{
	//create the shader
	unsigned int thisShader = _graphicsDevice->CreateShader(shaderType);
	
	//set the shader source
	_graphicsDevice->SetShaderDataSource(thisShader, 1, shaderData, NULL);

	//Compile the shader
	_graphicsDevice->CompileShader(thisShader);

	//Check for errors
	if(!_graphicsDevice->CheckShaderCompileStatus(thisShader, shaderType))
	{
		this->_compilerError = true;
	}

	return thisShader;
}

