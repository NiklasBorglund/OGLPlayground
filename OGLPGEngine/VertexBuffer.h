//VertexBuffer.h
#ifndef VERTEXBUFFER_H_INCLUDED
#define VERTEXBUFFER_H_INCLUDED

#include "Buffer.h"
#include <vector>

//A class to store the information used in each vertex attribute
class VertexAttributeInformation
{
public:
	VertexAttributeInformation(unsigned int index, int size, GraphicsDataType type, bool normalized, unsigned int stride, unsigned int offset);
	~VertexAttributeInformation();

	const unsigned int GetIndex()const;
	const int GetSize()const;
	const GraphicsDataType GetType()const;
	const bool GetIsNormalized()const;
	const unsigned int GetStride()const;
	void* GetOffset() const;

private:
	unsigned int index;
	int size;
	GraphicsDataType type;
	bool normalized;
	unsigned int stride;
	unsigned int offset;
};

class VertexContainer;
class VertexBuffer: public Buffer
{
public:
	/* using this will require you to delete the bufferdata yourself */
	VertexBuffer(GraphicsDevice* graphicsDevice,BufferType bufferType, BufferUsage bufferUsage,unsigned int elementSize, unsigned int numberOfElements, void* bufferData);

	VertexBuffer(GraphicsDevice* graphicsDevice,unsigned int numberOfElements, VertexContainer* vertexContainer, size_t vertexSize);
	virtual ~VertexBuffer();

	void AddVertexAttributeInformation(unsigned int index, int size, GraphicsDataType type, bool normalized,unsigned int stride, unsigned int offset);
	const VertexAttributeInformation& GetVertexAttributeInformation(int index)const;
	int GetNumberOfAttributeInfos()const;
private:
	std::vector<VertexAttributeInformation> _vertexAttributeInfo;
	VertexContainer* _vertexContainer;
};
#endif //VERTEXBUFFER_H_INCLUDED