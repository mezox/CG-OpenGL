/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tom� Kubov?�k, t.kubovcik@gmail.com
*	File desc:	Mathematics helper header file
*/


#ifndef FOREST_MATH_COMMON_H
#define FOREST_MATH_COMMON_H

#ifndef _CMATH_
	#include <cmath>
#endif

namespace Forest
{
	namespace Math
	{
		const float epsilon = 0.00001f;		//epsilon for single precision
		const float mpi = 3.1415926f;

		static inline float toDegrees(float radians)
		{
			return radians * 180.0f / (float)mpi;
		}

		static inline float toRadians(float degrees)
		{
			return (float)(mpi * degrees / 180.0f);
		}

		static inline bool FloatEqual(float a, float b)
		{
			const float d = a - b;

			if (d<epsilon && d>-epsilon)
				return true;
			else
				return false;
		}
	}
}


#endif