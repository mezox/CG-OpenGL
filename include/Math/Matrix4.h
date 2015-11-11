/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Matrix4 class declaration
*/

#ifndef FOREST_MATH_MATRIX4_H
#define FOREST_MATH_MATRIX4_H

#include "Vector4.h"
#include "Common.h"
//#include "Quaternion.h"

namespace Forest
{
	namespace Math
	{
		class Matrix4
		{
		public:
			static Matrix4 Identity() { return Matrix4(1.0f); }
			static Matrix4 Orthographic(float left, float right, float bottom, float top, float nearp, float farp);
			static Matrix4 Perspective(float fov, float aspect, float nearp, float farp);
			static Matrix4 MakeTranslation(const Vector3& pos);
			static Matrix4 MakeRotation(float angle, const Vector3& axis);
			static Matrix4 MakeRotation(const Vector3& rot);
			//static Matrix4 MakeRotation(const Quaternion &q);
			static Matrix4 MakeScale(const Vector3& scale);

		public:
			Matrix4();
			Matrix4(float diagonal);

			//Access
			Vector4&		operator[] (const size_t i);
			const Vector4&	operator [] (const size_t i) const;
			const float		&operator()(const size_t row, const size_t column) const;
			float			&operator()(const size_t row, const size_t column); //Access and modify

			bool			operator == (const Matrix4& m) const;
			bool			operator != (const Matrix4& m) const;

			//Arithmetic
			Matrix4&	operator + (const Matrix4& m);
			Matrix4&	operator * (const float s);
			Vector4		operator * (const Vector4& v) const;
			Matrix4&	operator * (const Matrix4& m);

			//Translation
			Matrix4& Translate(const Vector3& v);
			Matrix4& TranslateTo(const Vector3& v);

			//Scaling
			Matrix4& Scale(const Vector3& v);

			//Rotation
			
			Matrix4& Rotate(float angle, const Vector3& axis);

			friend inline uostream& operator<<(uostream& stream, const Matrix4& m);

		public:
			Vector4 c1;
			Vector4 c2;
			Vector4 c3;
			Vector4 c4;
		};
	}
}

#endif	//FOREST_MATH_MATRIX4_H