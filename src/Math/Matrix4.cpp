/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Matrix4 class definition
*/

#include "Matrix4.h"

#ifndef FOREST_MATH_COMMON_H
	#include "Common.h"
#endif

namespace Forest
{
	namespace Math
	{
		Matrix4::Matrix4()
		{
			c1 = Vector4::Zero();
			c2 = Vector4::Zero();
			c3 = Vector4::Zero();
			c4 = Vector4::Zero();
		}

		Matrix4::Matrix4(float diagonal)
		{
			Matrix4();

			c1.x = diagonal;
			c2.y = diagonal;
			c3.z = diagonal;
			c4.w = diagonal;
		}

		Vector4& Matrix4::operator[](const size_t i)
		{
			assert(i < 4);
			return *(&c1 + i);
		}

		const Vector4& Matrix4::operator [] (const size_t i) const
		{
			assert(i < 4);
			return *(&c1 + i);
		}

		const float& Matrix4::operator()(const size_t row, const size_t column) const
		{
			return *(&(&c1 + column - 1)->x + row - 1);
		}

		float& Matrix4::operator()(const size_t row, const size_t column)
		{
			return *(&(&c1 + column - 1)->x + row - 1);
		}

		bool Matrix4::operator ==(const Matrix4& m) const
		{
			return (m.c1 == c1) && (m.c2 == c2) && (m.c3 == c3) && (m.c4 == c4);
		}

		bool Matrix4::operator !=(const Matrix4& m) const
		{
			return !(*this == m);
		}


		/// <summary>
		/// Adds two matrices. Storing the result in this matrix
		/// </summary>
		/// <param name="m">Matrix to be added.</param>
		/// <returns>This matrix</returns>
		Matrix4& Matrix4::operator+(const Matrix4& m)
		{
			c1 += m.c1;
			c2 += m.c2;
			c3 += m.c3;
			c4 += m.c4;

			return *this;
		}


		/// <summary>
		/// Multiplies this matrix by another matrix, storing
		/// the result in this matrix.
		/// </summary>
		/// <param name="m">Matrix to be multiplied by.</param>
		/// <returns>Multiplied matrix</returns>
		Matrix4& Matrix4::operator*(const Matrix4& m)
		{
			Matrix4& v = *this;

			for (unsigned int y = 0; y < 4; y++)
				for (unsigned int x = 0; x < 4; x++)
					v(y, x) = v(y, 1) * m(1, x) +
					v(y, 2) * m(2, x) +
					v(y, 3) * m(3, x) +
					v(y, 4) * m(4, x);

			return *this;
		}


		/// <summary>
		/// Multiplies all matrix components by scalar value
		/// </summary>
		/// <param name="s">Scalar value.</param>
		/// <returns>Modified matrix</returns>
		Matrix4& Matrix4::operator*(const float s)
		{
			Matrix4& v = *this;

			for (int x = 1; x < 5; x++)
				for (int y = 1; y < 5; y++)
					v(x, y) *= s;

			return *this;
		}


		/// <summary>
		/// Transforms the point specified as 4D vector by this matrix
		/// </summary>
		/// <param name="v">Vector to transform (Vector4).</param>
		/// <returns>Transformed vector</returns>
		Vector4 Matrix4::operator*(const Vector4& v) const
		{
			return Vector4(
				c1.x * v.x + c2.x * v.y + c3.x * v.z + c4.x * v.w,
				c1.y * v.x + c2.y * v.y + c3.y * v.z + c4.y * v.w,
				c1.z * v.x + c2.z * v.y + c3.z * v.z + c4.z * v.w,
				c1.w * v.x + c2.w * v.y + c3.w * v.z + c4.w * v.w
				);
		}

		Matrix4& Matrix4::Translate(const Vector3& v)
		{
			c4.x += v.x;
			c4.y += v.y;
			c4.z += v.z;

			return *this;
		}

		Matrix4& Matrix4::TranslateTo(const Vector3& v)
		{
			c4.x = v.x;
			c4.y = v.y;
			c4.z = v.z;

			return *this;
		}

		/// <summary>
		/// Scales the specified v.
		/// </summary>
		/// <param name="v">The v.</param>
		/// <returns></returns>
		Matrix4& Matrix4::Scale(const Vector3& v)
		{
			c1.x *= v.x; c2.x *= v.x; c3.x *= v.x; c4.x *= v.x;
			c1.y *= v.y; c2.y *= v.y; c3.y *= v.y; c4.y *= v.y;
			c1.z *= v.z; c2.z *= v.z; c3.z *= v.z; c4.z *= v.z;

			return *this;
		}


