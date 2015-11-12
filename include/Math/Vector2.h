#ifndef FOREST_MATH_VECTOR2_H
#define FOREST_MATH_VECTOR2_H

#ifndef FOREST_DEFINES_STRINGSTREAM_H
	#include "StringStream.h"
#endif

namespace Forest
{
	namespace Math
	{
		class Vector2
		{
		public:
			static const Vector2 Zero() { return Vector2(); }
			static const Vector2 Unit() { return Vector2(1.0f, 1.0f); }


		public:
			//Constructors
			Vector2() : x(0.0f), y(0.0f) {}
			Vector2(const float _x, const float _y) : x(_x), y(_y) { }

			//Comparison
			bool operator==(const Vector2& v) const { return ((v.x == x) && (v.y == y)); }
			bool operator!=(const Vector2& v) const { return !((*this) == v); }

			//Assignment
			const Vector2& operator=(const Vector2& v) { x = v.x; y = v.y; return *this; }

			//Print
			friend inline uostream& operator<<(uostream& stream, const Vector2& v)
			{
				stream << "Vector2(" << v.x << ", " << v.y << ")";
				return stream;
			}

		public:
			float x;
			float y;
		};
	}
}

#endif	//FOREST_MATH_VECTOR2_H