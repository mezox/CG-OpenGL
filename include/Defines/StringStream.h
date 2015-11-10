/*
*	Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubov?ík, t.kubovcik@gmail.com
*	File desc:	definition of unicode string stream types
*/

#ifndef FOREST_DEFINES_STRINGSTREAM_H
#define FOREST_DEFINES_STRINGSTREAM_H

#ifndef _SSTREAM_
#include <sstream>
#endif

#ifndef FOREST_DEFINES_IOSTREAM_H
#include "Iostream.h"
#endif

#ifndef _OSTREAM_
#include <ostream>
#endif

#if defined(UNICODE) || defined(_UNICODE)
	using usstream = std::wstringstream;
	using uostream = std::wostream;
#else
	using usstream = std::stringstream;
	using uostream = std::ostream;
#endif

#endif	//FOREST_DEFINES_STRINGSTREAM_H
