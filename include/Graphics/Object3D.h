#ifndef FOREST_GRAPHICS_OBJECT3D_H
#define FOREST_GRAPHICS_OBJECT3D_H

#include <iostream>
#include <GL/glew.h>

#ifndef FOREST_MATH_MATHS_H
	#include "Maths.h"
#endif

#ifndef FOREST_GRAPHICS_OBJMODEL_H
	#include "OBJModel.h"
#endif

namespace Forest
{
	namespace Graphics
	{
		using namespace Forest::Math;

		class Object3D
		{
		public:
			Object3D();
			Object3D(const Vector3& position);
			Object3D(const Vector3& position, const Vector3& rotation);
			Object3D(const Vector3& position, const Vector3& rotation, const Vector3& scale);
			virtual ~Object3D() {}

			//Getters
			const Matrix4&		Matrix();
			const Vector3&		Position() const { return m_Position; }
			const Vector3&		Rotation() const { return m_Rotation; }
			const Vector3&		Scale() const { return m_Scale; }

			//Setters
			void	SetMatrix(const Matrix4& m) { m_Matrix = m; m_bNeedUpdate = true; }
			void	SetPosition(const Vector3& p) { m_Position = p; m_bNeedUpdate = true; }
			void	SetRotation(const Vector3& r) { m_Rotation = r; m_bNeedUpdate = true; }
			void	SetScale(const Vector3& s) { m_Scale = s; m_bNeedUpdate = true; }

			//Transforms
			virtual void	Move(const Vector3& d) { m_Position += d; m_bNeedUpdate = true; }
			void	MoveX(const float d) { m_Position.x += d; m_bNeedUpdate = true; }
			void	MoveY(const float d) { m_Position.y += d; m_bNeedUpdate = true; }
			void	MoveZ(const float d) { m_Position.z += d; m_bNeedUpdate = true; }

			void	Rotate(const Vector3& d) { m_Rotation += d; m_bNeedUpdate = true; }
			void	RotateX(const float d) { m_Rotation.x += d; m_bNeedUpdate = true; }
			void	RotateY(const float d) { m_Rotation.y += d; m_bNeedUpdate = true; }
			void	RotateZ(const float d) { m_Rotation.z += d; m_bNeedUpdate = true; }


		protected:
			void	Update();

		protected:
			Matrix4		m_Matrix;
			Vector3		m_Position;
			Vector3		m_Rotation;
			Vector3		m_Scale;

			bool		m_bNeedUpdate;
		};
	}
}

#endif		//FOREST_GRAPHICS_OBJECT3D_H