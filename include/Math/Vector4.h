/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	Vector4 class declaration
*/


#ifndef FOREST_MATH_VECTOR4_H
#define FOREST_MATH_VECTOR4_H

#ifndef FOREST_MATH_VECTOR3_H
	#include "Vector3.h"
#endif

namespace Forest
{
	namespace Math
	{
		class Vector4
		{
		public:
			static const Vector4 Zero() { return Vector4(0.0f); }
			static const Vector4 Unit() { return Vector4(1.0f); }

		public:
			//Constructors
			Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
			Vector4(const float& s) : x(s), y(s), z(s), w(s) {};
			Vector4(const float& _x, const float& _y, const float& _z, const float& _w) : x(_x), y(_y), z(_z), w(_w) {};
			Vector4(const Vector3& v, const float& _w) : x(v.x), y(v.y), z(v.z), w(_w) {};
			Vector4(const float& _x, const Vector3& v) : x(_x), y(v.x), z(v.y), w(v.z) {};

			//Comparison
			bool operator==(const Vector4& v) const;
			bool operator!=(const Vector4& v) const;

			//Negation
			const Vector4 operator-() const;

			//Assignment
			const Vector4& operator=(const Vector4& v);
			const Vector4& operator+=(const Vector4& v);
			const Vector4& operator+=(const float& s);
			const Vector4& operator-=(const Vector4& v);
			const Vector4& operator-=(const float& s);
			const Vector4& operator*=(const Vector4& v);
			const Vector4& operator*=(const float& s);
			const Vector4& operator/=(const Vector4& v);
			const Vector4& operator/=(const float& s);

			//Add
			const Vector4 operator+(const Vector4& v) const;
			const Vector4 operator+(const float& s) const;

			//Subtract
			const Vector4 operator-(const Vector4& v) const;
			const Vector4 operator-(const float& s) const;

			//Multiply
			const Vector4 operator*(const Vector4& v) const;
			const Vector4 operator*(const float& s) const;

			//Divide
			const Vector4 operator/(const Vector4& v) const;
			const Vector4 operator/(const float& s) const;

			//Print
			friend inline uostream& operator<<(uostream& stream, const Vector4& v);

			//Other operations
			const float Dot(const Vector4& v) const;
			const float Length() const;
			const Vector4& Normalize();

		public:
			float x;
			float y;
			float z;
			float w;
		};
	}
}


#endif		//FOREST_MATH_VECTOR4_H