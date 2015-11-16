#include "Camera3D.h"
#include <SDL.h>

#ifndef FOREST_CORE_WINDOW_H
	#include <Window.h>
#endif

#include "Keyboard.h"

namespace Forest
{
	namespace Graphics
	{
		const Vector3 Camera3D::FORWARD = Vector3(0.0f, 0.0f, -1.0f);
		const Vector3 Camera3D::UP = Vector3(0.0f, 1.0f, 0.0f);
		const Vector3 Camera3D::RIGHT = Vector3(1.0f, 0.0f, 0.0f);
		const float Camera3D::RUN_SPEED = 20.0f;
		const float Camera3D::TURN_SPEED = 90.0f;

		//must be less than 90 to avoid gimbal lock
		static const float MaxVerticalAngle = 89.0f;

		Camera3D::Camera3D(uint16_t width, uint16_t height, const Vector3& position) :
			Object3D(position),
			m_Fov(67.0f),
			m_NearPlane(1.0f),
			m_FarPlane(1000.0f),
			m_RunSpeed(0.0f),
			m_TurnSpeed(0.0f),
			m_DistFromPlayer(10.0f),
			m_AngleAroundPlayer(0.0f),

			m_bUpdateViewMatrix(false),
			m_bUpdateProjMatrix(false)
		{
			m_xAxis = Vector3(1.0f, 0.0f, 0.0f);
			m_yAxis = Vector3(0.0f, 1.0f, 0.0f);
			m_zAxis = Vector3(0.0f, 0.0f, 1.0f);
			m_ViewDir = Vector3(0.0f, 0.0f, -1.0f);
			m_ViewMatrix = Matrix4::Identity();

			Object3D::m_Rotation = Vector3(-20.0f, -30.0f, 0.0f);

			m_Projection = Matrix4::Perspective(m_Fov, static_cast<float>(width) / static_cast<float>(height), m_NearPlane, m_FarPlane);
		}

		void Camera3D::Update()
		{
			HandleInput();

			float distance = m_RunSpeed * Core::Window::DeltaTime();
			Vector3 displacement = Forward() * distance;

			Object3D::Move(displacement);

			m_bUpdateViewMatrix = false;
		}

		/// <summary>
		/// Computes projection matrix.
		/// </summary>
		/// <returns>Projection matrix</returns>
		const Matrix4& Camera3D::Projection(const PROJECTION_TYPES& type)
		{
			//if (m_bUpdateProjMatrix)
			//{
				if (type == PROJECTION_TYPES::PERSPECTIVE)
					m_Projection = Matrix4::Perspective(m_Fov, static_cast<float>(1280) / static_cast<float>(720), m_NearPlane, m_FarPlane);
				else if (type == PROJECTION_TYPES::ORTHOGRAPHIC)
					m_Projection = Matrix4::Orthographic(-640.0f, 640.0f, -360.0f, 360.0f, 1.0f, -1000.0f);

				//m_bUpdateProjMatrix = false;
			//}

			return m_Projection;
		}

		/// <summary>
		/// Computes view matrix.
		/// </summary>
		/// <returns></returns>
		const Matrix4& Camera3D::View()
		{
			//LookAt(Vector3(0.0f,0.0f,-1.0f), Vector3(0.0f, 1.0f, 0.0f));
			//if (m_bUpdateViewMatrix)

			FirstPerson();

			return m_ViewMatrix;
		}


		void Camera3D::CalcPitch(float mdy)
		{
			float pitchChange = mdy * 0.3f;

			if (m_Rotation.x < 89.0f)
				m_Rotation.x += pitchChange;
			else if (pitchChange > 0.0f && m_Rotation.x >= 89.0f)
				m_Rotation.x -= pitchChange;

			m_bUpdateViewMatrix = true;
		}


		void Camera3D::CalcAngleAround(float mdx)
		{
			m_Rotation.y += (mdx * 0.4f);
			m_bUpdateViewMatrix = true;
		}


		void Camera3D::Zoom(int wheel)
		{
			float zoomLevel = wheel * 0.5f;

			/*if (m_DistFromPlayer > 5.5f)
				m_DistFromPlayer -= zoomLevel;
			else if (m_DistFromPlayer > 3.0f && m_DistFromPlayer <= 5.5f && zoomLevel < 0.0f)
				m_DistFromPlayer -= zoomLevel;*/

			m_Fov += zoomLevel;

			m_bUpdateProjMatrix = true;
		}


