#ifndef FOREST_GRAPHICS_TEXTURE_H
#define FOREST_GRAPHICS_TEXTURE_H

#ifndef FOREST_DEFINES_STRINGS_H
	#include "Strings.h"
#endif

#ifndef __glew_h__
	#include <GL/glew.h>
#endif

namespace Forest
{
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture();
			Texture(GLenum tTarget);

			bool Load(const ustring& file);
			void Bind(GLenum tUnit);
			void Unbind();

		private:
			GLuint	m_TextureID;
			GLenum	m_TextureTarget;
			GLenum	m_TextureType;
		};
	}
}

#endif	//FOREST_GRAPHICS_TEXTURE_H
