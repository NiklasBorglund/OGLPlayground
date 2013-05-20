//VertexDeclarations.h
#ifndef VERTEXDECLARATIONS_H_INCLUDED
#define VERTEXDECLARATIONS_H_INCLUDED

#include "Vector2.h"
#include "Vector3.h"

struct VertexPosTex
{
	VertexPosTex(Vector3 position, Vector2 texCoord):_position(position), _texCoord(texCoord){}
	Vector3 _position;
	Vector2 _texCoord;
};

#endif //VERTEXDECLARATIONS_H_INCLUDED