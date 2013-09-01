//GraphicsDevice.h
#ifndef GRAPHICSDEVICE_H_INCLUDED
#define GRAPHICSDEVICE_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

#include <string>

class GraphicsMode
{
public:
	static GraphicsMode CullFace(){return GraphicsMode(GL_CULL_FACE);};
	static GraphicsMode DepthTest(){return GraphicsMode(GL_DEPTH_TEST);};
	static GraphicsMode Blend(){return GraphicsMode(GL_BLEND);};

	int GetMode() const
	{
		return this->_mode;
	}
private:
	explicit GraphicsMode(int mode):_mode(mode){};
	int _mode;
};
class CullMode
{
public:
	static CullMode Front(){return CullMode(GL_FRONT);};
	static CullMode Back(){return CullMode(GL_BACK);};
	static CullMode FrontAndBack(){return CullMode(GL_FRONT_AND_BACK);};

	int GetMode() const
	{
		return this->_mode;
	}
private:
	explicit CullMode(int mode):_mode(mode){};
	int _mode;
};
class GraphicsDataType
{
public:
	static GraphicsDataType UnsignedByte(){return GraphicsDataType(GL_UNSIGNED_BYTE);};
	static GraphicsDataType UnsignedInt(){return GraphicsDataType(GL_UNSIGNED_INT);};
	static GraphicsDataType UnsignedShort(){return GraphicsDataType(GL_UNSIGNED_SHORT);};
	static GraphicsDataType UnsignedInt_8_8_8_8(){return GraphicsDataType(GL_UNSIGNED_INT_8_8_8_8);};
	static GraphicsDataType Float(){return GraphicsDataType(GL_FLOAT);};

	GLenum GetIndexDataType() const
	{
		return this->_indexDataType;
	}
private:
	explicit GraphicsDataType(GLenum indexDataType):_indexDataType(indexDataType){};
	GLenum _indexDataType;
};
class ColorFormat
{
public:
	static ColorFormat RGBA(){return ColorFormat(GL_RGBA);};
	static ColorFormat RGB(){return ColorFormat(GL_RGB);};
	static ColorFormat Red(){return ColorFormat(GL_RED);};

	GLenum GetFormat() const
	{
		return this->_format;
	}
private:
	explicit ColorFormat(GLenum format):_format(format){};
	GLenum _format;
};

class GraphicsPrimitiveType
{
public:
	static GraphicsPrimitiveType Points(){return GraphicsPrimitiveType(GL_POINTS);};
	static GraphicsPrimitiveType LineStrip(){return GraphicsPrimitiveType(GL_LINE_STRIP);};
	static GraphicsPrimitiveType LineStripAdjacency(){return GraphicsPrimitiveType(GL_LINE_STRIP_ADJACENCY);};
	static GraphicsPrimitiveType LineLoop(){return GraphicsPrimitiveType(GL_LINE_LOOP);};
	static GraphicsPrimitiveType Lines(){return GraphicsPrimitiveType(GL_LINES);};
	static GraphicsPrimitiveType LinesAdjacency(){return GraphicsPrimitiveType(GL_LINES_ADJACENCY);};
	static GraphicsPrimitiveType TriangleStrip(){return GraphicsPrimitiveType(GL_TRIANGLE_STRIP);};
	static GraphicsPrimitiveType TriangleStripAdjacency(){return GraphicsPrimitiveType(GL_TRIANGLE_STRIP_ADJACENCY);};
	static GraphicsPrimitiveType TriangleFan(){return GraphicsPrimitiveType(GL_TRIANGLE_FAN);};
	static GraphicsPrimitiveType Triangles(){return GraphicsPrimitiveType(GL_TRIANGLES);};
	static GraphicsPrimitiveType TrianglesAdjacency(){return GraphicsPrimitiveType(GL_TRIANGLES_ADJACENCY);};
	static GraphicsPrimitiveType Patches(){return GraphicsPrimitiveType(GL_PATCHES);};

	int GetType() const
	{
		return this->_primitiveType;
	}
private:
	explicit GraphicsPrimitiveType(int primitiveType):_primitiveType(primitiveType){};
	int _primitiveType;
};

