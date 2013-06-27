//Buffer.h
#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#define GLEW_STATIC
#include <GL\glew.h>

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
		return this->bufferType;
	}
private:
	explicit BufferType(GLenum bufferType):bufferType(bufferType){};
	GLenum bufferType;
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
		return this->bufferUsage;
	}
private:
	explicit BufferUsage(GLenum bufferUsage):bufferUsage(bufferUsage){};
	GLenum bufferUsage;
};

class Buffer
{
public:
	Buffer(BufferType bufferType, BufferUsage bufferUsage, unsigned int elementSize, unsigned int numberOfElements, GLvoid* bufferData);
	virtual ~Buffer();

	const GLuint GetBuffer() const;
	const GLenum GetBufferType()const;
	unsigned int GetStride() const;
	unsigned int GetElementSize()const;
	unsigned int GetNumberOfElements()const;
	void BindBuffer();
	void UnbindBuffer();
	//Make sure that the buffer settings are correct before using this
	//And that the buffer is bound to the context
	void SetBufferData(int numberOfElements, GLvoid* bufferData); 
	bool IsBuffer()const;

	void SetStride(unsigned int stride);
private:
	GLenum _bufferType;
	GLenum _bufferUsage;
	GLuint _buffer;
	unsigned int _stride;
	unsigned int _elementSize;
	unsigned int _numberOfElements;
};
#endif //BUFFER_H_INCLUDED