//Buffer.cpp
#include "Buffer.h"
Buffer::Buffer(GraphicsDevice* graphicsDevice,BufferType bufferType, BufferUsage bufferUsage, 
			   unsigned int elementSize, unsigned int numberOfElements, 
			   GLvoid* bufferData): _graphicsDevice(graphicsDevice),
			   _bufferType(bufferType), _bufferUsage(bufferUsage),
			   _buffer(0), _stride(0), 
			   _elementSize(elementSize), _numberOfElements(numberOfElements)
{
	//Generate the buffer
	_graphicsDevice->GenerateBuffers(1, &_buffer);
    
	//Bind the buffer to the context
	BindBuffer();

	//Set the buffer data
	_graphicsDevice->SetBufferData(_bufferType, (_elementSize * _numberOfElements), bufferData, _bufferUsage);

	//Unbind the buffer
	UnbindBuffer();
}
Buffer::~Buffer()
{
	if(IsBuffer())
	{
		_graphicsDevice->DeleteBuffers(1, &_buffer);
	}
}

const unsigned int Buffer::GetBuffer() const
{
	return this->_buffer;
}
const BufferType Buffer::GetBufferType()const
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
	_graphicsDevice->BindBuffer(_bufferType, _buffer);
}
void Buffer::UnbindBuffer()
{
	_graphicsDevice->BindBuffer(_bufferType, 0);
}
//Make sure that the buffer settings are correct before using this
//And that the buffer is bound to the context
void Buffer::SetBufferData(int numberOfElements, void* bufferData)
{
	_numberOfElements = numberOfElements;
	_graphicsDevice->SetBufferData(_bufferType, (_elementSize * _numberOfElements), bufferData, _bufferUsage);
}
bool Buffer::IsBuffer()const
{
	return _graphicsDevice->IsBuffer(_buffer);
}
void Buffer::SetStride(unsigned int stride)
{
	this->_stride = stride;
}