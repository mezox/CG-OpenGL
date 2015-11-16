#ifndef FOREST_TERRAINSHADER_H
#define FOREST_TERRAINSHADER_H

#include "Shader.h"
#include "Light.h"

namespace Forest
{
	namespace Graphics
	{
		class TerrainShader : public Shader
		{
		public:
			static const int LIGHT_COUNT = 25;

		public:
			TerrainShader();
			~TerrainShader();

			void BindModelMatrix(const Matrix4& m) const		{ BindUniform(m_loc_ModelMatrix, m); }
			void BindViewMatrix(const Matrix4& m) const			{ BindUniform(m_loc_ViewMatrix, m); }
			void BindProjectionMatrix(const Matrix4& m) const	{ BindUniform(m_loc_ProjectionMatrix, m); }
			void BindCameraPosition(const Vector3& p) const		{ BindUniform(m_loc_CameraPosition, p); }
			void BindSkyColor(Vector3& c) const					{ BindUniform(m_loc_SkyColor, c); }
			void BindSpecularVariables(float sd, float r) const { BindUniform(m_loc_ShineDamper, sd); BindUniform(m_loc_Reflectivity, r); }
			void BindLights(const vector<Light>& l) const;

			void BindTextures() const
			{
				BindUniform(m_loc_tex_bgTexture, 0);
				BindUniform(m_loc_tex_rTexture, 1);
				BindUniform(m_loc_tex_gTexture, 2);
				BindUniform(m_loc_tex_bTexture, 3);
				BindUniform(m_loc_tex_blendmap, 4);
			}

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

			//Texture lodactions
			GLuint m_loc_tex_bgTexture;
			GLuint m_loc_tex_rTexture;
			GLuint m_loc_tex_gTexture;
			GLuint m_loc_tex_bTexture;
			GLuint m_loc_tex_blendmap;
		};
	}
}

#endif	//FOREST_TERRAINSHADER_H
