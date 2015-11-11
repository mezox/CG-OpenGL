/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Quaternion class declaration
*/

#ifndef FOREST_MATH_QUATERNION_H
#define FOREST_MATH_QUATERNION_H

#ifndef FOREST_MATH_VECTOR3_H
	#include "Vector3.h"
#endif

namespace Forest
{
	namespace Math
	{
		class Quaternion
		{
		public:
			static Quaternion Identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }

		public:
			Quaternion();
			Quaternion(const float& _x, const float& _y, const float& _z, const float& _w);
			Quaternion(const Vector3& axis, const float angle);
			Quaternion(const Vector3& vec);


			Quaternion&	operator*(const Quaternion& q);
			Vector3		operator*(const Vector3& V);
			
			Quaternion	Conjugate() const;
			float		Length() const;
			
		public:
			float	w;
			Vector3	v;
		};
	}
}

#endif //FOREST_MATH_QUATERNION_H
