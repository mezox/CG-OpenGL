/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Quaternion class definition
*/

#include "Quaternion.h"

#ifndef FOREST_MATH_COMMON_H
	#include "Common.h"
#endif

namespace Forest
{
	namespace Math
	{
		Quaternion::Quaternion() :
			v(Vector3(0.0f)),
			w(0.0f)
		{
		}

		Quaternion::Quaternion(const float & _x, const float & _y, const float & _z, const float & _w) : 
			v(_x, _y, _z),
			w(_w)
		{
		}

		Quaternion::Quaternion(const Vector3 & axis, const float angle)
		{
			float halfTheta = toRadians(angle) * 0.5f;
			float s = sinf(halfTheta);

			w = cosf(halfTheta);
			v.x = axis.x * s;
			v.y = axis.y * s;
			v.z = axis.z * s;
		}

		Quaternion::Quaternion(const Vector3 & vec)
		{
			float c = (float)(mpi / 360),
				x = vec.x * c,
				y = vec.y * c,
				z = vec.z * c,

				c1 = cos(y),
				s1 = sin(y),
				c2 = cos(-z),
				s2 = sin(-z),
				c3 = cos(x),
				s3 = sin(x),

				c1c2 = c1 * c2,
				s1s2 = s1 * s2;

			w = c1c2 * c3 - s1s2 * s3;
			v.x = c1c2 * s3 + s1s2 * c3;
			v.y = s1 * c2 * c3 + c1 * s2 * s3;
			v.z = c1 * s2 * c3 - s1 * c2 * s3;
		}

		Quaternion & Quaternion::operator*(const Quaternion & q)
		{
			w = w*q.w - v.Dot(q.v);
			v = v*q.w + q.v*w + v.Cross(q.v);

			return *this;
		}

		Vector3 Quaternion::operator*(const Vector3 & V)
		{
			Quaternion p;

			p.w = 0;
			p.v = V;

			Vector3 vcV = v.Cross(V);
			return V + vcV*(2 * w) + v.Cross(vcV) * 2;
		}

		Quaternion Quaternion::Conjugate() const
		{
			Quaternion q;

			q.w = w;
			q.v.x = -v.x;
			q.v.y = -v.y;
			q.v.z = -v.z;

			return q;
		}

		float Quaternion::Length() const
		{
			return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z + w*w);
		}
	}
}