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


		void StaticShader::GetAllUniformLocations()
		{
			m_loc_ModelMatrix = GetUniformLocation("modelMatrix");
			m_loc_ViewMatrix = GetUniformLocation("viewMatrix");
			m_loc_ProjectionMatrix = GetUniformLocation("projectionMatrix");
			m_loc_CameraPosition = GetUniformLocation("cameraPosition");

			m_loc_DiffuseTexture = GetUniformLocation("diffuseTex");
			m_loc_AlphaTexture = GetUniformLocation("alphaTex");
		}
	}
}