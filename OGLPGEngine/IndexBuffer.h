//IndexBuffer.h
#ifndef INDEXBUFFER_H_INCLUDED
#define INDEXBUFFER_H_INCLUDED

#include "Buffer.h"

class GLIndexDataType
{
public:
	static GLIndexDataType UnsignedByte(){return GLIndexDataType(GL_UNSIGNED_BYTE);};
	static GLIndexDataType UnsignedInt(){return GLIndexDataType(GL_UNSIGNED_INT);};
	static GLIndexDataType UnsignedShort(){return GLIndexDataType(GL_UNSIGNED_SHORT);};

	GLenum GetIndexDataType() const
	{
		return this->_indexDataType;
	}
private:
	explicit GLIndexDataType(GLenum indexDataType):_indexDataType(indexDataType){};
	GLenum _indexDataType;
};


class IndexBuffer: public Buffer
{
public:
	/* using this will require you to delete the bufferdata yourself */
	IndexBuffer(unsigned int elementSize, unsigned int numberOfElements, GLIndexDataType indexType, GLvoid* bufferData);

	IndexBuffer(unsigned int numberOfElements, GLuint* indices);
	virtual ~IndexBuffer();

	const GLenum GetIndexType() const;
private:
	GLenum _indexType;
	GLuint* _indices;
};
#endif //INDEXBUFFER_H_INCLUDED