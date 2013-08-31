//VertexBuffer.cpp
#include "VertexBuffer.h"
#include "VertexDeclarations.h"

//VertexAttrributeInformation
VertexAttributeInformation::VertexAttributeInformation(unsigned int index, int size, GraphicsDataType type, bool normalized, unsigned int stride, unsigned int offset):
		index(index), size(size), type(type), normalized(normalized), stride(stride), offset(offset)
{}
VertexAttributeInformation::~VertexAttributeInformation(){}
const unsigned int VertexAttributeInformation::GetIndex()const{return this->index;}
const int VertexAttributeInformation::GetSize()const{return this->size;}
const GraphicsDataType VertexAttributeInformation::GetType()const{return this->type;}
const bool VertexAttributeInformation::GetIsNormalized()const{return this->normalized;}
const unsigned int VertexAttributeInformation::GetStride()const {return this->stride;}
void* VertexAttributeInformation::GetOffset() const{return (void*)this->offset;}

//VertexBuffer
VertexBuffer::VertexBuffer(GraphicsDevice* graphicsDevice, BufferType bufferType, BufferUsage bufferUsage,unsigned int elementSize, unsigned int numberOfElements, GLvoid* bufferData): 
		Buffer(graphicsDevice, bufferType, bufferUsage, elementSize, numberOfElements, bufferData)
{
	_vertexContainer = NULL;
}
VertexBuffer::VertexBuffer(GraphicsDevice* graphicsDevice,unsigned int numberOfElements, VertexContainer* vertexContainer, size_t vertexSize):
	Buffer(graphicsDevice, BufferType::ArrayBuffer(), BufferUsage::StaticDraw(), vertexSize, numberOfElements, vertexContainer->GetData()),
	_vertexContainer(vertexContainer)
{

}
VertexBuffer::~VertexBuffer()
{
	if(_vertexContainer != NULL)
	{
		delete _vertexContainer;
	}
}

void VertexBuffer::AddVertexAttributeInformation(unsigned int index, int size, GraphicsDataType type, bool normalized,unsigned int stride, unsigned int offset)
{
	this->_vertexAttributeInfo.push_back(VertexAttributeInformation(index,size,type,normalized, stride, offset));
}
const VertexAttributeInformation& VertexBuffer::GetVertexAttributeInformation(int index)const
{
	return this->_vertexAttributeInfo[index];
}
int VertexBuffer::GetNumberOfAttributeInfos()const
{
	return this->_vertexAttributeInfo.size();
}