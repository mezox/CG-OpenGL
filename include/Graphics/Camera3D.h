#ifndef FOREST_GRAPHICS_Camera3D_H
#define FOREST_GRAPHICS_Camera3D_H

#ifndef FOREST_MATH_MATHS_H
	#include "Maths.h"
#endif

#ifndef FOREST_GRAPHICS_OBJECT3D_H
	#include "Object3D.h"
#endif

namespace Forest
{
	namespace Graphics
	{
		using namespace Forest::Math;

		/// <summary>
		/// 3D Camera class, using projection view
		/// </summary>
		class Camera3D : public Object3D
		{
		public:
			static const Vector3 UP;
			static const Vector3 RIGHT;
			static const Vector3 FORWARD;
			static const float Camera3D::RUN_SPEED;
			static const float Camera3D::TURN_SPEED;

			enum class PROJECTION_TYPES
			{
				INVALID,
				PERSPECTIVE,
				ORTHOGRAPHIC,
				MAX_TYPES
			};

		public:
			Camera3D(uint16_t width, uint16_t height, const Vector3& position);
			~Camera3D() {}

			//Getters
			const float			NearPlane() const	{ return m_NearPlane; }
			const float			FarPlane() const	{ return m_FarPlane; }
			const float			Fov() const			{ return m_Fov; }
			const float			Pitch() const		{ return m_Rotation.x; }
			const float			Yaw() const			{ return m_Rotation.y; }
			const float			Roll() const		{ return m_Rotation.z; }
			const Vector3&		Forward() const		{ return m_zAxis; }
			const Vector3&		Right() const		{ return m_xAxis; }
			const Vector3&		Up() const			{ return m_yAxis; }
			const Matrix4&		Projection(const PROJECTION_TYPES& type);
			const Matrix4&		View();

			void				Update();
			void				CalcPitch(float mdy);
			void				CalcAngleAround(float mdx);
			void				Zoom(int wheel);

			//Types of camera	
			void				LookAt(const Vector3& target, const Vector3& up);
			void				FirstPerson();

		private:
			void		HandleInput();

		private:
			Matrix4		m_Projection;	//Perspective projection matrix
			Matrix4		m_ViewMatrix;	//Camera's view matrix

			float		m_Fov;			//Field of View !in degrees!
			float		m_NearPlane;
			float		m_FarPlane;

			float		m_RunSpeed;
			float		m_TurnSpeed;

			Vector3		m_xAxis;	//Current view x axis
			Vector3		m_yAxis;	//Current view y axis
			Vector3		m_zAxis;	//Current view z axis
			Vector3		m_ViewDir;	//View direction of camera

			float		m_DistFromPlayer;
			float		m_AngleAroundPlayer;

			bool		m_bUpdateViewMatrix;
			bool		m_bUpdateProjMatrix;
		};
	}
}

#endif	//FOREST_GRAPHICS_Camera3D_H