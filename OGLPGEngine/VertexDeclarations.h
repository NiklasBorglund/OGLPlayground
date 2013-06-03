//VertexDeclarations.h
#ifndef VERTEXDECLARATIONS_H_INCLUDED
#define VERTEXDECLARATIONS_H_INCLUDED

#include "Vector2.h"
#include "Vector3.h"

struct VertexPosTex
{
	VertexPosTex():_position(0.0f), _texCoord(0.0f){}
	VertexPosTex(Vector3 position, Vector2 texCoord):_position(position), _texCoord(texCoord){}
	Vector3 _position;
	Vector2 _texCoord;
};
struct VertexPosNormTex
{
	VertexPosNormTex():_position(0.0f),_normal(0.0f), _texCoord(0.0f){}
	VertexPosNormTex(Vector3 position, Vector3 normal, Vector2 texCoord):_position(position),_normal(normal), _texCoord(texCoord){}
	Vector3 _position;
	Vector3 _normal;
	Vector2 _texCoord;
};

#endif //VERTEXDECLARATIONS_H_INCLUDED