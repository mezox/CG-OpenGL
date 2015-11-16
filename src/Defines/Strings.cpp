/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	implementation of conversion from unicode
*				to std::string
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