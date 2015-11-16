
#include "Renderer.h"

#include <random>

namespace Forest
{
	namespace Graphics
	{
		Renderer::Renderer(Camera3D& camera) :
			m_ClearColor(Vector3(0.0f,0.0f,0.0f))
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			//Set clear color
			glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, 1.0f);

			PrepareScene();

			//Bind uniforms that wont change during application run loop
			m_Shader.Bind();
				m_Shader.BindProjectionMatrix(camera.Projection(Camera3D::PROJECTION_TYPES::PERSPECTIVE));
				m_Shader.BindLights(m_Lights);
				m_Shader.BindSkyColor(m_ClearColor);
			m_Shader.Unbind();

		}

		Renderer::~Renderer()
		{
		}

		void Renderer::PrepareScene()
		{
			shared_ptr<OBJModel> tree = make_shared<OBJModel>(U("hightree"), true, true);
			shared_ptr<OBJModel> palm = make_shared<OBJModel>(U("palm"), true, true);
			shared_ptr<OBJModel> rock = make_shared<OBJModel>(U("rock"), true, false);
			shared_ptr<OBJModel> lamp = make_shared<OBJModel>(U("lamp"), true, false);
			shared_ptr<OBJModel> bush = make_shared<OBJModel>(U("bush"), true, true);
			shared_ptr<OBJModel> smallplant = make_shared<OBJModel>(U("smallplant"), true, true);

			//Load meshes
			tree->LoadBinary();
			palm->LoadBinary();
			rock->LoadBinary();
			lamp->LoadBinary();
			bush->LoadBinary();
			smallplant->LoadBinary();

			//Set reflectivity properties if needed
			lamp->SetShineDamper(5.0f);
			lamp->SetReflectivity(1.0f);
			rock->SetReflectivity(0.5f);
			rock->SetShineDamper(10.0f);

			//Change normals if needed
			lamp->SetUseFakeLighting(true);
			bush->SetUseFakeLighting(true);
			smallplant->SetUseFakeLighting(true);

			std::random_device rd;
			std::mt19937 mt(rd());

			std::uniform_real_distribution<float> pRG(0.0f, 150.0f);		//Position generator
			std::uniform_real_distribution<float> sRG(0.5f, 2.0f);			//Scale generator
			std::uniform_real_distribution<float> rzRG(-5.0f, 5.0f);		//Rotation around z axis
			std::uniform_real_distribution<float> ryRG(0.0f, 360.0f);		//Rotation around y axis
			std::uniform_real_distribution<float> rsRG(0.5f, 1.0f);

			std::vector<Entity> hightrees;
			std::vector<Entity> palms;
			std::vector<Entity> rocks;
			std::vector<Entity> lamps;
			std::vector<Entity> bushes;
			std::vector<Entity> smallplants;

			//Generate trees
			for (int i = 0; i < 50; i++)
			{
				Entity e = Entity(
					tree,
					Vector3(pRG(mt), 0.0f, (pRG(mt) * (-1))),	//generate position
					Vector3(0.0f, ryRG(mt), rzRG(mt)),			//generate rotation
					Vector3(sRG(mt)));							//generate scale

				hightrees.push_back(e);
			}
			tree.reset();

			//Generate palms
			for (int i = 0; i < 100; i++)
			{
				Entity e = Entity(
					palm, 
					Vector3(pRG(mt), 0.0f, (pRG(mt) * (-1))),	//generate position
					Vector3(0.0f, ryRG(mt), rzRG(mt)),			//generate rotation
					Vector3(sRG(mt)));							//generate scale

				palms.push_back(e);
			}
			palm.reset();

			//Generate rocks
			for (int i = 0; i < 24; i++)
			{
				float x = pRG(mt);
				float z = pRG(mt) * -1;

				Entity e = Entity(
					rock,
					Vector3(pRG(mt), 0.0f, (pRG(mt) * (-1))),	//generate position
					Vector3(0.0f, ryRG(mt), rzRG(mt)),			//generate rotation
					Vector3(rsRG(mt)));							//generate scale

				rocks.push_back(e);
			}
			rock.reset();

			//Generate lamps
			for (int i = 0; i < 24; i++)
			{
				float x = pRG(mt);
				float z = pRG(mt) * -1.0f;

				Entity e = Entity(
					lamp,
					Vector3(pRG(mt), 0.0f, (pRG(mt) * (-1))),	//generate position
					Vector3(0.0f, ryRG(mt), rzRG(mt)),			//generate rotation
					Vector3(1.0f));								//don't scale

				lamps.push_back(e);
			}

			//Generate bushes
			for (int i = 0; i < 30; i++)
			{
				float x = pRG(mt);
				float z = pRG(mt) * -1.0f;

				Entity e = Entity(
					bush,
					Vector3(pRG(mt), 0.0f, (pRG(mt) * (-1))),	//generate position
					Vector3(0.0f, ryRG(mt), rzRG(mt)),			//generate rotation
					Vector3(rsRG(mt)));								//don't scale

				bushes.push_back(e);
			}

			//Generate plants
			for (int i = 0; i < 30; i++)
			{
				float x = pRG(mt);
				float z = pRG(mt) * -1.0f;

				Entity e = Entity(
					smallplant,
					Vector3(pRG(mt), 0.0f, (pRG(mt) * (-1))),	//generate position
					Vector3(0.0f, ryRG(mt), rzRG(mt)),			//generate rotation
					Vector3(sRG(mt)));							//generate scale

				smallplants.push_back(e);
			}


			//Setup lights
			//-----------------------------------------------------------------------
			Vector3 pLightAtt = Vector3(1.0f, 0.001f, 0.002f);
			
			for (int i = 0; i < StaticShader::LIGHT_COUNT - 1; i++)
			{
				Entity lampTmp = lamps.at(i);
				Vector3 color;

				if (i % 2 == 0 && i < 25)
					color = Vector3(1.0f, 0.0f, 0.0f);	//0,2,4,6,8,10,...
				else if (i % 3 == 0 && i != 0)
					color = Vector3(0.0f, 0.0f, 1.0f);	//3,6,9,....
				else if (i == 1 || i == 5 || i == 7 || i == 11 || i == 13 || i == 17)
					color = Vector3(1.0f, 1.0f, 0.0f);

				m_Lights.push_back(Light(Vector3(lampTmp.Position().x, lampTmp.Position().y + 14.0f, lampTmp.Position().z), color, pLightAtt, 0.02f));
			}

			//Add directional light
			m_Lights.push_back(Light(Vector3(0.0f, 120.0f, 0.0f), Vector3(0.4f), Vector3(1.0f, 0.0f, 0.0f), 0.05f));
			//-----------------------------------------------------------------------


			for (auto& entity : hightrees)
				ProcessEntity(entity);

			for (auto& entity : palms)
				ProcessEntity(entity);

			for (auto& entity : rocks)
				ProcessEntity(entity);

			for (auto& entity : lamps)
				ProcessEntity(entity);

			for (auto& entity : bushes)
				ProcessEntity(entity);

			for (auto& entity : smallplants)
				ProcessEntity(entity);

			hightrees.clear();
			hightrees.shrink_to_fit();
			palms.clear();
			palms.shrink_to_fit();
			rocks.clear();
			rocks.shrink_to_fit();
			lamps.clear();
			lamps.shrink_to_fit();
			bushes.clear();
			bushes.shrink_to_fit();
			smallplants.clear();
			smallplants.shrink_to_fit();
		}

		void Renderer::PrepareModel(const shared_ptr<OBJModel>& model)
		{
			glBindVertexArray(model->VAO());
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			bool bHasTex = model->HasTextures();
			bool bHasTransparency = model->HasTransparency();

			if (bHasTex)
			{
				m_Shader.BindDiffuse();
				model->Diffuse()->Bind(GL_TEXTURE0);
			}

			if (model->HasTransparency())
			{
				m_Shader.BindAlpha();
				model->Alpha()->Bind(GL_TEXTURE1);
				glDisable(GL_CULL_FACE);
			}

			m_Shader.BindUseFakeLighting(model->UseFakeLighting());
			m_Shader.BindSpecularVariables(model->ShineDamper(), model->Reflectivity());

			m_Shader.BindHasTextures(bHasTex);
			m_Shader.BindHasTransparency(bHasTransparency);
		}

		void Renderer::PrepareInstance(Entity& entity)
		{
			m_Shader.BindModelMatrix(entity.Matrix());
		}


		void Renderer::ProcessEntity(Entity& entity)
		{
			const shared_ptr<OBJModel>& model = entity.Model();
			EntityMap::iterator pair = m_Entities.find(model);

			if (pair == m_Entities.end() || pair->second.empty())
			{
				std::vector<Entity> newBatch;
				newBatch.push_back(entity);

				std::pair<shared_ptr<OBJModel>, std::vector<Entity>> newItem (model, newBatch);

				m_Entities.insert(newItem);
			}
			else
			{
				pair->second.push_back(entity);
			}
		}


		/// <summary>
		/// Unbinds the model. Re-enables backface culling (if transparent geometry was rendered)
		/// </summary>
		void Renderer::UnbindModel()
		{
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindVertexArray(0);
			
			glEnable(GL_CULL_FACE);
		}

		
		void Renderer::Render(Camera3D& camera)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_Shader.Bind();
				m_Shader.BindViewMatrix(camera.View());

				for (const auto& kv : m_Entities)
				{
					PrepareModel(kv.first);
				
					for (Entity entity : kv.second)
					{
						PrepareInstance(entity);						
						glDrawElements(GL_TRIANGLES, (GLsizei)entity.Model()->Indices(), GL_UNSIGNED_INT, 0);
					}

					UnbindModel();
				}

			m_Shader.Unbind();

			//m_Entities.clear();
		}
	}
}