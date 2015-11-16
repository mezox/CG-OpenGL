#ifndef FOREST_GRAPHICS_OBJMODEL_H
#define FOREST_GRAPHICS_OBJMODEL_H

#include <GL/glew.h>

#ifndef _VECTOR_
#	include <vector>
#endif

#ifndef FOREST_MATH_MATHS_H
#	include "Maths.h"
#endif

#ifndef FOREST_DEFINES_STRINGS_H
#	include "Strings.h"
#endif

#ifndef FOREST_GRAPHICS_TEXTURE_H
#	include "Texture.h"
#endif

using namespace std;
using namespace Forest::Math;

#define BUFFER_SIZE 512

namespace Forest
{
	namespace Graphics
	{
		class OBJModel
		{
		public:
			static const ustring MODELS_DIR;
			static const ustring TEXTURES_DIR;

		public:
			OBJModel(const ustring& file, bool hasTextures, bool hasTransparency);
			~OBJModel();

			//Getters
			size_t	Vertices() const		{ return m_VerticesCnt; }
			size_t	Indices() const			{ return m_IndicesCnt; }
			float	ShineDamper() const		{ return m_ShineDamper; }
			float	Reflectivity() const	{ return m_Reflectivity; }
			bool	HasTransparency() const	{ return m_bHasTransparency; }
			bool	HasTextures() const		{ return m_bHasTextures; }
			bool	UseFakeLighting() const	{ return m_bUseFakeLighting; }
			GLuint		VAO()		const	{ return m_Vao; }
			Texture*	Diffuse()	const	{ return m_DiffuseTex; }
			Texture*	Alpha()		const	{ return m_AlphaTex; }

			//Setters
			void	SetShineDamper(float val)		{ m_ShineDamper = val; }
			void	SetReflectivity(float val)		{ m_Reflectivity = val; }
			void	SetUseFakeLighting(bool val)	{ m_bUseFakeLighting = val; }
			
			bool	LoadOBJ(bool bExportBinary = false);
			void	LoadBinary();

			
		private:
			void	SaveBinary();
			void	StoreDataInVBO();
			void	DeleteCPUData();

		private:
			ustring	m_FileName;

			size_t	m_VerticesCnt;
			size_t	m_IndicesCnt;
			float	m_ShineDamper;
			float	m_Reflectivity;

			bool	m_bHasTransparency;
			bool	m_bHasTextures;
			bool	m_bUseFakeLighting;

			//Textures
			Texture* m_DiffuseTex;
			Texture* m_AlphaTex;

			//Data on CPU, used just for reading/writing
			vector<Vector3>		m_Positions;
			vector<Vector2>		m_TexCoords_elem;
			vector<Vector3>		m_Normals_elem;
			vector<uint32_t>	m_Indices;
			
			// Data on GPU
			GLuint	m_PositionsVBO;
			GLuint	m_UVsVBO;
			GLuint	m_NormalsVBO;
			GLuint	m_IndicesVBO;
			GLuint	m_Vao;
		};
	}
}
#endif
