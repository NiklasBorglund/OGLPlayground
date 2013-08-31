//Buffer.h
#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include "GraphicsDevice.h"

class Buffer
{
public:
	Buffer(GraphicsDevice* graphicsDevice, BufferType bufferType, BufferUsage bufferUsage, unsigned int elementSize, unsigned int numberOfElements, GLvoid* bufferData);
	virtual ~Buffer();

	const unsigned int GetBuffer() const;
	const BufferType GetBufferType()const;
	unsigned int GetStride() const;
	unsigned int GetElementSize()const;
	unsigned int GetNumberOfElements()const;
	void BindBuffer();
	void UnbindBuffer();
	//Make sure that the buffer settings are correct before using this
	//And that the buffer is bound to the context
	void SetBufferData(int numberOfElements, void* bufferData); 
	bool IsBuffer()const;

	void SetStride(unsigned int stride);
private:
	GraphicsDevice* _graphicsDevice;
	BufferType _bufferType;
	BufferUsage _bufferUsage;
	unsigned int _buffer;
	unsigned int _stride;
	unsigned int _elementSize;
	unsigned int _numberOfElements;
};
#endif //BUFFER_H_INCLUDED