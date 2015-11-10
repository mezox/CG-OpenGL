/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	Mouse input class (singleton) declaration
*/

#ifndef FOREST_CORE_INPUT_MOUSE_H
#define FOREST_CORE_INPUT_MOUSE_H

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
		struct ClickState
		{
			uint8_t clicks;
			uint8_t state;
		};

		class Mouse : INonCopy
		{
		public:
			static const uint8_t MOUSE_BUTTONS_NUM	= 3;
			static const uint8_t MOUSE_LEFT			= 0;
			static const uint8_t MOUSE_RIGHT		= 1;
			static const uint8_t MOUSE_MIDDLE		= 2;

		public:
			static Mouse& Instance();
			const uint16_t X() const;
			const uint16_t Y() const;
			const uint16_t PrevX() const;
			const uint16_t PrevY() const;

			bool Released(uint8_t button);
			bool Pressed(uint8_t button);
			bool SinglePress(uint8_t button);

			void Move(uint16_t x, uint16_t y);
			void Event(SDL_MouseButtonEvent e);
			void Update();

		private:
			Mouse();

		private:
			uint16_t	m_X;
			uint16_t	m_PrevX;
			uint16_t	m_Y;
			uint16_t	m_PrevY;

			ClickState m_Cur[MOUSE_BUTTONS_NUM];
			ClickState m_Prev[MOUSE_BUTTONS_NUM];
		};
	}
}

#endif	//FOREST_CORE_INPUT_MOUSE_H