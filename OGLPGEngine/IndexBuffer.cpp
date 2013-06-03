//IndexBuffer.cpp
#include "IndexBuffer.h"

//Indexbuffer
IndexBuffer::IndexBuffer(unsigned int elementSize, unsigned int numberOfElements, GLIndexDataType indexType, GLvoid* bufferData): 
	Buffer(BufferType::ElementArrayBuffer(), BufferUsage::StaticDraw(), elementSize, numberOfElements, bufferData), _indexType(indexType.GetIndexDataType()), _indices(0)
{
}
IndexBuffer::IndexBuffer(unsigned int numberOfElements, GLushort* indices): 
	Buffer(BufferType::ElementArrayBuffer(), BufferUsage::StaticDraw(), sizeof(GLushort), numberOfElements, (GLvoid*)indices), 
	_indexType(GLIndexDataType::UnsignedShort().GetIndexDataType()), _indices(indices)
{

}
IndexBuffer::~IndexBuffer()
{
	if(_indices != 0)
	{
		delete [] _indices;
	}
}
const GLenum IndexBuffer::GetIndexType() const
{
		return this->_indexType;
}