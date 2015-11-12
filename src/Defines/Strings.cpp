/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	implementation of conversion from unicode
*				to std::tring
*/

#include "Strings.h"

std::string UStringToStd(const ustring& str)
{
#ifdef FOREST_SYS_WINDOWS
	uconverter cv;
	return cv.to_bytes(str);
#else
	return UString(str);
#endif
}