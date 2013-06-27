//Buffer.cpp
#include "Buffer.h"
Buffer::Buffer(BufferType bufferType, BufferUsage bufferUsage, 
			   unsigned int elementSize, unsigned int numberOfElements, 
			   GLvoid* bufferData): 
			   _bufferType(bufferType.GetBufferType()), _bufferUsage(bufferUsage.GetBufferUsage()),
			   _buffer(0), _stride(0), 
			   _elementSize(elementSize), _numberOfElements(numberOfElements)
{
	//Generate the buffer
	glGenBuffers(1, &_buffer);
    
	//Bind the buffer to the context
	BindBuffer();

	//Set the buffer data
	glBufferData(_bufferType, (_elementSize * _numberOfElements), bufferData, _bufferUsage);

	//Unbind the buffer
	UnbindBuffer();
}
Buffer::~Buffer()
{
	if(IsBuffer())
	{
		glDeleteBuffers(1, &_buffer);
	}
}

const GLuint Buffer::GetBuffer()const
{
	return this->_buffer;
}
const GLenum Buffer::GetBufferType()const
{
	return this->_bufferType;
}
unsigned int Buffer::GetStride() const
{
	return this->_stride;
}
unsigned int Buffer::GetElementSize()const
{
	return this->_elementSize;
}
unsigned int Buffer::GetNumberOfElements()const
{
	return this->_numberOfElements;
}
void Buffer::BindBuffer()
{
	glBindBuffer(_bufferType, _buffer);
}
void Buffer::UnbindBuffer()
{
	glBindBuffer(_bufferType, 0);
}
//Make sure that the buffer settings are correct before using this
//And that the buffer is bound to the context
void Buffer::SetBufferData(int numberOfElements, GLvoid* bufferData)
{
	_numberOfElements = numberOfElements;
	glBufferData(_bufferType, (_elementSize * _numberOfElements), bufferData, _bufferUsage);
}
bool Buffer::IsBuffer()const
{
	return glIsBuffer(_buffer)? true : false;
}
void Buffer::SetStride(unsigned int stride)
{
	this->_stride = stride;
}