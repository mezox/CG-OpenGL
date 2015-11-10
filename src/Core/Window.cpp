/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Window class (singleton) declaration
*/

#include "Window.h"

#include <glew.h>
#include <iostream>

namespace Forest
{
	namespace Core
	{
		Window::Window() :
			INonCopy(),
			m_bRunning(false),
			m_bFullscreen(false),
			m_bCursorHidden(false)
		{
			Initialize();
			glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
		}


		Window::~Window()
		{
			Destroy();

			m_Handle = nullptr;
			m_GLContext = nullptr;
		}


		bool Window::IsRunning()
		{
			return m_bRunning;
		}


		void Window::Run()
		{
			m_bRunning = true;

			//Main Game loop
			while (m_bRunning)
			{
				glClear(GL_COLOR_BUFFER_BIT);

				SDL_Event event;

				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_QUIT:
						m_bRunning = false;
						break;

					case SDL_KEYDOWN:
						Keyboard::Instance().Press(event.key.keysym.scancode);

						switch (event.key.keysym.sym)
						{
						case SDLK_ESCAPE:
							m_bRunning = false;
							break;

						default:
							break;
						}

						break;

					case SDL_KEYUP:
						Keyboard::Instance().Release(event.key.keysym.scancode);
						break;

					case SDL_MOUSEWHEEL:
						break;

					case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
						Mouse::Instance().Event(event.button);
						break;

					case SDL_MOUSEMOTION:
						Mouse::Instance().Move(event.motion.x, event.motion.y);
						break;
					}
				}

				Mouse::Instance().Update();
				Keyboard::Instance().Update();

				SwapBuffers();
			}
		}


		bool Window::Initialize()
		{
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
			{
				std::cerr << "Failed to create SDL2 window!" << std::endl;
				return false;
			}

			std::string title = "Forest";

			m_Handle = SDL_CreateWindow(
				title.c_str(),
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				DEF_WINDOW_WIDTH,
				DEF_WINDOW_HEIGHT,
				SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
			);

			if (!m_Handle)
			{
				SDL_Quit();
				std::cerr << "Failed to create SDL Window!" << std::endl;
				
				return false;
			}

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

			m_GLContext = SDL_GL_CreateContext(m_Handle);

			if (!m_GLContext)
			{
				std::cerr << "Failed to create GL Context!" << std::endl;
				return false;
			}

			GLenum err = glewInit();

			if (err != GLEW_OK)
			{
				std::cerr << "Glew Error: -> " << glewGetErrorString(err) << std::endl;
				return false;
			}

			return true;
		}


		void Window::SwapBuffers()
		{
			SDL_GL_SwapWindow(m_Handle);
		}

		void Window::Destroy()
		{
			m_bRunning = false;
			SDL_DestroyWindow(m_Handle);
			SDL_GL_DeleteContext(m_GLContext);
			SDL_Quit();
		}
	}
}
