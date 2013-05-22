//Vector3.cpp
#ifndef VECTOR3_H_INCLUDED
#define VECTOR3_H_INCLUDED

#include <math.h>

class Vector3  
{
public:
	union
	{
		struct  
		{
			float _x;
			float _y;
			float _z;
		};
		float values[3];
	};
	Vector3(float x, float y, float z):_x(x), _y(y), _z(z){}
	explicit Vector3(float value): _x(value), _y(value), _z(value) {}
	Vector3(): _x(0), _y(0), _z(0){}

	float Length()
	{
		return sqrt(_x * _x + _y * _y + _z * _z);
	}
	float SquaredLength()
	{
		return (_x * _x + _y * _y + _z * _z);
	}
	void Normalize()
	{
		float length = Length();
		if (length <= 0.0f)
		{
			_x = 1.0f;
			_y = 0.0f;
			_z = 0.0f;
		}
		else
		{
			_x /= length;
			_y /= length;
			_z /= length;
		}
	}
	const float* Pointer() const
	{
		return &_x;
	}
	static Vector3 Clamp(const Vector3& value1, const Vector3& min, const Vector3& max)
	{
		Vector3 temp;

		temp._x = (value1._x > min._x) ? ((value1._x < max._x) ? value1._x : max._x) : min._x;
		temp._y = (value1._y > min._y) ? ((value1._y < max._y) ? value1._y : max._y) : min._y;
		temp._z = (value1._z > min._z) ? ((value1._z < max._z) ? value1._z : max._z) : min._z;

		return temp;
	}

	static Vector3 Max(const Vector3& value1, const Vector3& value2)
	{
		return Vector3((value1._x > value2._x) ? value1._x : value2._x,
					   (value1._y > value2._y) ? value1._y : value2._y,
					   (value1._z > value2._z) ? value1._z : value2._z);
	}

	static Vector3 Min(const Vector3& value1, const Vector3& value2)
	{
		return Vector3((value1._x < value2._x) ? value1._x : value2._x,
					   (value1._y < value2._y) ? value1._y : value2._y,
					   (value1._z < value2._z) ? value1._z : value2._z);
	}

	static Vector3 Multiply(const Vector3& value1, const float& scalar)
	{
		return Vector3(value1 * scalar);
	}

	static Vector3 Lerp(const Vector3& value1, const Vector3& value2, const float& amount)
	{
		return Vector3((value1) + (value2 - value1) * amount);
	}

	static float Dot(const Vector3& value1, const Vector3& value2)
	{
		return (value1._x * value2._x + value1._y * value2._y + value1._z * value2._z);
	}

	static Vector3 Cross(const Vector3& value1, const Vector3& value2)
	{
		return Vector3(value1._y * value2._z - value1._z * value2._y,
					   value1._z * value2._x - value1._x * value2._z,
					   value1._x * value2._y - value1._y * value2._x);
	}

	static float Distance(const Vector3& value1, const Vector3& value2)
	{
		return Vector3(fabs(value1._x - value2._x),
							  fabs(value1._y - value2._y),
							  fabs(value1._z - value2._z)).Length();
	}

	static Vector3 Up()											{ return Vector3(0.0f, 1.0f, 0.0f); }
	static Vector3 Down()										{ return Vector3(0.0f, -1.0f, 0.0f); }
	static Vector3 Right()										{ return Vector3(1.0f, 0.0f, 0.0f); }
	static Vector3 Left()										{ return Vector3(-1.0f, 0.0f, 0.0f); }
	static Vector3 Backward()									{ return Vector3(0.0f, 0.0f, -1.0f); }
	static Vector3 Forward()									{ return Vector3(0.0f, 0.0f, 1.0f); }
	static Vector3 Zero()										{ return Vector3(0.0f, 0.0f, 0.0f); }
	static Vector3 One()										{ return Vector3(1.0f, 1.0f, 1.0f); }
	static Vector3 UnitX()										{ return Vector3(1.0f, 0.0f, 0.0f); }
	static Vector3 UnitY()										{ return Vector3(0.0f, 1.0f, 0.0f); }
	static Vector3 UnitZ()										{ return Vector3(0.0f, 0.0f, 1.0f); }



	Vector3(const Vector3& other)								{ _x = other._x; _y = other._y; _z = other._z; }
	Vector3& operator =   (const Vector3& other)				{ _x = other._x; _y = other._y; _z = other._z; return *this; }

	Vector3  operator +   (const Vector3& other) const			{ return Vector3(_x + other._x, _y + other._y, _z + other._z); }
	Vector3& operator +=  (const Vector3& other)					{ _x += other._x; _y += other._y; _z += other._z; return *this; }

	Vector3  operator -   (const Vector3& other) const			{ return Vector3(_x - other._x, _y - other._y, _z - other._z); }
	Vector3& operator -=  (const Vector3& other)					{ _x -= other._x; _y -= other._y; _z -= other._z; return *this; }
	Vector3  operator -() const									{ return Vector3(-_x, -_y, -_z); }

	Vector3  operator *	  (const float scalar) const			{ return Vector3(_x * scalar, _y * scalar, _z * scalar); }
	Vector3	 operator *   (const Vector3& other) const			{ return Vector3(_x * other._x, _y * other._y, _z * other._z); }
	Vector3& operator *=  (const float scalar)					{ _x *= scalar; _y *= scalar; _z *= scalar; return *this; }


	Vector3  operator /   (float amount) const					{ return Vector3(_x / amount, _y / amount, _z / amount); }
	Vector3& operator /=  (float amount)						{ _x /= amount; _y /= amount; _z /= amount; return *this; }

	Vector3  operator /   (Vector3& amount) const					{ return Vector3(_x / amount._x, _y / amount._y, _z / amount._z); }
	Vector3& operator /=  (Vector3& amount)						{ _x /= amount._x; _y /= amount._y; _z /= amount._z; return *this; }

	bool	 operator ==  (const Vector3& other) const			{ return _x == other._x && _y == other._y && _z == other._z; }
	bool	 operator !=  (const Vector3& other) const			{ return _x != other._x || _y != other._y || _z != other._z; }
};
#endif //VECTOR3_H_INCLUDED