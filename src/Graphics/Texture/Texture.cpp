/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Texture class definition, loading textures
*				using stbi_image.c lib
*/


#include "Texture.h"
#include "stbi_image.h"

#ifndef FOREST_DEFINES_IOSTREAM_H
	#include "Iostream.h"
#endif

namespace Forest
{
	namespace Graphics
	{
		Texture::~Texture()
		{
			glDeleteTextures(1, &m_TextureID);
		}


		/// <summary>
		/// Loads the texture from file using stb_image.c library.
		/// </summary>
		/// <returns>TRUE on success.</returns>
		bool Texture::Load(const ustring& file)
		{
			int x, y, n;
			int force_channels = 4;

			unsigned char* image_data = nullptr;

			try
			{
				image_data = stbi_load(UStringToStd(file).c_str(), &x, &y, &n, force_channels);
			}
			catch (std::exception)
			{
				ucout << U("ERROR: could not load") << file << U("\n");
			}

			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_BGRA, GL_UNSIGNED_BYTE, image_data);

			//OpenGL 4.2+
			//glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, x, y);
			//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, x, y, GL_BGRA, GL_UNSIGNED_BYTE, image_data);

			//generate mipmap
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//unbind texture
			glBindTexture(GL_TEXTURE_2D, 0);

			//free resources
			free(image_data);

			return true;
		}

		/// <summary>
		/// Binds texture to specified texture unit.
		/// </summary>
		/// <param name="TextureUnit">texture unit.</param>
		void Texture::Bind(GLenum tUnit)
		{
			glActiveTexture(tUnit);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			m_TextureTarget = tUnit;
		}


		/// <summary>
		/// Unbinds this texture.
		/// </summary>
		void Texture::Unbind()
		{
			glActiveTexture(m_TextureTarget);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}