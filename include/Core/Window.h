/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Window class (singleton) declaration
*/

#ifndef FOREST_CORE_WINDOW_H
#define FOREST_CORE_WINDOW_H

#include "INonCopy.h"
#include <SDL.h>

namespace Forest
{
	namespace Core
	{
		class Window : public INonCopy
		{
		public:
			static const uint16_t DEF_WINDOW_WIDTH = 1280;
			static const uint16_t DEF_WINDOW_HEIGHT = 720;

		public:
			Window();
			~Window();

		public:
			bool	IsRunning();
			void	Run();

			static float Time();
			static float DeltaTime() { return m_DeltaTime; }

		private:
			bool	Initialize();
			void	SwapBuffers();
			void	Destroy();

		private:
			SDL_Window*		m_Handle;
			SDL_GLContext	m_GLContext;

			bool	m_bRunning;
			bool	m_bFullscreen;
			bool	m_bCursorHidden;
			static float	m_DeltaTime;
		};
	}
}

#endif