		/// <summary>
		/// Creates the rotation matrix and rotates the object
		/// (multiplies object matrix with rotation matrix).
		///	Rotation around specified axis, by specified angle.
		/// Rotation axis must be normalized.
		/// </summary>
		/// <param name="angle">Angle of rotation (degrees).</param>
		/// <param name="axis">Axis of rotation (Vector3).</param>
		/// <returns>Rotated model matrix</returns>
		Matrix4& Matrix4::Rotate(float angle, const Vector3 &axis)
		{
			*this = *this * MakeRotation(angle, axis);

			return *this;
		}


		/// <summary>
		/// Constructs column order translation matrix
		/// </summary>
		/// <param name="pos">Position to translate to.</param>
		/// <returns>Translation matrix</returns>
		Matrix4 Matrix4::MakeTranslation(const Vector3& pos)
		{
			Matrix4 m = Matrix4::Identity();
			m.c4 = Vector4(pos.x, pos.y, pos.z, 1.0f);

			return m;
		}


		/// <summary>
		/// Constructs column order rotation matrix.
		/// </summary>
		/// <param name="angle">Angle of rotation in degrees.</param>
		/// <param name="axis">Axis of rotation.</param>
		/// <returns></returns>
		Matrix4 Matrix4::MakeRotation(float angle, const Vector3& axis)
		{
			Matrix4 m = Matrix4::Identity();

			//Create copy of axis and normalize it
			Vector3 axisNormalized = Vector3(axis);
			axisNormalized.Normalize();

			float x = axisNormalized.x, y = axisNormalized.y, z = axisNormalized.z;

			float rAngle = toRadians(angle);
			float c = cos(rAngle);
			float s = sin(rAngle);

			m.c1.x = x * x * (1.0f - c) + c;     m.c2.x = x * y * (1.0f - c) - z * s; m.c3.x = x * z * (1.0f - c) + y * s;
			m.c1.y = y * x * (1.0f - c) + z * s; m.c2.y = y * y * (1.0f - c) + c;     m.c3.y = y * z * (1.0f - c) - x * s;
			m.c1.z = z * x * (1.0f - c) - y * s; m.c2.z = y * z * (1.0f - c) + x * s; m.c3.z = z * z * (1.0f - c) + c;

			return m;
		}


		/// <summary>
		/// Constructs rotation matrix from quaternion
		/// </summary>
		/// <param name="q">Quaternion rotation.</param>
		/// <returns>Rotation matrix</returns>
		Matrix4 Matrix4::MakeRotation(const Quaternion& q)
		{
			Matrix4 m = Matrix4::Identity();

			float x = q.v.x, y = q.v.y, z = q.v.z, w = q.w,

			x2 = x + x,
			y2 = y + y,
			z2 = z + z,

			xx = x * x2,
			xy = x * y2,
			xz = x * z2,
			yy = y * y2,
			yz = y * z2,
			zz = z * z2,
			wx = w * x2,
			wy = w * y2,
			wz = w * z2;

			m.c1.x = 1.0f - (yy + zz);
			m.c2.x = xy - wz;
			m.c3.x = xz + wy;
			
			m.c1.y = xy + wz;
			m.c2.y = 1.0f - (xx + zz);
			m.c3.y = yz - wx;
			
			m.c1.z = xz - wy;
			m.c2.z = yz + wx;
			m.c3.z = 1 - (xx + yy);

			return m;
		}


		/// <summary>
		/// Computes rotation matrix from pitch, yaw and roll
		/// </summary>
		/// <param name="rot">Rotation specified by pitch, yaw, roll Vector3(pitch,yaw,roll).</param>
		/// <returns>Rotation matrix</returns>
		Matrix4 Matrix4::MakeRotation(const Vector3& rot)
		{
			Matrix4 m = Matrix4::Identity();

			float rPitch = toRadians(rot.x);
			float rYaw = toRadians(rot.y);
			float rRoll = toRadians(rot.z);

			float cosY = cosf(rYaw);
			float cosP = cosf(rPitch);
			float cosR = cosf(rRoll);
			float sinY = sinf(rYaw);
			float sinP = sinf(rPitch);
			float sinR = sinf(rRoll);

			m(0, 0) = cosR * cosY - sinR * sinP * sinY;
			m(0, 1) = sinR * cosY + cosR * sinP * sinY;
			m(0, 2) = -cosP * sinY;
			m(0, 3) = 0.0f;

			m(1, 0) = -sinR * cosP;
			m(1, 1) = cosR * cosP;
			m(1, 2) = sinP;
			m(1, 3) = 0.0f;

			m(2, 0) = cosR * sinY + sinR * sinP * cosY;
			m(2, 1) = sinR * sinY - cosR * sinP * cosY;
			m(2, 2) = cosP * cosY;
			m(2, 3) = 0.0f;

			m(3, 0) = 0.0f;
			m(3, 1) = 0.0f;
			m(3, 2) = 0.0f;
			m(3, 3) = 1.0f;

			return m;
		}