class TextureType
{
public:
	static TextureType Texture1D(){return TextureType(GL_TEXTURE_1D);};
	static TextureType Texture2D(){return TextureType(GL_TEXTURE_2D);};
	static TextureType Texture3D(){return TextureType(GL_TEXTURE_3D);};
	static TextureType Texture1DArray(){return TextureType(GL_TEXTURE_1D_ARRAY);};
	static TextureType Texture2DArray(){return TextureType(GL_TEXTURE_2D_ARRAY);};
	static TextureType TextureRectangle(){return TextureType(GL_TEXTURE_RECTANGLE);};
	static TextureType TextureCubeMap(){return TextureType(GL_TEXTURE_CUBE_MAP);};
	static TextureType TextureCubeMapArray(){return TextureType(GL_TEXTURE_CUBE_MAP_ARRAY);};
	static TextureType TextureBuffer(){return TextureType(GL_TEXTURE_BUFFER);};
	static TextureType Texture2DMultisample(){return TextureType(GL_TEXTURE_2D_MULTISAMPLE);};
	static TextureType Texture2DMultisampleArray(){return TextureType(GL_TEXTURE_2D_MULTISAMPLE_ARRAY);};

	int GetType() const
	{
		return this->_textureType;
	}
private:
	explicit TextureType(int textureType):_textureType(textureType){};
	int _textureType;
};

class TextureParameterType
{
public:
	static TextureParameterType DepthStencilTextureMode(){return TextureParameterType(GL_DEPTH_STENCIL_TEXTURE_MODE);};
	static TextureParameterType TextureBaseLevel(){return TextureParameterType(GL_TEXTURE_BASE_LEVEL);};
	static TextureParameterType TextureBorderColor(){return TextureParameterType(GL_TEXTURE_BORDER_COLOR);};
	static TextureParameterType TextureCompareFunction(){return TextureParameterType(GL_TEXTURE_COMPARE_FUNC);};
	static TextureParameterType TextureCompareMode(){return TextureParameterType(GL_TEXTURE_COMPARE_MODE);};
	static TextureParameterType TextureLODBias(){return TextureParameterType(GL_TEXTURE_LOD_BIAS);};
	static TextureParameterType TextureMinFilter(){return TextureParameterType(GL_TEXTURE_MIN_FILTER);};
	static TextureParameterType TextureMagFilter(){return TextureParameterType(GL_TEXTURE_MAG_FILTER);};
	static TextureParameterType TextureMinLOD(){return TextureParameterType(GL_TEXTURE_MIN_LOD);};
	static TextureParameterType TextureMaxLOD(){return TextureParameterType(GL_TEXTURE_MAX_LOD);};
	static TextureParameterType TextureMaxLevel(){return TextureParameterType(GL_TEXTURE_MAX_LEVEL);};
	static TextureParameterType TextureSwizzleR(){return TextureParameterType(GL_TEXTURE_SWIZZLE_R);};
	static TextureParameterType TextureSwizzleG(){return TextureParameterType(GL_TEXTURE_SWIZZLE_G);};
	static TextureParameterType TextureSwizzleB(){return TextureParameterType(GL_TEXTURE_SWIZZLE_B);};
	static TextureParameterType TextureSwizzleA(){return TextureParameterType(GL_TEXTURE_SWIZZLE_A);};
	static TextureParameterType TextureSwizzleRGBA(){return TextureParameterType(GL_TEXTURE_SWIZZLE_RGBA);};
	static TextureParameterType TextureWrapS(){return TextureParameterType(GL_TEXTURE_WRAP_S);};
	static TextureParameterType TextureWrapT(){return TextureParameterType(GL_TEXTURE_WRAP_T);};
	static TextureParameterType TextureWrapR(){return TextureParameterType(GL_TEXTURE_WRAP_R);};

	int GetType() const
	{
		return this->_textureParameterType;
	}
private:
	explicit TextureParameterType(int textureParameterType):_textureParameterType(textureParameterType){};
	int _textureParameterType;
};
class TextureParameterValue
{
public:
	static TextureParameterValue ClampToEdge(){return TextureParameterValue(GL_CLAMP_TO_EDGE);};
	static TextureParameterValue Linear(){return TextureParameterValue(GL_LINEAR);};

	int GetValue() const
	{
		return this->_textureParameterValue;
	}
private:
	explicit TextureParameterValue(int textureParameterValue):_textureParameterValue(textureParameterValue){};
	int _textureParameterValue;
};
class PixelStorageType
{
public:
	static PixelStorageType PackAligment(){return PixelStorageType(GL_PACK_ALIGNMENT);};
	static PixelStorageType UnpackAligment(){return PixelStorageType(GL_UNPACK_ALIGNMENT);};

