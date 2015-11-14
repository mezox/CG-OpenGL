/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Shader program class declaration
*/


#ifndef FOREST_GRAPHICS_SHADER_H
#define FOREST_GRAPHICS_SHADER_H

#include <GL/glew.h>
#include "Strings.h"

#ifndef FOREST_MATH_MATHS_H
	#include "Maths.h"
#endif

using namespace Forest::Math;

namespace Forest
{
	namespace Graphics
	{
		class Shader
		{
		public:
			static GLuint	LoadShader(const ustring& file, GLuint type);
			static void		ValidateCompile(GLuint sID);

		public:
			Shader(const ustring& vs, const ustring& fs);
			virtual ~Shader();

			void	Bind()	const;
			void	Unbind() const;

		protected:
			virtual void	GetAllUniformLocations() = 0;
			GLuint			GetUniformLocation(const GLchar* name)							{ return glGetUniformLocation(m_ProgramID, name); }

			void	BindUniform(const GLuint location, int32_t i) const						{ glUniform1i(location, i); }
			void	BindUniform(const GLuint location, float f)	const						{ glUniform1f(location, f); }
			void	BindUniform(const GLuint location, float f1, float f2) const			{ glUniform2f(location, f1, f2); }
			void	BindUniform(const GLuint location, float f1, float f2, float f3) const	{ glUniform3f(location, f1, f2, f3); }
			void	BindUniform(const GLuint location, const Vector3& v) const				{ glUniform3f(location, v.x, v.y, v.z); }
			void	BindUniform(const GLuint location, const Vector4& v) const				{ glUniform4f(location, v.x, v.y, v.z, v.w); }
			void	BindUniform(const GLuint location, const Matrix4& m) const				{ glUniformMatrix4fv(location, 1, GL_FALSE, &m.c1.x); }
			void	BindUniform(const GLuint location, bool b) const						{ glUniform1i(location, b ? 1 : 0); }

		private:
			GLuint		m_ProgramID;
			GLuint		m_VertexShaderID;
			GLuint		m_FragmentShaderID;
		};
	}
}


#endif	//FOREST_GRAPHICS_SHADER_H
