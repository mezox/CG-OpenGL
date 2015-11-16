#include "Terrain.h"

#include <vector>

namespace Forest
{
	namespace Graphics
	{
		const ustring Terrain::TEXTURES_DIR = U("Textures/");

		Terrain::Terrain(float gridX, float gridZ) :
			m_X(gridX * (float)SIZE),
			m_Z(gridZ * (float)SIZE)
		{
			GenerateTerrain();
			
			m_bgTexture = new Texture();
			m_rTexture = new Texture();
			m_gTexture = new Texture();
			m_bTexture = new Texture();
			m_BlendMap = new Texture();

			m_bgTexture->Load(TEXTURES_DIR + U("bgTexture.jpg"));
			m_rTexture->Load(TEXTURES_DIR + U("rTexture.jpg"));
			m_gTexture->Load(TEXTURES_DIR + U("bTexture.jpg"));
			m_bTexture->Load(TEXTURES_DIR + U("gTexture.jpg"));
			m_BlendMap->Load(TEXTURES_DIR + U("blendMap.jpg"));
		}

		Terrain::~Terrain()
		{
			/*glDeleteBuffers(1, &m_PositionsVBO);
			glDeleteBuffers(1, &m_UVsVBO);
			glDeleteBuffers(1, &m_NormalsVBO);
			glDeleteBuffers(1, &m_IndicesVBO);
			glDeleteVertexArrays(1, &m_Vao);

			m_bgTexture->Unbind();
			delete m_bgTexture;
			m_bgTexture = nullptr;
			
			m_rTexture->Unbind();
			delete m_rTexture;
			m_rTexture = nullptr;

			m_gTexture->Unbind();
			delete m_gTexture;
			m_gTexture = nullptr;

			m_bTexture->Unbind();
			delete m_bTexture;
			m_bTexture = nullptr;

			m_BlendMap->Unbind();
			delete m_BlendMap;
			m_BlendMap = nullptr;*/
		}


		void Terrain::GenerateTerrain()
		{
			const int count = VERTEX_COUNT * VERTEX_COUNT;

			float vertices[count * 3];
			float normals[count * 3];
			float textureCoords[count * 2];
			int indices[6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)];

			int vertexPointer = 0;

			for (int i = 0;i<VERTEX_COUNT;i++)
			{
				for (int j = 0;j<VERTEX_COUNT;j++)
				{
					vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
					vertices[vertexPointer * 3 + 1] = 0.0f;
					vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
					normals[vertexPointer * 3] = 0;
					normals[vertexPointer * 3 + 1] = 1.0f;
					normals[vertexPointer * 3 + 2] = 0.0f;
					textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
					textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
					vertexPointer++;
				}
			}

			int pointer = 0;

			for (int gz = 0; gz<VERTEX_COUNT - 1; gz++)
			{
				for (int gx = 0;gx<VERTEX_COUNT - 1;gx++)
				{
					int topLeft = (gz*VERTEX_COUNT) + gx;
					int topRight = topLeft + 1;
					int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
					int bottomRight = bottomLeft + 1;
					indices[pointer++] = topLeft;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = topRight;
					indices[pointer++] = topRight;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = bottomRight;
				}
			}

			m_VerticesCnt = count;
			m_IndicesCnt = pointer;

			std::vector<float> verticesVector;
			std::vector<float> normalsVector;
			std::vector<float> texcoordsVector;
			std::vector<uint32_t> indicesVector;

			for (int i = 0; i < count * 3; i++)
				verticesVector.push_back(vertices[i]);

			for (int i = 0; i < count * 3; i++)
				normalsVector.push_back(normals[i]);

			for (int i = 0; i < count * 2; i++)
				texcoordsVector.push_back(textureCoords[i]);

			for (int i = 0; i < pointer; i++)
				indicesVector.push_back(indices[i]);

			//Load data to GPU
			glGenVertexArrays(1, &m_Vao);
			glBindVertexArray(m_Vao);

			glGenBuffers(1, &m_PositionsVBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_PositionsVBO);
			glBufferData(GL_ARRAY_BUFFER, count * 3 * sizeof(float), &verticesVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &m_UVsVBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_UVsVBO);
			glBufferData(GL_ARRAY_BUFFER, count * 2 * sizeof(float), &texcoordsVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &m_NormalsVBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_NormalsVBO);
			glBufferData(GL_ARRAY_BUFFER, count * 3 * sizeof(float), &normalsVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &m_IndicesVBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, pointer * sizeof(uint32_t), &indicesVector[0], GL_STATIC_DRAW);
		}
	}
}