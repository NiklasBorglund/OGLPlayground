//Matrix4x4.h
//A row major matrix 4x4 class

#ifndef MATRIX4X4_H_INCLUDED
#define MATRIX4X4_H_INCLUDED

#include <math.h>
#include <string>
#include "Vector3.h"

class Matrix4x4
{
public:
	union
		{
			struct
			{
				float	_11, _12, _13, _14;
				float	_21, _22, _23, _24;
				float	_31, _32, _33, _34;
				float	_41, _42, _43, _44;
			};
			float	m[4][4];
            float   mat[16];
		};

		Matrix4x4(float m00, float m01, float m02, float m03,
				  float m10, float m11, float m12, float m13,
				  float m20, float m21, float m22, float m23,
				  float m30, float m31, float m32, float m33)
		{
			_11 = m00; _12 = m01; _13 = m02; _14 = m03;
			_21 = m10; _22 = m11; _23 = m12; _24 = m13;
			_31 = m20; _32 = m21; _33 = m22; _34 = m23;
			_41 = m30; _42 = m31; _43 = m32; _44 = m33;
		}
		Matrix4x4(float val)
		{
			_11 = _12 = _13 = _14 = val;
			_21 = _22 = _23 = _24 = val;
			_31 = _32 = _33 = _34 = val;
			_41 = _42 = _43 = _44 = val;
		}
		Matrix4x4(){SetZero();}
		void SetZero()
		{
			_11 = _12 = _13 = _14 = 0.0f;
			_21 = _22 = _23 = _24 = 0.0f;
			_31 = _32 = _33 = _34 = 0.0f;
			_41 = _42 = _43 = _44 = 0.0f;
		}
		void SetIdentity()
		{
			_12 = _13 = _14 = 0.0f;
			_21 = _23 = _24 = 0.0f;
			_31 = _32 = _34 = 0.0f;
			_41 = _42 = _43 = 0.0f;
			_11 = _22 = _33 = _44 = 1.0f;
		}
		void SetTranslationXYZ(float x, float y, float z)
		{
			SetIdentity();
			_41 = x; _42 = y; _43 = z;
		}
		void SetScale(float x, float y, float z)
		{
			SetIdentity();
			_11 = x; _22 = y; _33 = z;
		}
		void SetScale(const Vector3& scale)
		{
			SetScale(scale._x, scale._y, scale._z);
		}
		void SetScale(float scale)
		{
			SetScale(scale, scale, scale);
		}
		void SetRotationX(float x)
		{
			float sinus = sin(x);
			float cosinus = cos(x);
			_11 = 1.0f; _12 = 0.0f;    _13 = 0.0f;    _14 = 0.0f;
			_21 = 0.0f; _22 = cosinus; _23 = sinus;   _24 = 0.0f;
			_31 = 0.0f; _32 = -sinus;  _33 = cosinus; _34 = 0.0f;
			_41 = 0.0f; _42 = 0.0f;    _43 = 0.0f;    _44 = 1.0f;
		}
		void SetRotationY(float y)
		{
			float sinus = sin(y);
			float cosinus = cos(y);
			_11 = cosinus; _12 = 0.0f; _13 = -sinus;  _14 = 0.0f;
			_21 = 0.0f;    _22 = 1.0f; _23 = 0.0f;    _24 = 0.0f;
			_31 = sinus;   _32 = 0.0f; _33 = cosinus; _34 = 0.0f;
			_41 = 0.0f;    _42 = 0.0f; _43 = 0.0f;    _44 = 1.0f;
		}
		void SetRotationZ(float z)
		{
			float sinus = sin(z);
			float cosinus = cos(z);
			_11 = cosinus; _12 = sinus;   _13 = 0.0f; _14 = 0.0f;
			_21 = -sinus;  _22 = cosinus; _23 = 0.0f; _24 = 0.0f;
			_31 = 0.0f;    _32 = 0.0f;    _33 = 1.0f; _34 = 0.0f;
			_41 = 0.0f;    _42 = 0.0f;    _43 = 0.0f; _44 = 1.0f;
		}
		void SetProjectionMatrixRH(float nearPlane, float farPlane, float fovY, float aspect)
		{
			float yScale = (float)(1.0f / tan(fovY * 0.5f));
			float xScale = yScale / aspect;
			float k = farPlane / (nearPlane - farPlane);

			_11 = xScale;	_12 = 0.0f;		_13 = 0.0f;				_14 = 0.0f;
			_21 = 0.0f;		_22 = yScale;	_23 = 0.0f;				_24 = 0.0f;
			_31 = 0.0f;		_32 = 0.0f;		_33 = k;				_34 = -1.0f;
			_41 = 0.0f;		_42 = 0.0f;		_43 = nearPlane * k;	_44 = 1.0f;
		}
		void SetOrthographicMatrixRH(float width, float height, float zNear, float zFar)
		{
			_11 = (0.5f * width);	_12 = 0.0f;				_13 = 0.0f;						_14 = 0.0f;
			_21 = 0.0f;				_22 = (0.5f * height);	_23 = 0.0f;						_24 = 0.0f;
			_31 = 0.0f;				_32 = 0.0f;				_33 = (1 / (zNear - zFar));		_34 = 0.0f;
			_41 = 0.0f;				_42 = 0.0f;				_43 = (zNear / (zNear - zFar));	_44 = 1.0f;
		}
		void SetLookAtRH(const Vector3& position, const Vector3& lookAt, const Vector3& up)
		{
			Vector3 Z(position - lookAt);
			Z.Normalize();

			Vector3 X(Vector3::Cross(up, Z));
			X.Normalize();

			Vector3 Y(Vector3::Cross(Z, X));

			_11 = X._x;		_12 = Y._x;		_13 = Z._x;				_14 = 0.0f;
			_21 = X._y;		_22 = Y._y;		_23 = Z._y;				_24 = 0.0f;
			_31 = X._z;		_32 = Y._z;		_33 = Z._z;				_34 = 0.0f;
			_41 = -Vector3::Dot(X, position);		_42 = -Vector3::Dot(Y, position);		_43 = -Vector3::Dot(Z, position);	_44 = 1.0f;
		}
		void Transpose()
		{
			float temp = _12;
			_12 = _21;
			_21 = temp;

			temp = _13;
			_13 = _31;
			_31 = temp;

			temp = _14;
			_14 = _41;
			_41 = temp;

			temp = _23;
			_23 = _32;
			_32 = temp;

			temp = _24;
			_24 = _42;
			_42 = temp;

			temp = _34;
			_34 = _43;
			_43 = temp;
		}
		const float* Pointer() const
		{
			return &mat[0];
		}
		//static functions
		static Matrix4x4 GetTranslationMatrix(float x, float y, float z)
		{
			return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							x,    y,    z,   1.0f);
		}
		static Matrix4x4 GetScale(float x, float y, float z)
		{
			return Matrix4x4( x,   0.0f, 0.0f, 0.0f,
							 0.0f,  y,   0.0f, 0.0f,
							 0.0f, 0.0f,  z,   0.0f,
							 0.0f, 0.0f, 0.0f, 1.0f);
		}
		static Matrix4x4 GetRotationX(float x)
		{
			float sinus = sin(x);
			float cosinus = cos(x);
			return Matrix4x4(1.0f, 0.0f,    0.0f,    0.0f,
							 0.0f, cosinus, sinus,   0.0f,
							 0.0f, -sinus,  cosinus, 0.0f,
							 0.0f, 0.0f,    0.0f,    1.0f);
		}
		static Matrix4x4 GetRotationY(float y)
		{
			float sinus = sin(y);
			float cosinus = cos(y);
			return Matrix4x4(cosinus, 0.0f, -sinus,  0.0f,
							 0.0f,    1.0f, 0.0f,    0.0f,
							 sinus,   0.0f, cosinus, 0.0f,
							 0.0f,    0.0f, 0.0f,    1.0f);
		}
		static Matrix4x4 GetRotationZ(float z)
		{
			float sinus = sin(z);
			float cosinus = cos(z);
			return Matrix4x4(cosinus, sinus,   0.0f, 0.0f,
							 -sinus,  cosinus, 0.0f, 0.0f,
							 0.0f,    0.0f,    1.0f, 0.0f,
							 0.0f,    0.0f,    0.0f, 1.0f);
		}
		//Projection & LookAt functions
		static Matrix4x4 CreateProjectionMatrixRH(float nearPlane, float farPlane, float fovY, float aspect)
		{
			float yScale = (float)(1.0f / tan(fovY * 0.5f));
			float xScale = yScale / aspect;
			float k = farPlane / (nearPlane - farPlane);
		
			return Matrix4x4(xScale, 0.0f,	 0.0f,			0.0f,
							 0.0f,	 yScale, 0.0f,			0.0f,
							 0.0f,	 0.0f,	 k,				-1.0f,
							 0.0f,	 0.0f,	 nearPlane * k, 1.0f);
		}
		static Matrix4x4 CreateOrthographicMatrixRH(float width, float height, float zNear, float zFar)
		{
			return Matrix4x4((0.5f * width), 0.0f,	 0.0f,			0.0f,
							 0.0f,	 (0.5f * height), 0.0f,			0.0f,
							 0.0f,	 0.0f,	 (1 / (zNear - zFar)),				0.0f,
							 0.0f,	 0.0f,	 (zNear / (zNear - zFar)), 1.0f);
		}
		static Matrix4x4 CreateLookAtRH(const Vector3& position, const Vector3& lookAt, const Vector3& up)
		{
			Vector3 Z(position - lookAt);
			Z.Normalize();

			Vector3 X(Vector3::Cross(up, Z));
			X.Normalize();

			Vector3 Y(Vector3::Cross(Z, X));

			return Matrix4x4(			 X._x,						 Y._x,						 Z._x,		     0.0f,
										 X._y,						 Y._y,						 Z._y,			 0.0f,
										 X._z,						 Y._z,						 Z._z,			 0.0f,
							 -Vector3::Dot(X, position), -Vector3::Dot(Y, position), -Vector3::Dot(Z, position), 1.0f);
		}
		static Matrix4x4 Identity()										{ return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
					 			 			 			 			 			 		   0.0f, 1.0f, 0.0f, 0.0f,
					 			 			 			 			 					   0.0f, 0.0f, 1.0f, 0.0f,
					 			 			 			 			 					   0.0f, 0.0f, 0.0f, 1.0f); }
		static Matrix4x4 Zero()											{ return Matrix4x4(0.0f, 0.0f, 0.0f, 0.0f,
					 			 			 			 			 			 		   0.0f, 0.0f, 0.0f, 0.0f,
					 			 			 			 			 					   0.0f, 0.0f, 0.0f, 0.0f,
					 			 			 			 			 					   0.0f, 0.0f, 0.0f, 0.0f); }
		const float& operator ()  (int row, int column) const							{ return m[row][column]; }
		float& operator		  ()  (int row, int column)									{ return m[row][column]; }
		bool operator		  ==  (const Matrix4x4& other) const							{ return (memcmp(this, &other, sizeof(Matrix4x4)) == 0); }
		bool operator		  !=  (const Matrix4x4& other) const							{ return (memcmp(this, &other, sizeof(Matrix4x4)) != 0); }
		Matrix4x4& operator   =   (const Matrix4x4& other)								{ memcpy(this, &other, sizeof(Matrix4x4)); return *this; }
		Matrix4x4 operator*(const Matrix4x4& other) const
		{
			Matrix4x4 tempMatrix;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						tempMatrix(i, j) += m[i][k] * other(k, j);
					}
				}
			}
			return tempMatrix;
		}
		Matrix4x4& operator*=(const Matrix4x4& other)
		{
			//Copy the matrix to a temp variable
			Matrix4x4 tempMatrix(*this);

			//Set the current matrix to zero
			SetZero();

			//Multiply the temp variable to the "other" matrix
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						m[i][j] += tempMatrix(i, k) * other(k, j);
					}
				}
			}
			return *this;
		}

};
#endif //MATRIX4X4_H_INCLUDED