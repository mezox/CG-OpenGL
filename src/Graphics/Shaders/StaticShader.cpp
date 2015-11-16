/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Static shader definition
*/

#include "StaticShader.h"

namespace Forest
{
	namespace Graphics
	{
		static const ustring VERTEX_SHADER_FILE		= U("simple_vs.glsl");
		static const ustring FRAGMENT_SHADER_FILE	= U("simple_fs.glsl");

		StaticShader::StaticShader() :
			Shader(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE)
		{
			GetAllUniformLocations();
		}


		StaticShader::~StaticShader()
		{
		}

		void StaticShader::BindLights(const vector<Light>& l) const
		{
			for (int i = 0; i < LIGHT_COUNT; i++)
			{
				if (i < l.size())
				{
					BindUniform(m_loc_LightPosition[i], l.at(i).Position());
					BindUniform(m_loc_LightColor[i], l.at(i).Color());
					BindUniform(m_loc_LightAttenuation[i], l.at(i).Attenuation());
				}
				else
				{
					BindUniform(m_loc_LightPosition[i], Vector3());
					BindUniform(m_loc_LightColor[i], Vector3());
					BindUniform(m_loc_LightAttenuation[i], Vector3(1.0f,0.0f,0.0f));
				}
			}
			
			BindUniform(m_loc_LightAmbientIntensity, 0.3f);
		}


		void StaticShader::GetAllUniformLocations()
		{
			m_loc_ModelMatrix		= GetUniformLocation("modelMatrix");
			m_loc_ViewMatrix		= GetUniformLocation("viewMatrix");
			m_loc_ProjectionMatrix	= GetUniformLocation("projectionMatrix");
			m_loc_CameraPosition	= GetUniformLocation("cameraPosition");

			m_loc_HasTransparency	= GetUniformLocation("hasTransparency");
			m_loc_HasTextures		= GetUniformLocation("hasTextures");
			m_loc_UseFakeLighting	= GetUniformLocation("useFakeLighting");
			m_loc_DiffuseTexture	= GetUniformLocation("diffuseTex");
			m_loc_AlphaTexture		= GetUniformLocation("alphaTex");

			m_loc_ShineDamper		= GetUniformLocation("shineDamper");
			m_loc_Reflectivity		= GetUniformLocation("reflectivity");
			
			for (int i = 0; i < LIGHT_COUNT; i++)
			{
				m_loc_LightPosition[i]		= GetUniformLocation(("lightPosition[" + to_string(i) + "]").c_str());
				m_loc_LightColor[i]			= GetUniformLocation(("lColor[" + to_string(i) + "]").c_str());
				m_loc_LightAttenuation[i]	= GetUniformLocation(("lAttenuation[" + to_string(i) + "]").c_str());
			}

			m_loc_LightAmbientIntensity = GetUniformLocation("lAmIntensity");
			m_loc_SkyColor = GetUniformLocation("skyColor");
		}
	}
}