//VertexDeclarations.h
#ifndef VERTEXDECLARATIONS_H_INCLUDED
#define VERTEXDECLARATIONS_H_INCLUDED

#include "Vector2.h"
#include "Vector3.h"

struct VertexPos
{
public:
	VertexPos():_position(0.0f){}
	VertexPos(Vector3 position):_position(position){}
	Vector3 _position;
};
struct VertexPosTex
{
public:
	VertexPosTex():_position(0.0f), _texCoord(0.0f){}
	VertexPosTex(Vector3 position, Vector2 texCoord):_position(position), _texCoord(texCoord){}
	Vector3 _position;
	Vector2 _texCoord;
};
struct VertexPosNormTex
{
public:
	VertexPosNormTex():_position(0.0f),_normal(0.0f), _texCoord(0.0f){}
	VertexPosNormTex(Vector3 position, Vector3 normal, Vector2 texCoord):_position(position),_normal(normal), _texCoord(texCoord){}
	Vector3 _position;
	Vector3 _normal;
	Vector2 _texCoord;
};

class VertexContainer
{
public:
	VertexContainer(){}
	virtual ~VertexContainer(){}

	virtual size_t GetVertexSize() = 0;
	virtual void* GetData()= 0;
};
class VertexPosContainer : public VertexContainer
{
public:
	VertexPosContainer(int numberOfVertices): _numberOfVertices(numberOfVertices)
	{
		_vertices = new VertexPos[numberOfVertices];
	}
	virtual ~VertexPosContainer()
	{
		if(_vertices != NULL)
		{
			delete [] _vertices;
		}
	}
	virtual void* GetData()
	{
		return (void*)_vertices;
	}
	virtual size_t GetVertexSize()
	{
		return sizeof(VertexPos);
	}
	VertexPos& GetVertex(const int& i)
	{
		return this->_vertices[i];
	}
private:
	VertexPos* _vertices;
	int _numberOfVertices;
};
class VertexPosTexContainer : public VertexContainer
{
public:
	VertexPosTexContainer(int numberOfVertices): _numberOfVertices(numberOfVertices)
	{
		_vertices = new VertexPosTex[numberOfVertices];
	}
	virtual ~VertexPosTexContainer()
	{
		if(_vertices != NULL)
		{
			delete [] _vertices;
		}
	}
	virtual void* GetData()
	{
		return (void*)_vertices;
	}
	virtual size_t GetVertexSize()
	{
		return sizeof(VertexPosTex);
	}
	VertexPosTex& GetVertex(const int& i)
	{
		return this->_vertices[i];
	}
private:
	VertexPosTex* _vertices;
	int _numberOfVertices;
};
class VertexPosNormTexContainer : public VertexContainer
{
public:
	VertexPosNormTexContainer(int numberOfVertices): _numberOfVertices(numberOfVertices)
	{
		_vertices = new VertexPosNormTex[numberOfVertices];
	}
	virtual ~VertexPosNormTexContainer()
	{
		if(_vertices != NULL)
		{
			delete [] _vertices;
		}
	}
	virtual void* GetData()
	{
		return (void*)_vertices;
	}
	virtual size_t GetVertexSize()
	{
		return sizeof(VertexPosNormTex);
	}
	VertexPosNormTex& GetVertex(const int& i)
	{
		return this->_vertices[i];
	}
private:
	VertexPosNormTex* _vertices;
	int _numberOfVertices;
};

#endif //VERTEXDECLARATIONS_H_INCLUDED