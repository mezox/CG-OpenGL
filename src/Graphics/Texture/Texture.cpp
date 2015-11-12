
#include "Texture.h"
#include "stbi_image.h"

#ifndef FOREST_DEFINES_IOSTREAM_H
	#include "Iostream.h"
#endif

namespace Forest
{
	namespace Graphics
	{
		Texture::Texture() :
			m_TextureTarget(GL_TEXTURE_2D)
		{
		}

		Texture::Texture(GLenum tTarget)
		{
			m_TextureTarget = tTarget;
		}

		/// <summary>
		/// Loads the texture from file using stb_image.c library.
		/// </summary>
		/// <returns>TRUE on success.</returns>
		bool Texture::Load(const ustring& file)
		{
			int x, y, n;
			int force_channels = 4;

			unsigned char* image_data = NULL;

			try
			{
				image_data = stbi_load(UStringToStd(file).c_str(), &x, &y, &n, force_channels);
			}
			catch (std::exception)
			{
				ucout << U("ERROR: could not load") << file << U("\n");
			}

			glGenTextures(1, &m_TextureID);
			glBindTexture(m_TextureTarget, m_TextureID);

			glTexImage2D(m_TextureTarget, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

			//generate mipmap
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameterf(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
			glBindTexture(m_TextureTarget, m_TextureID);

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