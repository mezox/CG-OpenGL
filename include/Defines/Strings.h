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

#ifdef FOREST_SYS_WINDOWS
	#include <codecvt>
#endif

#ifdef UNICODE
	#define _U(x) L##x
	#define U(x) _U(x)
#else
	#define U(x) x
#endif


#if defined(UNICODE) || defined(_UNICODE)
	using ustring = std::wstring;
	#define to_ustring(v) std::to_wstring(v)
	using uconverter = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>;
#else
	#define ustring std::string
	#define to_ustring(v) std::to_string(v)
#endif


std::string UStringToStd(const ustring& str);

#endif	//FOREST_DEFINES_STRINGS_H