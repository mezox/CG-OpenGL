/*
*  Project:		Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	definition of unicode string types
*/


#ifndef FOREST_DEFINES_STRINGS_H
#define FOREST_DEFINES_STRINGS_H

//C Runtime header files
#ifdef FOREST_SYS_WINDOWS
	#ifndef _TCHAR_INC_
	#include <tchar.h>
	#endif
#else
	#include <string.h>
#endif

#ifndef _STRING_H
	#include <string>
#endif


#if defined(UNICODE) || defined(_UNICODE)
	using ustring = std::wstring;
	#define to_ustring(v) std::to_wstring(v)
#else
	#define ustring std::string
	#define to_ustring(v) std::to_string(v)
#endif

#endif	//FOREST_DEFINES_STRINGS_H