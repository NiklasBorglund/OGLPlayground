//IndexBuffer.cpp
#include "IndexBuffer.h"

//Indexbuffer
IndexBuffer::IndexBuffer(GraphicsDevice* graphicsDevice,unsigned int elementSize, unsigned int numberOfElements, GraphicsDataType indexType, void* bufferData): 
	Buffer(graphicsDevice, BufferType::ElementArrayBuffer(), BufferUsage::StaticDraw(), elementSize, numberOfElements, bufferData), _indexType(indexType), _indices(0)
{
}
IndexBuffer::IndexBuffer(GraphicsDevice* graphicsDevice,unsigned int numberOfElements, unsigned int* indices): 
	Buffer(graphicsDevice,BufferType::ElementArrayBuffer(), BufferUsage::StaticDraw(), sizeof(unsigned int), numberOfElements, (void*)indices), 
	_indexType(GraphicsDataType::UnsignedInt()), _indices(indices)
{

}
IndexBuffer::~IndexBuffer()
{
	if(_indices != 0)
	{
		delete [] _indices;
	}
}
const GraphicsDataType IndexBuffer::GetIndexDataType()const
{
	return this->_indexType;
}
