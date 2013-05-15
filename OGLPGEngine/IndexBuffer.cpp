//IndexBuffer.cpp
#include "IndexBuffer.h"

//Indexbuffer
IndexBuffer::IndexBuffer(unsigned int elementSize, unsigned int numberOfElements, GLIndexDataType indexType, GLvoid* bufferData): 
		Buffer(BufferType::ElementArrayBuffer(), BufferUsage::StaticDraw(), elementSize, numberOfElements, bufferData), _indexType(indexType.GetIndexDataType())
{}
IndexBuffer::~IndexBuffer()
{

}
const GLenum IndexBuffer::GetIndexType() const
{
		return this->_indexType;
}