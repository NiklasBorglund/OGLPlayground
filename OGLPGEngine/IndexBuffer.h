//IndexBuffer.h
#ifndef INDEXBUFFER_H_INCLUDED
#define INDEXBUFFER_H_INCLUDED

#include "Buffer.h"
#include "GraphicsDevice.h"


class IndexBuffer: public Buffer
{
public:
	/* using this will require you to delete the bufferdata yourself */
	IndexBuffer(GraphicsDevice* graphicsDevice,unsigned int elementSize, unsigned int numberOfElements, GraphicsDataType indexType, void* bufferData);

	IndexBuffer(GraphicsDevice* graphicsDevice,unsigned int numberOfElements, unsigned int* indices);
	virtual ~IndexBuffer();

	const GraphicsDataType GetIndexDataType()const;
private:
	GraphicsDataType _indexType;
	unsigned int* _indices;
};
#endif //INDEXBUFFER_H_INCLUDED