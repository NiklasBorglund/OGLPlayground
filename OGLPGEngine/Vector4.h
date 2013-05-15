//Vector4.cpp
#ifndef VECTOR4_H_INCLUDED
#define VECTOR4_H_INCLUDED

#include <math.h>

class Vector4
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
		float values[4];
	};
	Vector4(float x, float y, float z, float w):_x(x), _y(y), _z(z), _w(w){}
	explicit Vector4(float value): _x(value), _y(value), _z(value), _w(value) {}
	Vector4(): _x(0), _y(0), _z(0), _w(0){}

	float Length()
	{
		return sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
	}
	float SquaredLength()
	{
		return (_x * _x + _y * _y + _z * _z + _w * _w);
	}
	void Normalize()
	{
		float length = this->Length();
		_x = _x / length;
		_y = _y / length;
		_z = _z / length;
		_w = _w / length;
	}
	static Vector4 Clamp(const Vector4& value1, const Vector4& min, const Vector4& max)
	{
		Vector4 temp;

		temp._x = (value1._x > min._x) ? ((value1._x < max._x) ? value1._x : max._x) : min._x;
		temp._y = (value1._y > min._y) ? ((value1._y < max._y) ? value1._y : max._y) : min._y;
		temp._z = (value1._z > min._z) ? ((value1._z < max._z) ? value1._z : max._z) : min._z;
		temp._w = (value1._w > min._w) ? ((value1._w < max._w) ? value1._w : max._w) : min._w;

		return temp;
	}
	static Vector4 Max(const Vector4& value1, const Vector4& value2)
	{
		return Vector4((value1._x > value2._x) ? value1._x : value2._x,
						(value1._y > value2._y) ? value1._y : value2._y,
						(value1._z > value2._z) ? value1._z : value2._z,
						(value1._w > value2._w) ? value1._w : value2._w);
	}
	static Vector4 Min(const Vector4& value1, const Vector4& value2)
	{
		return Vector4((value1._x < value2._x) ? value1._x : value2._x,
						(value1._y < value2._y) ? value1._y : value2._y,
						(value1._z < value2._z) ? value1._z : value2._z,
						(value1._w < value2._w) ? value1._w : value2._w);
	}
	static Vector4 Multiply(const Vector4& value1, const float& scalar)
	{
		return Vector4(value1 * scalar);
	}
	static Vector4 Lerp(const Vector4& value1, const Vector4& value2, const float& amount)
	{
		return Vector4(value1 + (value2 - value1) * amount);
	}
	static float Dot(const Vector4& vector1, const Vector4& vector2)
	{
		return (vector1._x * vector2._x + vector1._y * vector2._y + vector1._z * vector2._z + vector1._w * vector2._w);
	}
	static float Distance(const Vector4& vector1, const Vector4& vector2)
	{
		return Vector4(fabs(vector1._x - vector2._x),
			fabs(vector1._y - vector2._y),
			fabs(vector1._z - vector2._z),
			fabs(vector1._w - vector2._w)).Length();
	}
	const float* Pointer() const
    {
        return &_x;
    }

	static Vector4 Zero()										{ return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
	static Vector4 One()										{ return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
	static Vector4 UnitX()										{ return Vector4(1.0f, 0.0f, 0.0f, 0.0f); }
	static Vector4 UnitY()										{ return Vector4(0.0f, 1.0f, 0.0f, 0.0f); }
	static Vector4 UnitZ()										{ return Vector4(0.0f, 0.0f, 1.0f, 0.0f); }
	static Vector4 UnitW()										{ return Vector4(0.0f, 0.0f, 0.0f, 1.0f); }

	Vector4(const Vector4& other)								{ _x = other._x; _y = other._y; _z = other._z; _w = other._w; }
	Vector4& operator =   (const Vector4& other)				{ _x = other._x; _y = other._y; _z = other._z; _w = other._w; return *this; }

	Vector4  operator +   (const Vector4& other) const			{ return Vector4(_x + other._x, _y + other._y, _z + other._z, _w + other._w); }
	Vector4& operator +=  (const Vector4& other)					{ _x += other._x; _y += other._y; _z += other._z; _w += other._w; return *this; }

	Vector4  operator -   (const Vector4& other) const			{ return Vector4(_x - other._x, _y - other._y, _z - other._z, _w - other._w); }
	Vector4& operator -=  (const Vector4& other)					{ _x -= other._x; _y -= other._y; _z -= other._z; _w -= other._w; return *this; }
	Vector4  operator -() const									{ return Vector4(-_x, -_y, -_z, -_w); }

	Vector4  operator *	  (const float scalar) const			{ return Vector4(_x * scalar, _y * scalar, _z * scalar, _w * scalar); }
	Vector4	 operator *   (const Vector4& other) const			{ return Vector4(_x * other._x, _y * other._y, _z * other._z, _w * other._w); }
	Vector4& operator *=  (const float scalar)					{ _x *= scalar; _y *= scalar; _z *= scalar; _w *= scalar; return *this; }

	Vector4  operator /   (float amount) const					{ return Vector4(_x / amount, _y / amount, _z / amount, _w / amount); }
	Vector4& operator /=  (float amount)						{ _x /= amount; _y /= amount; _z /= amount; _w /= amount; return *this; }

	bool	 operator ==  (const Vector4& other) const			{ return _x == other._x && _y == other._y && _z == other._z && _w == other._w; }
	bool	 operator !=  (const Vector4& other) const			{ return _x != other._x || _y != other._y || _z != other._z || _z != other._z; }
};
#endif //VECTOR4_H_INCLUDED