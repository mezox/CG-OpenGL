/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	Keyboard input class (singleton) declaration
*/

#ifndef FOREST_CORE_INPUT_KEYBOARD_H
#define FOREST_CORE_INPUT_KEYBOARD_H

//C++ Runtime
#include <map>

#ifndef _SDL_H
	#include "SDL2\SDL.h"
#endif

#ifndef FOREST_CORE_INONCOPY_H
	#include "InonCopy.h"
#endif

namespace Forest
{
	namespace Core
	{
		class Keyboard
		{
			typedef std::map<SDL_Scancode, bool> KeyState;

		public:
			static Keyboard&	Instance();

			void Press(SDL_Scancode sc);
			void Release(SDL_Scancode sc);
			bool SingleKey(SDL_Scancode sc);
			void Update();

		private:
			KeyState m_Cur;
			KeyState m_Prev;
		};
	}
}

#endif