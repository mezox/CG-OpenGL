/*
*  Project:		Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	definition of in and out unicode streams
*/

#ifndef FOREST_DEFINES_IOSTREAM_H
#define FOREST_DEFINES_IOSTREAM_H

//C Runtime header files
#ifndef _IOSTREAM_
	#include <iostream>
#endif


#if defined(UNICODE) || defined(_UNICODE)
	#define ucout std::wcout
	#define ucin std::wcin
#else
	#define ucout std::cout
	#define ucin std::cin
#endif

#endif //FOREST_DEFINES_IOSTREAM_H

