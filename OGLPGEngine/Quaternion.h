//Quaternion.h
#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include <math.h>
#include "Vector3.h"

class Quaternion
{
public:
	union
	{
		struct 
		{
			float _x;
			float _y;
			float _z;
			float _w;
		};
		float q[4];
	};

	Quaternion(float x, float y, float z, float w): _x(x), _y(y), _z(z), _w(w){}
	explicit Quaternion(float value): _x(value), _y(value), _z(value), _w(value){}
	Quaternion(const Quaternion& other) : _x(other._x), _y(other._y), _z(other._z), _w(other._w) {}
	Quaternion(const Vector3& eulerAngles)
	{
		SetFromEuler(eulerAngles);
	}
	Quaternion() : _x(0), _y(0), _z(0), _w(0) {}
	Quaternion& operator= (const Quaternion& other)
	{
		_x = other._x;
		_y = other._y;
		_z = other._z;
		_w = other._w;
		return *this;	
	}
	~Quaternion(){}

	Quaternion operator+ (const Quaternion& other) const{return Quaternion(_x + other._x, _y + other._y, _z + other._z, _w + other._w);}
	Quaternion& operator+= (const Quaternion& other)
	{
		_x += other._x;
		_y += other._y;
		_z += other._z;
		_w += other._w;
		return *this;
	}
	Quaternion operator* (const float scalar) const
	{
		return Quaternion(scalar * _x, scalar * _y, scalar * _z,scalar * _w);
	}
	Quaternion operator*= (const float scalar)
	{
		_x *= scalar;
		_y *= scalar;
		_z *= scalar;
		_w *= scalar;
		return *this;
	}
	Quaternion operator* (const Quaternion& other) const
	{
		return Quaternion(_w * other._x + _x * other._w + _y * other._z - _z * other._y,
						  _w * other._y + _y * other._w + _z * other._x - _x * other._z,
						  _w * other._z + _z * other._w + _x * other._y - _y * other._x,
						  _w * other._w - _x * other._x - _y * other._y - _z * other._z);
	}
	Quaternion operator*= (const Quaternion& other)
	{
		_x = _w * other._x + _x * other._w + _y * other._z - _z * other._y;
		_y = _w * other._y + _y * other._w + _z * other._x - _x * other._z;
		_z = _w * other._z + _z * other._w + _x * other._y - _y * other._x;
		_w = _w * other._w - _x * other._x - _y * other._y - _z * other._z;
		return *this;
	}
	Quaternion operator/ (const float scalar) const
	{
		return Quaternion(scalar / _x, scalar / _y, scalar / _z, scalar / _w);
	}
	Quaternion operator/= (const float scalar)
	{
		_x /= scalar;
		_y /= scalar;
		_z /= scalar;
		_w /= scalar;
		return *this;
	}

	bool operator== (const Quaternion& other) const			{ return (_x == other._x) && (_y == other._y) && (_z == other._z) && (_w == other._w); }
	bool operator!= (const Quaternion& other) const			{ return (_x != other._x) || (_y != other._y) || (_z != other._z) || (_w != other._w); }

	float Length() const
	{
		return (sqrt(_x * _x + _y * _y + _z * _z + _w * _w));
	}
	float SquaredLength() const
	{
		return (_x * _x + _y * _y + _z * _z + _w * _w);
	}
	void Normalize()
	{
		*this /= SquaredLength();
	}
	Quaternion GetNormalized() const
	{
		Quaternion temp(*this);
		temp.Normalize();
		return temp;
	}
	float Dot(const Quaternion& other) const
	{
		return (other._x * _x + other._y * _y + other._z * _z + other._w * _w);
	}
	void Conjugate()
	{
		_x = -_x;
		_y = -_y;
		_z = -_z;
	}
	Quaternion& Invert()
	{
		Conjugate();
		*this /= SquaredLength();
		return *this;
	}
	/* Invert a unit quaternion, if unit = only need the conjugate which is much cheaper */
	Quaternion& InvertUnit()
	{
		Conjugate();
		return *this;
	}
	void GetInvert(Quaternion& quaternion) const
	{
		quaternion = *this;
		quaternion.Invert();
	}
	/* Invert a unit quaternion, if unit = only need the conjugate which is much cheaper */
	void GetInvertUnit(Quaternion& quaternion) const
	{
		quaternion = *this;
		quaternion.InvertUnit();
	}
	void SetFromEuler(const Vector3& eulerAngles)
	{
		Quaternion quatX(sin(eulerAngles._x / 2.0f), 0, 0, cos(eulerAngles._x / 2.0f));
		Quaternion quatY(0, sin(eulerAngles._y / 2.0f), 0, cos(eulerAngles._y / 2.0f));
		Quaternion quatZ(0, 0, sin(eulerAngles._z / 2.0f), cos(eulerAngles._z / 2.0f));
		*this = quatX * quatY * quatZ;
	}
	void SetFromEuler(float x, float y, float z)
	{
		SetFromEuler(Vector3(x,y,z));
	}
	Vector3 ToEuler() const
	{
		float squaredQW = _w * _w;    
		float squaredQX = _x * _x;    
		float squaredQY = _y * _y;    
		float squaredQZ = _z * _z;
		Vector3 vec;
		vec._x = atan2(2.0f * (_y * _z + _w * _x), (squaredQW - squaredQX - squaredQY + squaredQZ));    
		vec._y = asin(-2.0f * (_x * _z - _w * _y));
		vec._z = atan2(2.0f * (_x * _y + _w * _z), (squaredQW + squaredQX - squaredQY - squaredQZ));
		return vec;
	}
	static Quaternion CreateFromEuler(const Vector3& vec)
	{
		Quaternion quatX(sin(vec._x / 2.0f), 0, 0, cos(vec._x / 2.0f));
		Quaternion quatY(0, sin(vec._y / 2.0f), 0, cos(vec._y / 2.0f));
		Quaternion quatZ(0, 0, sin(vec._z / 2.0f), cos(vec._z / 2.0f));
		return quatX * quatY * quatZ;
	}
	static Quaternion CreateFromAxisAngle(const Vector3& vec, const float angleInRadians)
	{
		const float halfAngle = angleInRadians / 2.0f;
		float sinus = sin(halfAngle);
		return Quaternion(vec._x * sinus, vec._y * sinus, vec._z * sinus, cos(halfAngle));
	}
	static Quaternion Identity()
	{
		return Quaternion(0,0,0,1);
	}
};
#endif //QUATERNION_H_INCLUDED