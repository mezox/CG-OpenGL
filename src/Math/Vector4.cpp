/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	Vector4 class definition
*/

#include "Vector4.h"

namespace Forest
{
	namespace Math
	{
		bool Vector4::operator==(const Vector4 & v) const
		{
			return (x == v.x && y == v.y && z == v.z && w == v.w);
		}

		bool Vector4::operator!=(const Vector4 & v) const
		{
			return !(*this == v);
		}

		const Vector4 Vector4:: operator-() const
		{
			return Vector4(-x, -y, -z, -w);
		}

		const Vector4 & Vector4::operator=(const Vector4 & v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;

			return *this;
		}

		const Vector4 & Vector4::operator+=(const Vector4 & v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;

			return *this;
		}

		const Vector4 & Vector4::operator+=(const float & s)
		{
			x += s;
			y += s;
			z += s;
			w += s;

			return *this;
		}

		const Vector4 & Vector4::operator-=(const Vector4 & v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;

			return *this;
		}

		const Vector4 & Vector4::operator-=(const float & s)
		{
			x -= s;
			y -= s;
			z -= s;
			w -= s;

			return *this;
		}

		const Vector4 & Vector4::operator*=(const Vector4 & v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;

			return *this;
		}

		const Vector4 & Vector4::operator*=(const float & s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;

			return *this;
		}

		const Vector4 & Vector4::operator/=(const Vector4 & v)
		{
			assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f && v.w != 0.0f);

			x /= v.x;
			y /= v.y;
			z /= v.z;
			w /= v.w;

			return *this;
		}

		const Vector4 & Vector4::operator/=(const float & s)
		{
			assert(s != 0.0f);

			float r = 1.0f / s;

			x *= r;
			y *= r;
			z *= r;
			w *= r;

			return *this;
		}

		const Vector4 Vector4::operator+(const Vector4 & v) const
		{
			return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		const Vector4 Vector4::operator+(const float & s) const
		{
			return Vector4(x + s, y + s, z + s, w + s);
		}

		const Vector4 Vector4::operator-(const Vector4 & v) const
		{
			return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
		}
		const Vector4 Vector4::operator-(const float & s) const
		{
			return Vector4(x - s, y - s, z - s, w - s);
		}
		const Vector4 Vector4::operator*(const Vector4 & v) const
		{
			return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
		}

		const Vector4 Vector4::operator*(const float & s) const
		{
			return Vector4(x * s, y * s, z * s, w * s);
		}

		const Vector4 Vector4::operator/(const Vector4 & v) const
		{
			assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f && v.w != 0.0f);

			return Vector4((float)(x / v.x), (float)(y / v.y), (float)(z / v.z), (float)(w / v.w));
		}

		const Vector4 Vector4::operator/(const float & s) const
		{
			assert(s != 0.0f);

			float r = 1.0f / s;

			return Vector4(x * r, y * r, z * r, w * r);
		}

		const float Vector4::Dot(const Vector4 & v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		const float Vector4::Length() const
		{
			return (float)sqrt((*this).Dot(*this));
		}

		const Vector4 & Vector4::Normalize()
		{
			(*this) = (*this) / (*this).Length();

			return *this;
		}

		inline uostream & operator<<(uostream & stream, const Vector4 & v)
		{
			stream << "Vector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";

			return stream;
		}
}
}