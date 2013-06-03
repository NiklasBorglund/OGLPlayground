//VertexBuffer.cpp
#include "VertexBuffer.h"
#include "VertexDeclarations.h"

//VertexAttrributeInformation
VertexAttributeInformation::VertexAttributeInformation(GLuint index, GLint size, GLenum type, GLboolean normalized, unsigned int stride, unsigned int offset):
		index(index), size(size), type(type), normalized(normalized), stride(stride), offset(offset)
{}
VertexAttributeInformation::~VertexAttributeInformation(){}
const GLuint VertexAttributeInformation::GetIndex()const{return this->index;}
const GLint VertexAttributeInformation::GetSize()const{return this->size;}
const GLenum VertexAttributeInformation::GetType()const{return this->type;}
const GLboolean VertexAttributeInformation::GetIsNormalized()const{return this->normalized;}
const unsigned int VertexAttributeInformation::GetStride()const {return this->stride;}
GLvoid* VertexAttributeInformation::GetOffset() const{return (GLvoid*)this->offset;}

//VertexBuffer
VertexBuffer::VertexBuffer(BufferType bufferType, BufferUsage bufferUsage,unsigned int elementSize, unsigned int numberOfElements, GLvoid* bufferData): 
		Buffer(bufferType, bufferUsage, elementSize, numberOfElements, bufferData)
{
	_vertices = NULL;
}
VertexBuffer::VertexBuffer(unsigned int numberOfElements, VertexPosNormTex* vertices):
	Buffer(BufferType::ArrayBuffer(), BufferUsage::StaticDraw(), sizeof(VertexPosNormTex), numberOfElements, (GLvoid*)vertices),
	_vertices(vertices)
{

}
VertexBuffer::~VertexBuffer()
{
	if(_vertices != NULL)
	{
		delete [] _vertices;
	}
}

void VertexBuffer::AddVertexAttributeInformation(GLuint index, GLint size, GLenum type, GLboolean normalized,unsigned int stride, unsigned int offset)
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