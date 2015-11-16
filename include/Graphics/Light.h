#ifndef BALLZ_GRAPHICS_LIGHT_H
#define BALLZ_GRAPHICS_LIGHT_H

#include "Object3D.h"

namespace Forest
{
	namespace Graphics
	{
		class Light : public Object3D
		{
		public:
			Light(const Vector3& pos, const Vector3& color, float ambInt) : 
				Object3D(pos),
				m_Color(color),
				m_AmbientIntensity(ambInt)
			{}

			Light(const Vector3& pos, const Vector3& color, const Vector3& att, float ambInt) :
				Object3D(pos),
				m_Color(color),
				m_Attenuation(att),
				m_AmbientIntensity(ambInt)
			{}

			~Light() {}

			//Getters
			const Vector3&	Color() const				{ return m_Color; }
			const Vector3&	Attenuation() const			{ return m_Attenuation; }
			const float		AmbientIntensity() const	{ return m_AmbientIntensity; }

			//Setters
			void	SetColor(const Vector3& color) { m_Color = color; }

		private:
			Vector3		m_Color;
			Vector3		m_Attenuation;
			float		m_AmbientIntensity;

		};
	}
}

#endif	//BALLZ_GRAPHICS_LIGHT_H