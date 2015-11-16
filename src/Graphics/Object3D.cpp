#include "Object3D.h"

namespace Forest
{
	namespace Graphics
	{
		Object3D::Object3D() :
			m_Position(0.0f),
			m_Rotation(0.0f),
			m_Scale(1.0f),
			m_Matrix(Matrix4::Identity()),
			m_bNeedUpdate(false)
		{
		}


		Object3D::Object3D(const Vector3 & position) :
			m_Position(position),
			m_Rotation(0.0f),
			m_Scale(1.0f),
			m_Matrix(Matrix4::Identity()),
			m_bNeedUpdate(true)
		{
		}

		Object3D::Object3D(const Vector3 & position, const Vector3 & rotation) :
			m_Position(position),
			m_Rotation(rotation),
			m_Scale(1.0f),
			m_Matrix(Matrix4::Identity()),
			m_bNeedUpdate(true)
		{
		}

		Object3D::Object3D(const Vector3 & position, const Vector3 & rotation, const Vector3 & scale) :
			m_Position(position),
			m_Rotation(rotation),
			m_Scale(scale),
			m_Matrix(Matrix4::Identity()),
			m_bNeedUpdate(true)
		{
		}

		const Matrix4& Object3D::Matrix()
		{
			if (m_bNeedUpdate)
				Update();

			return m_Matrix;
		}


		/// <summary>
		/// Updates this instance of matrix.
		/// Applies rotation, translation and scale 
		/// </summary>
		void Object3D::Update()
		{
			Quaternion q(m_Rotation);

			m_Matrix = Matrix4::Identity();
			m_Matrix.Rotate(q);
			m_Matrix.Scale(m_Scale);
			m_Matrix.Translate(m_Position);

			m_bNeedUpdate = false;
		}
	}
}