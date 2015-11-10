/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	Mouse input class (singleton) definition
*/

#include "Mouse.h"

//C-Runtime
#include <cassert>
#include <iostream>

namespace Forest
{
	namespace Core
	{
		Mouse::Mouse()
		{
			m_X = 1280 / 2;
			m_Y = 720 / 2;
			m_PrevX = 1280 / 2;
			m_PrevY = 720 / 2;
			m_Cur[MOUSE_LEFT].state = SDL_RELEASED;
			m_Cur[MOUSE_RIGHT].state = SDL_RELEASED;
			m_Cur[MOUSE_MIDDLE].state = SDL_RELEASED;

			m_Prev[MOUSE_LEFT].state = SDL_RELEASED;
			m_Prev[MOUSE_RIGHT].state = SDL_RELEASED;
			m_Prev[MOUSE_MIDDLE].state = SDL_RELEASED;
		}

		/// <summary>
		/// Access to the class.
		/// </summary>
		/// <returns></returns>
		Mouse& Mouse::Instance()
		{
			static Mouse m_pInstance;
			return m_pInstance;
		}


		/// <summary>
		/// Mouse cursor position on horizontal axis
		/// </summary>
		/// <returns>Current X-axis position</returns>
		const uint16_t Mouse::X() const
		{
			return m_X;
		}


		/// <summary>
		/// Mouse cursor position on vetical axis
		/// </summary>
		/// <returns>Current Y-axis position</returns>
		const uint16_t Mouse::Y() const
		{
			return m_Y;
		}


		/// <summary>
		/// Mouse cursor position on horizontal axis
		/// </summary>
		/// <returns>Previous X-axis position</returns>
		const uint16_t Mouse::PrevX() const
		{
			return m_PrevX;
		}


		/// <summary>
		/// Mouse cursor position on vertical axis
		/// </summary>
		/// <returns>Current X-axis position</returns>
		const uint16_t Mouse::PrevY() const
		{
			return m_PrevY;
		}


		/// <summary>
		/// Mouse button release check.
		/// </summary>
		/// <param name="button">Button being checked.</param>
		/// <returns>TRUE if button is released, FALSE otherwise</returns>
		bool Mouse::Released(uint8_t button)
		{
			#if defined(DEBUG) || defined(_DEBUG)
			assert(button >= 0 && button <= 3);
			#endif //DEBUG

			return (m_Cur[button].state == SDL_RELEASED && m_Prev[button].state == SDL_PRESSED);
		}


		/// <summary>
		/// Mouse button press/hold check.
		/// </summary>
		/// <param name="button">Button being checked.</param>
		/// <returns>TRUE if button is pressed/hold, FALSE otherwise</returns>
		bool Mouse::Pressed(uint8_t button)
		{
			#if defined(DEBUG) || defined(_DEBUG)
			assert(button >= 0 && button < 3);
			#endif //DEBUG

			return m_Cur[button].state == SDL_PRESSED;
		}

		/// <summary>
		/// Mouse button press check.
		/// </summary>
		/// <param name="button">Button being checked.</param>
		/// <returns>TRUE if button is pressed, FALSE otherwise</returns>
		bool Mouse::SinglePress(uint8_t button)
		{
			#if defined(DEBUG) || defined(_DEBUG)
			assert(button >= 0 && button < 3);
			#endif //DEBUG

			return (m_Cur[button].state == SDL_PRESSED && m_Prev[button].state == SDL_RELEASED);
		}


		/// <summary>
		/// Updates curson position inside the window.
		/// </summary>
		/// <param name="x">The x.</param>
		/// <param name="y">The y.</param>
		void Mouse::Move(uint16_t x, uint16_t y)
		{
			m_PrevX = m_X;
			m_X = x;

			m_PrevY = m_Y;
			m_Y = y;
		}


		/// <summary>
		/// Updates mouse button state
		/// </summary>
		/// <param name="e">Event transpired.</param>
		void Mouse::Event(SDL_MouseButtonEvent e)
		{
			switch (e.button)
			{
			case SDL_BUTTON_LEFT:
				m_Cur[MOUSE_LEFT].state = e.state;
				m_Cur[MOUSE_LEFT].clicks = e.clicks;
				break;

			case SDL_BUTTON_RIGHT:
				m_Cur[MOUSE_RIGHT].state = e.state;
				m_Cur[MOUSE_RIGHT].clicks = e.clicks;
				break;

			case SDL_BUTTON_MIDDLE:
				m_Cur[MOUSE_MIDDLE].state = e.state;
				m_Cur[MOUSE_MIDDLE].clicks = e.clicks;
				break;
			}
		}


		/// <summary>
		/// Updates the mouse input data.
		/// </summary>
		void Mouse::Update()
		{
			memcpy(m_Prev, m_Cur, sizeof(m_Cur));
		}
	}
}