		void Camera3D::LookAt(const Vector3& target, const Vector3& up)
		{
			//forward vector
			m_zAxis = m_Position - target;
			m_zAxis.Normalize();

			//right vector
			m_xAxis = up.Cross(m_zAxis);
			m_xAxis.Normalize();

			//up vector
			m_yAxis = m_zAxis.Cross(m_xAxis);

			m_ViewDir = -m_zAxis;

			/*Construct the view matrix, column order

			col1			 col2			 col3			 col4
			[	xAxis.x			xAxis.y			xAxis.z			0.0f	]
			[	yAxis.x			yAxis.y			yAxis.z			0.0f	]
			[	zAcis.x			zAcis.y			zAcis.z			0.0f	]
			[	0.0f			0.0f			0.0f			1.0f	]

			Then we should multiply this matrix with translation matrix

			col1		col2		col3		col4
			[	1.0f		0.0f		0.0f		-pos.x	]
			[	0.0f		1.0f		0.0f		-pos.y	]
			[	0.0f		0.0f		1.0f		-pos.z	]
			[	0.0f		0.0f		0.0f		1.0f	]

			But we can optimize this multiplication by direct computing of
			translation part of the matrix:

			col1			 col2			 col3			 col4
			[	xAxis.x			xAxis.y			xAxis.z			-Dot(xAxis,pos)	]
			[	yAxis.x			yAxis.y			yAxis.z			-Dot(yAxis,pos)	]
			[	zAcis.x			zAcis.y			zAcis.z			-Dot(zAxis,pos)	]
			[	0.0f			0.0f			0.0f			1.0f			]


			*/
			m_ViewMatrix.c1.x = m_xAxis.x;
			m_ViewMatrix.c2.x = m_xAxis.y;
			m_ViewMatrix.c3.x = m_xAxis.z;
			m_ViewMatrix.c4.x = -m_xAxis.Dot(m_Position);

			m_ViewMatrix.c1.y = m_yAxis.x;
			m_ViewMatrix.c2.y = m_yAxis.y;
			m_ViewMatrix.c3.y = m_yAxis.z;
			m_ViewMatrix.c4.y = -m_yAxis.Dot(m_Position);

			m_ViewMatrix.c1.z = m_zAxis.x;
			m_ViewMatrix.c2.z = m_zAxis.y;
			m_ViewMatrix.c3.z = m_zAxis.z;
			m_ViewMatrix.c4.z = -m_zAxis.Dot(m_Position);
		}


		/// <summary>
		/// Computes first person - like camera view matrix
		/// </summary>
		/// <returns>View matrix</returns>
		void Camera3D::FirstPerson()
		{
			float rPitch = toRadians(m_Rotation.x);
			float rYaw = toRadians(m_Rotation.y);

			float sinPitch = sinf(rPitch);
			float cosPitch = cosf(rPitch);

			float sinYaw = sinf(rYaw);
			float cosYaw = cosf(rYaw);

			m_xAxis = Vector3(cosYaw, 0.0f, -sinYaw);
			m_yAxis = Vector3(sinYaw * sinPitch, cosPitch, cosYaw * sinPitch);
			m_zAxis = Vector3(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

			m_ViewMatrix.c1.x = m_xAxis.x;
			m_ViewMatrix.c2.x = m_xAxis.y;
			m_ViewMatrix.c3.x = m_xAxis.z;
			m_ViewMatrix.c4.x = -m_xAxis.Dot(m_Position);

			m_ViewMatrix.c1.y = m_yAxis.x;
			m_ViewMatrix.c2.y = m_yAxis.y;
			m_ViewMatrix.c3.y = m_yAxis.z;
			m_ViewMatrix.c4.y = -m_yAxis.Dot(m_Position);

			m_ViewMatrix.c1.z = m_zAxis.x;
			m_ViewMatrix.c2.z = m_zAxis.y;
			m_ViewMatrix.c3.z = m_zAxis.z;
			m_ViewMatrix.c4.z = -m_zAxis.Dot(m_Position);
		}


		void Camera3D::HandleInput()
		{
			const uint8_t* state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_W])
			{
				m_RunSpeed = -RUN_SPEED;
				m_bUpdateViewMatrix = true;
			}
			else if (state[SDL_SCANCODE_S])
			{
				m_RunSpeed = RUN_SPEED;
				m_bUpdateViewMatrix = true;
			}
			else
				m_RunSpeed = 0.0f;

			if (state[SDL_SCANCODE_A])
			{
				m_TurnSpeed = TURN_SPEED;
				m_bUpdateViewMatrix = true;
			}
			else if (state[SDL_SCANCODE_D])
			{
				m_TurnSpeed = -TURN_SPEED;
				m_bUpdateViewMatrix = true;
			}
			else
				m_TurnSpeed = 0.0f;
		}
	}
}