#pragma once

#include "StaticShader.h"
#include <unordered_map>
#include "Entity.h"
#include "Camera3D.h"

namespace Forest
{
	namespace Graphics
	{
		class Renderer
		{
			using EntityMap = std::unordered_map<shared_ptr<OBJModel>, std::vector<Entity>>;

		public:
			Renderer(Camera3D& camera);
			~Renderer();

			void ProcessEntity(Entity& entity);
			void Render(Camera3D& camera);

			const vector<Light>&	Lights() const { return m_Lights; }

		private:
			void PrepareScene();

			void PrepareModel(const shared_ptr<OBJModel>& model);
			void PrepareInstance(Entity& entity);
			void UnbindModel();

		private:
			Vector3			m_ClearColor;

			StaticShader	m_Shader;
			EntityMap		m_Entities;
			vector<Light>	m_Lights;
		};
	}
}