	int GetType() const
	{
		return this->_pixelStorageType;
	}
private:
	explicit PixelStorageType(int pixelStorageType):_pixelStorageType(pixelStorageType){};
	int _pixelStorageType;
};

class BufferType
{
public:
	static BufferType ArrayBuffer(){return BufferType(GL_ARRAY_BUFFER);};
	static BufferType AtomicCounterBuffer(){return BufferType(GL_ATOMIC_COUNTER_BUFFER);};
	static BufferType CopyReadBuffer(){return BufferType(GL_COPY_READ_BUFFER);};
	static BufferType CopyWriteBuffer(){return BufferType(GL_COPY_WRITE_BUFFER);};
	static BufferType DrawIndirectBuffer(){return BufferType(GL_DRAW_INDIRECT_BUFFER);};
	static BufferType DispatchIndirectBuffer(){return BufferType(GL_DISPATCH_INDIRECT_BUFFER);};
	static BufferType ElementArrayBuffer(){return BufferType(GL_ELEMENT_ARRAY_BUFFER);};
	static BufferType PixelPackBuffer(){return BufferType(GL_PIXEL_PACK_BUFFER);};
	static BufferType PixelUnpackBuffer(){return BufferType(GL_PIXEL_UNPACK_BUFFER);};
	static BufferType ShaderStorageBuffer(){return BufferType(GL_SHADER_STORAGE_BUFFER);};
	static BufferType TextureBuffer(){return BufferType(GL_TEXTURE_BUFFER);};
	static BufferType TransformFeedbackBuffer(){return BufferType(GL_TRANSFORM_FEEDBACK_BUFFER);};
	static BufferType UniformBuffer(){return BufferType(GL_UNIFORM_BUFFER);};

	GLenum GetBufferType() const
	{
		return this->_bufferType;
	}
private:
	explicit BufferType(GLenum bufferType):_bufferType(bufferType){};
	GLenum _bufferType;
};

class BufferUsage
{
public:
	static BufferUsage StreamDraw(){return BufferUsage(GL_STREAM_DRAW);};
	static BufferUsage StreamRead(){return BufferUsage(GL_STREAM_READ);};
	static BufferUsage StreamCopy(){return BufferUsage(GL_STREAM_COPY);};
	static BufferUsage StaticDraw(){return BufferUsage(GL_STATIC_DRAW);};
	static BufferUsage StaticRead(){return BufferUsage(GL_STATIC_READ);};
	static BufferUsage StaticCopy(){return BufferUsage(GL_STATIC_COPY);};
	static BufferUsage DynamicDraw(){return BufferUsage(GL_DYNAMIC_DRAW);};
	static BufferUsage DynamicRead(){return BufferUsage(GL_DYNAMIC_READ);};
	static BufferUsage DynamicCopy(){return BufferUsage(GL_DYNAMIC_COPY);};

	GLenum GetBufferUsage() const
	{
		return this->_bufferUsage;
	}
private:
	explicit BufferUsage(GLenum bufferUsage):_bufferUsage(bufferUsage){};
	GLenum _bufferUsage;
};
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
class SourceBlendFactor
{
public:
	static SourceBlendFactor SourceAlpha(){return SourceBlendFactor(GL_SRC_ALPHA);};

	GLenum GetBlendFactor() const
	{
		return this->_blendFactor;
	}
private:
	explicit SourceBlendFactor(GLenum blendFactor):_blendFactor(blendFactor){};
	GLenum _blendFactor;
};
class DestinationBlendFactor
{
public:
	static DestinationBlendFactor OneMinusSourceAlpha(){return DestinationBlendFactor(GL_ONE_MINUS_SRC_ALPHA);};

	GLenum GetBlendFactor() const
	{
		return this->_blendFactor;
	}
private:
	explicit DestinationBlendFactor(GLenum blendFactor):_blendFactor(blendFactor){};
	GLenum _blendFactor;
};
class PolygonMode
{
public:
	static PolygonMode Point(){return PolygonMode(GL_POINT);};
	static PolygonMode Line(){return PolygonMode(GL_LINE);};
	static PolygonMode Fill(){return PolygonMode(GL_FILL);};

	GLenum GetMode() const
	{
		return this->_mode;
	}
private:
	explicit PolygonMode(GLenum mode):_mode(mode){};
	GLenum _mode;
};

