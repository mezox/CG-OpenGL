/*
*  Project:	Forest, rendering using OpenGL
*	Location:	Lappeenranta University of Technology
*	Author:		Tomáš Kubovčík, t.kubovcik@gmail.com
*	File desc:	NonCopyable class (interface) declaration
*/

#ifndef FOREST_CORE_INONCOPY_H
#define FOREST_CORE_INONCOPY_H

namespace Forest
{
	namespace Core
	{
		class INonCopy
		{
		public:
			INonCopy(const INonCopy&) = delete;
			INonCopy& operator=(const INonCopy&) = delete;

		protected:
			INonCopy() {}
			virtual ~INonCopy() {}
		};
	}
}

#endif	//FOREST_CORE_INONCOPY_H