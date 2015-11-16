#ifndef FOREST_GRAPHICS_TERRAINRENDERER_H
#define FOREST_GRAPHICS_TERRAINRENDERER_H

#include "Camera3D.h"
#include "TerrainShader.h"
#include "Terrain.h"

namespace Forest
{
	namespace Graphics
	{
		class TerrainRenderer
		{
		public:
			TerrainRenderer(Camera3D& camera, const vector<Light>& lights);
			~TerrainRenderer() {}

			void Init(const Terrain& t);
			void Render(const Terrain& t, Camera3D& camera);
			void Unbind();

		private:
			TerrainShader m_Shader;
		};
	}
}

#endif	//FOREST_GRAPHICS_TERRAINRENDERER_H