class Vector2;
class Vector3;
class Vector4;
class Matrix4x4;
class Color;
class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	const unsigned int GetUniformLocation(const unsigned int shaderIndex, const char* uniformName)const;
	const unsigned int GetUniformLocation(const unsigned int shaderIndex, std::string uniformName)const;
    void SetUniform(const int uniformLocation, const int count, const float* uniformValue)const;
	void SetUniform(const int uniformLocation, const Vector2& uniformValue)const;
	void SetUniform(const int uniformLocation, const Vector3& uniformValue)const;
	void SetUniform(const int uniformLocation, const Vector4& uniformValue)const;
	void SetUniform(const int uniformLocation, const Color& uniformValue)const;
	void SetUniform(const int uniformLocation, bool transpose, const Matrix4x4& uniformValue)const;
	void SetUniform(const int uniformLocation, const int uniformValue)const;

	void EnableVertexAttribute(const unsigned int attributeIndex)const;
	void SetVertexAttribute(const unsigned int attributeIndex, const int size, GraphicsDataType type, bool normalized, int stride,const void* attributePointer)const;
	void DisableVertexAttribute(const unsigned int attributeIndex)const;

	void GenerateVertexArrays(int count, unsigned int* arrays)const;
	void DeleteVertexArrays(int count, unsigned int* arrays)const;
	void BindVertexArray(const unsigned int vertexArrayIndex)const;
	bool IsVertexArray(const unsigned int vertexArrayIndex)const;

	void UseShader(const unsigned int shaderIndex)const;

	//false = clockwise
	void SetFrontFace(bool counterClockWise)const;
	void EnableGraphicsMode(GraphicsMode graphicsMode)const;
	void DisableGraphicsMode(GraphicsMode graphicsMode)const;
	void SetBlendFactor(SourceBlendFactor source, DestinationBlendFactor destination)const;

	void GenerateTextures(int count, unsigned int* textures)const;
	void DeleteTextures(int count, unsigned int* textures)const;
	void SetActiveTexture(int activeTexture)const;
	void BindTexture(TextureType type, const unsigned int textureIndex)const;
	void SetTextureParameter(TextureType type, TextureParameterType parameterType, TextureParameterValue parameterValue)const;
	void SetPixelStorageType(PixelStorageType mode, int value)const;
	void GenerateMipMap(TextureType type)const;
	void GetTextureImage(TextureType type, int level, ColorFormat format, GraphicsDataType dataType, const void* dataPointer)const;
	void SetTextureData(TextureType type, int level, ColorFormat internalFormat, int width, int height, int border, 
		ColorFormat format, GraphicsDataType dataType, const void* dataPointer)const;
	bool IsTexture(const unsigned int textureIndex)const;

	void GenerateBuffers(int count, unsigned int* buffers)const;
	void DeleteBuffers(int count, unsigned int* buffers)const;
	void BindBuffer(BufferType type, unsigned int bufferIndex)const;
	void SetBufferData(BufferType type, int sizeInBytes, const void* dataPointer, BufferUsage usage)const;
	bool IsBuffer(const unsigned int bufferIndex)const;


	unsigned int CreateShader(ShaderType type)const;
	void SetShaderDataSource(const unsigned int shaderIndex, int numberOfElements, const char* shaderData, int* length)const;
	void CompileShader(const unsigned int shaderIndex)const;
	void DeleteShader(const unsigned int shaderIndex)const;
	bool CheckShaderCompileStatus(unsigned int shader, ShaderType shaderType)const;
	
	unsigned int CreateProgram()const;
	void DeleteProgram(const unsigned int programIndex)const;
	bool IsShaderProgram(const unsigned int programIndex)const;
	void AttachShaderToProgram(const unsigned int program, const unsigned int shader)const;
	void DetachShaderFromProgram(const unsigned int program, const unsigned int shader)const;
	void LinkProgram(const unsigned int programIndex)const;
	bool CheckProgramLinkerStatus(const unsigned int programIndex)const;

	void SetClearColor(const Color& clearColor)const;
	void ClearBuffers(const unsigned int bitMask)const;
	void ClearBuffers(bool color,bool depth,bool stencil)const;
	void SetPolygonMode(PolygonMode mode);
	void SetCullMode(CullMode mode);
	void DrawElements(GraphicsPrimitiveType primitiveType, int elements, GraphicsDataType indexType, const void* indicesLocation)const;
	void DrawArrays(GraphicsPrimitiveType primitiveType, int firstIndex, int count)const;
};
#endif //GRAPHICSDEVICE_H_INCLUDED