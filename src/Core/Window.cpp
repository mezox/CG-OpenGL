/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	Window class (singleton) declaration
*/

#include "Window.h"

#include <GL/glew.h>

#ifndef FOREST_CORE_INPUT_MOUSE_H
#	include "Mouse.h"
#endif

#ifndef FOREST_CORE_INPUT_KEYBOARD_H
#	include "Keyboard.h"
#endif

#include <Windows.h>
#include "Renderer.h"
#include "TerrainRenderer.h"

using namespace Forest::Graphics;

namespace Forest
{
	namespace Core
	{
		float Window::m_DeltaTime = 0.0f;

		Window::Window() :
			INonCopy(),
			m_bRunning(false),
			m_bFullscreen(false),
			m_bCursorHidden(false)
		{
			Initialize();
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
			Camera3D	camera(1280,720, Vector3(0.0f,40.0f,0.0f));
			Renderer	renderer(camera);
			Terrain		terrain(-0.5f, -0.5f);
			TerrainRenderer tRenderer = TerrainRenderer(camera, renderer.Lights());

			float time = 0.0f;

			float t = 0.0f;
			float dt = 0.1f;

			float currentTime = 0.0f;
			float accumulator = 0.0f;

			m_bRunning = true;

			std::cout << glGetString(GL_VERSION) << std::endl;

			//Main Game loop
			while (m_bRunning)
			{
				const float newTime = Time();
				m_DeltaTime = newTime - currentTime;
				currentTime = newTime;

				if (m_DeltaTime > 0.25f)
					m_DeltaTime = 0.25f;

				accumulator += m_DeltaTime;

				while (accumulator >= dt)
				{
					accumulator -= dt;
					t += dt;
				}

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
						camera.Zoom(event.wheel.y);
						break;

					case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
						Mouse::Instance().Event(event.button);
						break;

					case SDL_MOUSEMOTION:
						Mouse::Instance().Move(event.motion.x, event.motion.y);

						if (Mouse::Instance().Pressed(Mouse::MOUSE_LEFT))
						{
							float mdx = static_cast<float>(Mouse::Instance().X() - Mouse::Instance().PrevX());
							float mdy = static_cast<float>(Mouse::Instance().Y() - Mouse::Instance().PrevY());

							camera.CalcPitch(mdy);
							camera.CalcAngleAround(mdx);
						}
						break;
					}
				}

				Mouse::Instance().Update();
				Keyboard::Instance().Update();

				camera.Update();

				renderer.Render(camera);
				tRenderer.Render(terrain, camera);

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


		/// <summary>
		/// Swap buffer function calling SDL2 built-in swap buff. function
		/// </summary>
		void Window::SwapBuffers()
		{
			SDL_GL_SwapWindow(m_Handle);
		}


		/// <summary>
		/// Window clean-up method.
		/// </summary>
		void Window::Destroy()
		{
			m_bRunning = false;
			SDL_DestroyWindow(m_Handle);
			SDL_GL_DeleteContext(m_GLContext);
			SDL_Quit();
		}


		/// <summary>
		/// Times method measuring time between frames.
		/// </summary>
		/// <returns></returns>
		float Window::Time()
		{
			static __int64 start = 0;
			static __int64 frequency = 0;

			if (start == 0)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&start);
				QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
				return 0.0f;
			}

			__int64 counter = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&counter);
			return (float)((counter - start) / double(frequency));
		}
	}
}
