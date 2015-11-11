/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	Vector3 class declaration
*/


#ifndef FOREST_MATH_VECTOR3_H
#define FOREST_MATH_VECTOR3_H

#include <cassert>

#ifndef FOREST_DEFINES_STRINGSTREAM_H
	#include "StringStream.h"
#endif

#include "Common.h"

namespace Forest
{
	namespace Math
	{
		class Vector3
		{
		public:
			static const Vector3 Zero() { return Vector3(0.0f); }
			static const Vector3 Unit() { return Vector3(1.0f); }
			static const Vector3 Left() { return Vector3(-1.0f, 0.0f, 0.0f); }
			static const Vector3 Right() { return Vector3(1.0f, 0.0f, 0.0f); };
			static const Vector3 Up() { return Vector3(0.0f, 1.0f, 0.0f); }
			static const Vector3 Down() { return Vector3(0.0f, -1.0f, 0.0f); }
			static const Vector3 Backward() { return Vector3(0.0f, 0.0f, 1.0f); }
			static const Vector3 Forward() { return Vector3(0.0f, 0.0f, -1.0f); }

		public:
			//Constructors
			Vector3() : x(0.0f), y(0.0f), z(0.0f) {};
			Vector3(const float& s) : x(s), y(s), z(s) {};
			Vector3(const float& _x, const float& _y, const float& _z) : x(_x), y(_y), z(_z) {};

			//Comparison
			bool operator==(const Vector3& v) const;
			bool operator!=(const Vector3& v) const;

			//Negation
			const Vector3 operator-() const;

			//Assignment
			const Vector3& operator=(const Vector3& v);
			const Vector3& operator+=(const Vector3& v);
			const Vector3& operator+=(const float& s);
			const Vector3& operator-=(const Vector3& v);
			const Vector3& operator-=(const float& s);
			const Vector3& operator*=(const Vector3& v);
			const Vector3& operator*=(const float& s);
			const Vector3& operator/=(const Vector3& v);
			const Vector3& operator/=(const float& s);

			//Add
			const Vector3 operator+(const Vector3& v) const;
			const Vector3 operator+(const float& s) const;

			//Subtract
			const Vector3 operator-(const Vector3& v) const;
			const Vector3 operator-(const float& s) const;

			//Multiply
			const Vector3 operator*(const Vector3& v) const;
			const Vector3 operator*(const float& s) const;

			//Divide
			const Vector3 operator/(const Vector3& v) const;
			const Vector3 operator/(const float& s) const;

			//Print
			friend inline uostream& operator<<(uostream& stream, const Vector3& v);

			//Other operations
			const float Dot(const Vector3& v) const;
			const float Length() const;
			const Vector3& Normalize();
			const Vector3 Cross(const Vector3& v) const;

		public:
			float x;
			float y;
			float z;
		};
	}
}

#endif //FOREST_MATH_VECTOR3_H