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
#include "Light.h"

namespace Forest
{
	namespace Graphics
	{
		class StaticShader : public Shader
		{
		public:
			static const int LIGHT_COUNT = 25;

		public:
			StaticShader();
			~StaticShader();

			void BindModelMatrix(const Matrix4& m) const		{ BindUniform(m_loc_ModelMatrix, m); }
			void BindViewMatrix(const Matrix4& m) const			{ BindUniform(m_loc_ViewMatrix, m); }
			void BindProjectionMatrix(const Matrix4& m) const	{ BindUniform(m_loc_ProjectionMatrix, m); }
			void BindCameraPosition(const Vector3& p) const		{ BindUniform(m_loc_CameraPosition, p); }
			void BindHasTextures(bool has) const				{ BindUniform(m_loc_HasTextures, has); }
			void BindHasTransparency(bool has) const			{ BindUniform(m_loc_HasTransparency, has); }
			void BindUseFakeLighting(bool val) const			{ BindUniform(m_loc_UseFakeLighting, val); }
			void BindDiffuse() const							{ BindUniform(m_loc_DiffuseTexture, 0); }
			void BindAlpha() const								{ BindUniform(m_loc_AlphaTexture, 1); }
			void BindSpecularVariables(float sd, float r) const { BindUniform(m_loc_ShineDamper, sd); BindUniform(m_loc_Reflectivity, r);}
			void BindSkyColor(const Vector3& color) const		{ BindUniform(m_loc_SkyColor, color); }
			void BindLights(const vector<Light>& l) const;


		protected:
			virtual void GetAllUniformLocations() override;

		private:
			GLuint	m_loc_ModelMatrix;
			GLuint	m_loc_ViewMatrix;
			GLuint	m_loc_ProjectionMatrix;
			GLuint	m_loc_CameraPosition;

			GLuint	m_loc_LightPosition[LIGHT_COUNT];
			GLuint	m_loc_LightColor[LIGHT_COUNT];
			GLuint	m_loc_LightAttenuation[LIGHT_COUNT];
			GLuint	m_loc_LightAmbientIntensity;

			GLuint	m_loc_ShineDamper;
			GLuint	m_loc_Reflectivity;
			GLuint	m_loc_SkyColor;

			GLuint	m_loc_HasTextures;
			GLuint	m_loc_HasTransparency;
			GLuint	m_loc_UseFakeLighting;
			GLuint	m_loc_DiffuseTexture;
			GLuint	m_loc_AlphaTexture;
		};
	}
}

#endif	//FOREST_GRAPHICS_STATICSHADER_H
