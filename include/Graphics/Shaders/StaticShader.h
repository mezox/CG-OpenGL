/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Static shader class declaration,
*				this shader serves as main shader for
*				rendering world entities
*/


#ifndef FOREST_GRAPHICS_STATICSHADER_H
#define FOREST_GRAPHICS_STATICSHADER_H

#include "Shader.h"

namespace Forest
{
	namespace Graphics
	{
		class StaticShader : public Shader
		{
		public:
			StaticShader();
			~StaticShader();

			void BindModelMatrix(const Matrix4& m) const		{ BindUniform(m_loc_ModelMatrix, m); }
			void BindViewMatrix(const Matrix4& m) const			{ BindUniform(m_loc_ViewMatrix, m); }
			void BindProjectionMatrix(const Matrix4& m) const	{ BindUniform(m_loc_ProjectionMatrix, m); }
			void BindCameraPosition(const Vector3& p) const		{ BindUniform(m_loc_CameraPosition, p); }
			void BindTextures() const							{ BindUniform(m_loc_DiffuseTexture, 0); BindUniform(m_loc_AlphaTexture, 1); }

		protected:
			virtual void GetAllUniformLocations() override;

		private:
			GLuint	m_loc_ModelMatrix;
			GLuint	m_loc_ViewMatrix;
			GLuint	m_loc_ProjectionMatrix;
			GLuint	m_loc_CameraPosition;

			GLuint	m_loc_DiffuseTexture;
			GLuint	m_loc_AlphaTexture;
		};
	}
}

#endif	//FOREST_GRAPHICS_STATICSHADER_H
