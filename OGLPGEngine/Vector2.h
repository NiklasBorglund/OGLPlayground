//Vector2.cpp
#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED

#include <math.h>

class Vector2
{
public:
	union
	{
		struct  
		{
			float _x;
			float _y;
		};
		float values[2];
	};

	Vector2(float x, float y): _x(x), _y(y){}
	explicit Vector2(float value): _x(value), _y(value){}
	Vector2(): _x(0.0f), _y(0.0f){}

	float AbsSquare()const
	{
		return (_x * _x + _y * _y);
	}
	float Length()
	{
		return sqrt(_x * _x + _y * _y);
	}
	void Normalize()
	{
		float length = this->Length();
		_x = _x / length;
		_y = _y / length;
	}
	const float* Pointer() const
	{
		return &_x;
	}
	Vector2(const Vector2& other)								{ _x = other._x; _y = other._y; }
	Vector2& operator =   (const Vector2& other)				{ _x = other._x; _y = other._y; return *this; }

	Vector2  operator +   (const Vector2& other) const			{ return Vector2(_x + other._x, _y + other._y); }
	Vector2& operator +=  (const Vector2& other)					{ _x += other._x; _y += other._y; return *this; }

	Vector2  operator -   (const Vector2& other) const			{ return Vector2(_x - other._x, _y - other._y); }
	Vector2& operator -=  (const Vector2& other)					{ _x -= other._x; _y -= other._y; return *this; }
	Vector2  operator -() const									{ return Vector2(-_x, -_y); }

	Vector2  operator *	  (const float scalar) const			{ return Vector2(_x * scalar, _y * scalar); }
	Vector2	 operator *   (const Vector2& other) const			{ return Vector2(_x * other._x, _y * other._y); }
	Vector2& operator *=  (const float scalar)					{ _x *= scalar; _y *= scalar; return *this; }

	Vector2  operator /   (float amount) const					{ return Vector2(_x / amount, _x / amount); }
	Vector2& operator /=  (float amount)						{ _x /= amount; _y /= amount; return *this; }

	bool	 operator ==  (const Vector2& other) const			{ return _x == other._x && _y == other._y; }
	bool	 operator !=  (const Vector2& other) const			{ return _x != other._x || _y != other._y; }

	static Vector2 Clamp(const Vector2& value1, const Vector2& min, const Vector2& max)
	{
		Vector2 temp;

		temp._x = (value1._x > min._x) ? ((value1._x < max._x) ? value1._x : max._x) : min._x;
		temp._y = (value1._y > min._y) ? ((value1._y < max._y) ? value1._y : max._y) : min._y;

		return temp;
	}
	static Vector2 Max(const Vector2& value1, const Vector2& value2)
	{
		return Vector2((value1._x > value2._x) ? value1._x : value2._x,
					   (value1._y > value2._y) ? value1._y : value2._y);
	}
	static Vector2 Min(const Vector2& value1, const Vector2& value2)
	{
		return Vector2((value1._x < value2._x) ? value1._x : value2._x,
					   (value1._y < value2._y) ? value1._y : value2._y);
	}
	static Vector2 Multiply(const Vector2& value1, const float& scalar)
	{
		return Vector2(value1 * scalar);
	}
	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, const float& amount)
	{
		return Vector2((value1) + (value2 - value1) * amount);
	}
	static float Dot(const Vector2& value1, const Vector2& value2)
	{
		return (value1._x * value2._x + value1._y * value2._y);
	}
	static float Distance(const Vector2& value1, const Vector2& value2)
	{
		return (value1 - value2).Length();
	}
	static Vector2 Zero()										{ return Vector2(0.0f, 0.0f); }
	static Vector2 One()										{ return Vector2(1.0f, 1.0f); }
	static Vector2 UnitX()										{ return Vector2(1.0f, 0.0f); }
	static Vector2 UnitY()										{ return Vector2(0.0f, 1.0f); }
};

#endif //VECTOR2_H_INCLUDED