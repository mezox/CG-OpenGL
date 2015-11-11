/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	Vector3 class definition
*/

#include "Vector3.h"

#ifndef FOREST_MATH_COMMON_H
	#include "Common.h"
#endif

namespace Forest
{
	namespace Math
	{
		bool Vector3::operator==(const Vector3 & v) const
		{
			return (FloatEqual(x,v.x) && FloatEqual(y,v.y) && FloatEqual(z,v.z));
		}

		bool Vector3::operator!=(const Vector3 & v) const
		{
			return !(*this == v);
		}

		const Vector3 Vector3::operator-() const
		{
			return Vector3(-x, -y, -z);
		}

		const Vector3 & Vector3::operator=(const Vector3 & v)
		{
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		const Vector3 & Vector3::operator+=(const Vector3 & v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		const Vector3 & Vector3::operator+=(const float & s)
		{
			x += s;
			y += s;
			z += s;

			return *this;
		}

		const Vector3 & Vector3::operator-=(const Vector3 & v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		const Vector3 & Vector3::operator-=(const float & s)
		{
			x -= s;
			y -= s;
			z -= s;

			return *this;
		}

		const Vector3 & Vector3::operator*=(const Vector3 & v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return *this;
		}

		const Vector3 & Vector3::operator*=(const float & s)
		{
			x *= s;
			y *= s;
			z *= s;

			return *this;
		}

		const Vector3 & Vector3::operator/=(const Vector3 & v)
		{
			assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);

			x /= v.x;
			y /= v.y;
			z /= v.z;

			return *this;
		}

		const Vector3 & Vector3::operator/=(const float & s)
		{
			assert(s != 0.0f);

			float r = 1.0f / s;

			x *= s;
			y *= s;
			z *= s;

			return *this;
		}

		const Vector3 Vector3::operator+(const Vector3 & v) const
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		const Vector3 Vector3::operator+(const float & s) const
		{
			return Vector3(x + s, y + s, z + s);
		}

		const Vector3 Vector3::operator-(const Vector3 & v) const
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		const Vector3 Vector3::operator-(const float & s) const
		{
			return Vector3(x - s, y - s, z - s);
		}

		const Vector3 Vector3::operator*(const Vector3 & v) const
		{
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		const Vector3 Vector3::operator*(const float & s) const
		{
			return Vector3(x * s, y * s, z * s);
		}

		const Vector3 Vector3::operator/(const Vector3 & v) const
		{
			assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);

			return Vector3((float)(x / v.x), (float)(y / v.y), (float)(z / v.z));
		}

		const Vector3 Vector3::operator/(const float & s) const
		{
			assert(s != 0.0f);

			float r = 1.0f / s;

			return Vector3(x * r, y * r, z * r);
		}

		const float Vector3::Dot(const Vector3 & v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		const float Vector3::Length() const
		{
			return (float)sqrt((*this).Dot(*this));
		}

		const Vector3 & Vector3::Normalize()
		{
			(*this) = (*this) / (*this).Length();

			return *this;
		}

		const Vector3 Vector3::Cross(const Vector3 & v) const
		{
			return Vector3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
		}

		inline uostream & operator<<(uostream & stream, const Vector3 & v)
		{
			stream << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";

			return stream;
		}

}
}