#include "TerrainRenderer.h"

namespace Forest
{
	namespace Graphics
	{
		TerrainRenderer::TerrainRenderer(Camera3D& camera, const vector<Light>& lights)
		{
			m_Shader.Bind();
				m_Shader.BindProjectionMatrix(camera.Projection(Camera3D::PROJECTION_TYPES::PERSPECTIVE));
				m_Shader.BindTextures();
				m_Shader.BindLights(lights);
			m_Shader.Unbind();
			
			//glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
		}

		void TerrainRenderer::Init(const Terrain& t)
		{
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBindVertexArray(t.Vao());
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			m_Shader.BindSpecularVariables(5.0f, 0.0f);
		}

		void TerrainRenderer::Render(const Terrain& t, Camera3D& camera)
		{
			m_Shader.Bind();
				Init(t);

				Matrix4 model = Matrix4::MakeTranslation(Vector3(t.X(), 0, t.Z()));
				m_Shader.BindModelMatrix(model);
				m_Shader.BindViewMatrix(camera.View());
				m_Shader.BindCameraPosition(camera.Position());

				t.BGTex()->Bind(GL_TEXTURE0);
				t.RTex()->Bind(GL_TEXTURE1);
				t.GTex()->Bind(GL_TEXTURE2);
				t.BTex()->Bind(GL_TEXTURE3);
				t.BlendMap()->Bind(GL_TEXTURE4);

				//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDrawElements(GL_TRIANGLES, (GLsizei)t.Indices(), GL_UNSIGNED_INT, 0);
				//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				Unbind();

			m_Shader.Unbind();
		}


		void TerrainRenderer::Unbind()
		{
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindVertexArray(0);
		}
	}
}
