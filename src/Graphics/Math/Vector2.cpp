/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	Vector2 class definition
*/

#include "Vector2.h"

#ifndef FOREST_MATH_COMMON_H
#include "Common.h"
#endif

namespace Forest
{
	namespace Math
	{
		bool Vector2::operator==(const Vector2 & v) const
		{
			return ((v.x == x) && (v.y == y));
		}


		bool Vector2::operator!=(const Vector2 & v) const
		{
			return !((*this) == v);
		}


		const Vector2 & Vector2::operator=(const Vector2 & v)
		{
			x = v.x; y = v.y; return *this;
		}


		inline uostream & operator<<(uostream & stream, const Vector2 & v)
		{
			stream << "Vector2(" << v.x << ", " << v.y << ")";
			return stream;
		}
	}
}