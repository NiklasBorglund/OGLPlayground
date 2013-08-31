//GraphicsDevice.cpp
#include "GraphicsDevice.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Color.h"

GraphicsDevice::GraphicsDevice(){}
GraphicsDevice::~GraphicsDevice(){}
const unsigned int GraphicsDevice::GetUniformLocation(const unsigned int shaderIndex, const char* uniformName)const
{
	return glGetUniformLocation(shaderIndex, uniformName);
}
const unsigned int GraphicsDevice::GetUniformLocation(const unsigned int shaderIndex, std::string uniformName)const
{
	return GetUniformLocation(shaderIndex,uniformName.c_str());
}
void GraphicsDevice::SetUniform(const int uniformLocation, const int count, const float* uniformValue)const
{
	glUniform1fv(uniformLocation, count,uniformValue); 
}
void GraphicsDevice::SetUniform(const int uniformLocation, const Vector2& uniformValue)const
{
	glUniform2fv(uniformLocation, 1, uniformValue.Pointer()); 
}
void GraphicsDevice::SetUniform(const int uniformLocation, const Vector3& uniformValue)const
{
	glUniform3fv(uniformLocation, 1, uniformValue.Pointer()); 
}
void GraphicsDevice::SetUniform(const int uniformLocation, const Vector4& uniformValue)const
{
	glUniform4fv(uniformLocation, 1, uniformValue.Pointer()); 
}
void GraphicsDevice::SetUniform(const int uniformLocation, const Color& uniformValue)const
{
	glUniform4fv(uniformLocation, 1, uniformValue.Pointer()); 
}
void GraphicsDevice::SetUniform(const int uniformLocation, bool transpose, const Matrix4x4& uniformValue)const
{
	glUniformMatrix4fv(uniformLocation,1, transpose, uniformValue.Pointer());
}
void GraphicsDevice::SetUniform(const int uniformLocation, const int& uniformValue)const
{
	glUniform1i(uniformLocation,uniformValue);
}
void GraphicsDevice::EnableVertexAttribute(const unsigned int attributeIndex)const
{
	glEnableVertexAttribArray(attributeIndex);
}
void GraphicsDevice::SetVertexAttribute(const unsigned int attributeIndex, const int size, GraphicsDataType type, bool normalized, int stride,const void* attributePointer)const
{
	glVertexAttribPointer(attributeIndex, size, type.GetIndexDataType(), normalized, stride, attributePointer);
}
void GraphicsDevice::DisableVertexAttribute(const unsigned int attributeIndex)const
{
	glDisableVertexAttribArray(attributeIndex);
}
void GraphicsDevice::GenerateVertexArrays(int count, unsigned int* arrays)const
{
	glGenVertexArrays(count, arrays);
}
void GraphicsDevice::DeleteVertexArrays(int count, unsigned int* arrays)const
{
	glDeleteVertexArrays(count,arrays);
}
void GraphicsDevice::BindVertexArray(const unsigned int vertexArrayIndex)const
{
	glBindVertexArray(vertexArrayIndex);
}
bool GraphicsDevice::IsVertexArray(const unsigned int vertexArrayIndex)const
{
	return glIsVertexArray(vertexArrayIndex) ? true : false;
}
void GraphicsDevice::UseShader(const unsigned int shaderIndex)const
{
	glUseProgram(shaderIndex);
}
void GraphicsDevice::SetFrontFace(bool counterClockWise)const
{
	GLenum face = counterClockWise ? GL_CCW : GL_CW;
	glFrontFace(face);
}
void GraphicsDevice::EnableGraphicsMode(GraphicsMode graphicsMode)const
{
	glEnable(graphicsMode.GetMode());
}
void GraphicsDevice::DisableGraphicsMode(GraphicsMode graphicsMode)const
{
	glDisable(graphicsMode.GetMode());
}
void GraphicsDevice::SetBlendFactor(SourceBlendFactor source, DestinationBlendFactor destination)const
{
	glBlendFunc(source.GetBlendFactor(), destination.GetBlendFactor());
}
void GraphicsDevice::GenerateTextures(int count, unsigned int* textures)const
{
	glGenTextures(count, textures);
}
void GraphicsDevice::DeleteTextures(int count, unsigned int* textures)const
{
	glDeleteTextures(count, textures);
}
void GraphicsDevice::SetActiveTexture(int activeTexture)const
{
	GLenum textureEnum = GL_TEXTURE0 + activeTexture;
	glActiveTexture(textureEnum);
}
void GraphicsDevice::BindTexture(TextureType type, const unsigned int textureIndex)const
{
	glBindTexture(type.GetType(), textureIndex);
}
void GraphicsDevice::SetTextureParameter(TextureType type, TextureParameterType parameterType, TextureParameterValue parameterValue)const
{
	glTexParameteri(type.GetType(), parameterType.GetType(), parameterValue.GetValue());
}
void GraphicsDevice::SetPixelStorageType(PixelStorageType mode, int value)const
{
	glPixelStorei(mode.GetType(), value);
}
bool GraphicsDevice::IsTexture(const unsigned int textureIndex)const
{
	return glIsTexture(textureIndex) ? true : false;
}
void GraphicsDevice::GenerateMipMap(TextureType type)const
{
	glGenerateMipmap(type.GetType());
}
void GraphicsDevice::GetTextureImage(TextureType type, int level, ColorFormat format, GraphicsDataType dataType, const void* dataPointer)const
{
	glGetTexImage(type.GetType(), level, format.GetFormat(), dataType.GetIndexDataType(), (GLvoid*)dataPointer);
}
void GraphicsDevice::SetTextureData(TextureType type, int level, ColorFormat internalFormat, int width, int height, int border, 
		ColorFormat format, GraphicsDataType dataType, const void* dataPointer)const
{
	glTexImage2D(type.GetType(), level, internalFormat.GetFormat(), width, height, border, format.GetFormat(), dataType.GetIndexDataType(), (GLvoid*) dataPointer);
}
void GraphicsDevice::GenerateBuffers(int count, unsigned int* buffers)const
{
	glGenBuffers(count, buffers);
}
void GraphicsDevice::DeleteBuffers(int count, unsigned int* buffers)const
{
	glDeleteBuffers(count, buffers);
}
void GraphicsDevice::BindBuffer(BufferType type, unsigned int bufferIndex)const
{
	glBindBuffer(type.GetBufferType(), bufferIndex);
}
void GraphicsDevice::SetBufferData(BufferType type, int sizeInBytes, const void* dataPointer, BufferUsage usage)const
{
	glBufferData(type.GetBufferType(), sizeInBytes, dataPointer, usage.GetBufferUsage());
}
bool GraphicsDevice::IsBuffer(const unsigned int bufferIndex)const
{
	return glIsBuffer(bufferIndex) ? true : false;
}
unsigned int GraphicsDevice::CreateShader(ShaderType type)const
{
	return glCreateShader(type.GetShaderType());
}
void GraphicsDevice::SetShaderDataSource(const unsigned int shaderIndex, int numberOfElements, const char* shaderData, int* length)const
{
	glShaderSource(shaderIndex, numberOfElements, &shaderData, length);
}
void GraphicsDevice::CompileShader(const unsigned int shaderIndex)const
{
	glCompileShader(shaderIndex);
}
void GraphicsDevice::DeleteShader(const unsigned int shaderIndex)const
{
	glDeleteShader(shaderIndex);
}
bool GraphicsDevice::CheckShaderCompileStatus(unsigned int shader, ShaderType shaderType)const
{
	bool success = true;
	GLint status;
	//Get the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		success = false;
		//Get the error message and print it to output
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		//for easier readability and debugging
		const char *strShaderType = NULL;
		switch(shaderType.GetShaderType())
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

	return success;
}
unsigned int GraphicsDevice::CreateProgram()const
{
	return glCreateProgram();
}
void GraphicsDevice::DeleteProgram(const unsigned int programIndex)const
{
	glDeleteProgram(programIndex);
}
bool GraphicsDevice::IsShaderProgram(const unsigned int programIndex)const
{
	return glIsProgram(programIndex) ? true : false;
}
void GraphicsDevice::AttachShaderToProgram(const unsigned int program, const unsigned int shader)const
{
	glAttachShader(program, shader);
}
void GraphicsDevice::DetachShaderFromProgram(const unsigned int program, const unsigned int shader)const
{
	glDetachShader(program, shader);
}
void GraphicsDevice::LinkProgram(const unsigned int programIndex)const
{
	glLinkProgram(programIndex);
}
bool GraphicsDevice::CheckProgramLinkerStatus(const unsigned int programIndex)const
{
	bool success = true;
	GLint status;
	glGetProgramiv (programIndex, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		success = false;
		GLint infoLogLength;
		glGetProgramiv(programIndex, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(programIndex, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
	return success;
}
void GraphicsDevice::SetClearColor(const Color& clearColor)const
{
	glClearColor(clearColor._r,clearColor._g,clearColor._b,clearColor._a);
}
void GraphicsDevice::ClearBuffers(const unsigned int bitMask)const
{
	glClear(bitMask);
}
void GraphicsDevice::ClearBuffers(bool color,bool depth,bool stencil)const
{
	//I have to change this method to something better
	unsigned int bitMask = 0;
	if(color)
	{
		bitMask = GL_COLOR_BUFFER_BIT;
	}
	if(depth)
	{
		if(bitMask = 0)
		{
			bitMask = GL_DEPTH_BUFFER_BIT;
		}
		else
		{
			//TEMP fix
			bitMask  = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		}
	}
	if(stencil)
	{
		if(bitMask = 0)
		{
			bitMask = GL_STENCIL_BUFFER_BIT;
		}
		else
		{
			bitMask |= GL_STENCIL_BUFFER_BIT;
		}
	}
	ClearBuffers(bitMask);
}
void GraphicsDevice::SetPolygonMode(PolygonMode mode)
{
	glPolygonMode(GL_FRONT_AND_BACK, mode.GetMode());
}
void GraphicsDevice::SetCullMode(CullMode mode)
{
	glCullFace(mode.GetMode());
}
void GraphicsDevice::DrawElements(GraphicsPrimitiveType primitiveType, int elements, GraphicsDataType indexType, const void* indicesLocation)const
{
	glDrawElements(primitiveType.GetType(),elements, indexType.GetIndexDataType(), (GLvoid*)indicesLocation);
}
void GraphicsDevice::DrawArrays(GraphicsPrimitiveType primitiveType, int firstIndex, int count)const
{
	glDrawArrays(primitiveType.GetType(), firstIndex, count);
}