		/// <summary>
		/// Constructs column order scale matrix.
		/// </summary>
		/// <param name="scale">Scale given as Vector3.</param>
		/// <returns>Scale matrix</returns>
		Matrix4 Matrix4::MakeScale(const Vector3& scale)
		{
			Matrix4 m = Matrix4::Identity();
			m.c1.x = scale.x;
			m.c2.y = scale.y;
			m.c3.z = scale.z;

			return m;
		}


		/// <summary>
		/// Computes orthographic projection matrix.
		/// </summary>
		/// <param name="left">Left plane.</param>
		/// <param name="right">Right plane.</param>
		/// <param name="bottom">Bottom plane.</param>
		/// <param name="top">Top plane.</param>
		/// <param name="nearp">Near plane.</param>
		/// <param name="farp">Far plane.</param>
		/// <returns>Orthographics projection matrix</returns>
		Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float nearp, float farp)
		{
			Matrix4 r = Matrix4::Identity();

			float rmh = right - left;
			float tmb = top - bottom;
			float fmn = farp - nearp;

			float a = (right + left) / rmh;
			float b = (top + bottom) / tmb;
			float c = (farp + nearp) / fmn;

			r(1, 1) = 2.0f / rmh;	r(1, 2) = 0.0f;			r(1, 3) = 0.0f;			r(1, 4) = -a;
			r(2, 1) = 0.0f;			r(2, 2) = 2.0f / tmb;	r(2, 3) = 0.0f;			r(2, 4) = -b;
			r(3, 1) = 0.0f;			r(3, 2) = 0.0f;			r(3, 3) = -2.0f / fmn;	r(3, 4) = -c;
			r(4, 1) = 0.0f;			r(4, 2) = 0.0f;			r(4, 3) = 0.0f;			r(4, 4) = 1.0f;

			return r;
		}

		/// <summary>
		/// Computes the perspective projection matrix.
		/// </summary>
		/// <param name="fov">Field of view (degrees).</param>
		/// <param name="aspect">Aspect ration of window.</param>
		/// <param name="nearp">Near plane.</param>
		/// <param name="farp">Far plane.</param>
		/// <returns></returns>
		Matrix4 Matrix4::Perspective(float fov, float aspect, float nearp, float farp)
		{
			Matrix4 r = Matrix4::Identity();

			float thetaY = 0.5f * toRadians(fov);
			float tanThetaY = std::tan(thetaY);
			float tanThetaX = tanThetaY * aspect;
			float halfW = tanThetaX * nearp;
			float halfH = tanThetaY * nearp;
			float left = -halfW;
			float right = halfW;
			float bottom = -halfH;
			float top = halfH;
			float iWidth = 1.0f / (right - left);
			float iHeight = 1.0f / (top - bottom);
			float iDepth = 1.0f / (farp - nearp);

			r(1, 1) = 2.0f * nearp * iWidth;	r(1, 2) = 0.0f;						r(1, 3) = (right + left) * iWidth;			r(1, 4) = 0.0f;
			r(2, 1) = 0.0f;						r(2, 2) = 2.0f * nearp * iHeight;	r(2, 3) = (top + bottom) * iHeight;			r(2, 4) = 0.0f;
			r(3, 1) = 0.0f;						r(3, 2) = 0.0f;						r(3, 3) = -(farp + nearp) * iDepth;			r(3, 4) = -2.0f * (farp * nearp) * iDepth;
			r(4, 1) = 0.0f;						r(4, 2) = 0.0f;						r(4, 3) = -1.0f;							r(4, 4) = 0.0f;

			return r;
		}


		/// <summary>
		/// Output stream operator overload.
		/// </summary>
		/// <param name="stream">The stream.</param>
		/// <param name="m">Matrix to be outputted.</param>
		/// <returns></returns>
		inline uostream& operator<<(uostream& stream, const Matrix4& m)
		{
			stream << "Matrix4(\n";

			for (unsigned int x = 1; x < 5; x++)
			{
				stream << "\t";

				for (unsigned int y = 1; y < 5; y++)
					stream << m(x, y) << ", ";

				stream << std::endl;
			}

			stream << ")" << std::endl;

			return stream;
		}
	}
}