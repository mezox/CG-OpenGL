/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	Keyboard input class (singleton) definition
*/

#include "Keyboard.h"

namespace Forest
{
	namespace Core
	{
		/// <summary>
		/// Instantiates keyboard input class.
		/// </summary>
		/// <returns>Reference to this instance (singleton)</returns>
		Keyboard & Keyboard::Instance()
		{
			static Keyboard m_pInstance;
			return m_pInstance;
		}


		/// <summary>
		/// Updates keyboard state (key state) after key has been pressed.
		/// </summary>
		/// <param name="sc">Key scancode.</param>
		void Keyboard::Press(SDL_Scancode sc)
		{
			m_Cur[sc] = true;
		}


		/// <summary>
		/// Updates keyboard state (key state) after key has been released.
		/// </summary>
		/// <param name="sc">Key scancode.</param>
		void Keyboard::Release(SDL_Scancode sc)
		{
			m_Cur[sc] = false;
		}


		/// <summary>
		/// Single key press check
		/// </summary>
		/// <param name="sc">Key scancode.</param>
		/// <returns>TRUE if key has been pressed once, FALSE otherwise</returns>
		bool Keyboard::SingleKey(SDL_Scancode sc)
		{
			return (!m_Prev[sc] && m_Cur[sc]);
		}


		/// <summary>
		/// Updates keyboard state.
		/// </summary>
		void Keyboard::Update()
		{
			m_Prev = m_Cur;
		}
	}
}
