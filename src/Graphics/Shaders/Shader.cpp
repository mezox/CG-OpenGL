/*
*   Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Shader program class definition
*/


#include "Shader.h"

#ifndef _FSTREAM_
#	include <fstream>
#endif

#ifndef FOREST_DEFINES_STRINGS_H
#	include "Strings.h"
#endif

#ifndef FOREST_DEFINES_STRINGSTREAM_H
#	include "StringStream.h"
#endif

namespace Forest
{
	namespace Graphics
	{
		Shader::Shader(const ustring & vs, const ustring & fs)
		{
			m_VertexShaderID = LoadShader(vs, GL_VERTEX_SHADER);
			m_FragmentShaderID = LoadShader(fs, GL_FRAGMENT_SHADER);

			//Create new shader program
			m_ProgramID = glCreateProgram();

			//Attach vertex and fragment shaders to the shader program
			glAttachShader(m_ProgramID, m_VertexShaderID);
			glAttachShader(m_ProgramID, m_FragmentShaderID);

			//Link and validate program
			glLinkProgram(m_ProgramID);
			glValidateProgram(m_ProgramID);
		}

		Shader::~Shader()
		{
			Unbind();

			//Detach vertex & fragment shader
			glDetachShader(m_ProgramID, m_VertexShaderID);
			glDetachShader(m_ProgramID, m_FragmentShaderID);

			//Delete vertex & fragment shader
			glDeleteShader(m_VertexShaderID);
			glDeleteShader(m_FragmentShaderID);

			//Delete program iteself
			glDeleteProgram(m_ProgramID);
		}

		void Shader::Bind() const
		{
			glUseProgram(m_ProgramID);
		}

		void Shader::Unbind() const
		{
			glUseProgram(0);
		}


		/// <summary>
		/// Loads the shader from source file.
		/// </summary>
		/// <param name="file">Path to the source file.</param>
		/// <param name="type">Type of shader (VERTEX/FRAGMENT SHADER).</param>
		/// <returns>Shader ID</returns>
		GLuint Shader::LoadShader(const ustring & file, GLuint type)
		{
			std::ifstream input;
			input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			std::string srcCode;

			try
			{
				input.open(file.c_str());
				srcCode.assign((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
			}
			catch (std::ifstream::failure e)
			{
				ucout << "Could not read shader file!\n";
			}

			GLuint sID = glCreateShader(type);
			const char * code = srcCode.c_str();

			glShaderSource(sID, 1, (const GLchar**)&code, NULL);
			glCompileShader(sID);

			ValidateCompile(sID);

			return sID;
		}

		/// <summary>
		/// Validates the compilation of shader program and prints errors.
		/// </summary>
		/// <param name="sID">ID of shader.</param>
		void Shader::ValidateCompile(GLuint sID)
		{
			GLint compiled;

			glGetShaderiv(sID, GL_COMPILE_STATUS, &compiled);

			if (!compiled)
			{
				GLsizei length;
				glGetShaderiv(sID, GL_INFO_LOG_LENGTH, &length);

				GLchar* log = new GLchar[length + 1];
				glGetShaderInfoLog(sID, length, &length, log);

				ucout << log << std::endl;

				delete[] log;

				glDeleteShader(sID);
			}
		}
	}
}