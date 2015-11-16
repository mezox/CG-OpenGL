#ifndef FOREST_GRAPHICS_TERRAIN_H
#define FOREST_GRAPHICS_TERRAIN_H

#include "Texture.h"

namespace Forest
{
	namespace Graphics
	{
		class Terrain
		{
		public:
			static const unsigned int SIZE = 800;
			static const unsigned int MAX_HEIGHT = 40;
			static const unsigned int MAX_PIXEL_COLOR = 256 * 256 * 256;
			static const unsigned int VERTEX_COUNT = 128;

			static const ustring TEXTURES_DIR;

		public:
			Terrain(float gridX, float gridZ);
			~Terrain();

			//Getters
			float		X() const { return m_X; }
			float		Z() const { return m_Z; }
			Texture*	BGTex() const { return m_bgTexture; }
			Texture*	RTex() const { return m_rTexture; }
			Texture*	GTex() const { return m_gTexture; }
			Texture*	BTex() const { return m_bTexture; }
			Texture*	BlendMap() const { return m_BlendMap; }
			
			size_t		Vertices() const { return m_VerticesCnt; }
			size_t		Indices() const { return m_IndicesCnt; }
			GLuint		Vao() const { return m_Vao; }

		private:
			void GenerateTerrain();

		private:
			float		m_X;
			float		m_Z;

			size_t		m_VerticesCnt;
			size_t		m_IndicesCnt;
			
			Texture*	m_bgTexture;
			Texture*	m_rTexture;
			Texture*	m_gTexture;
			Texture*	m_bTexture;
			Texture*	m_BlendMap;

			GLuint	m_Vao;
			GLuint	m_PositionsVBO;
			GLuint	m_UVsVBO;
			GLuint	m_NormalsVBO;
			GLuint	m_IndicesVBO;
		};
	}
}

#endif	//FOREST_GRAPHICS_TERRAIN_H