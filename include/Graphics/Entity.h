#pragma once

#ifndef FOREST_GRAPHICS_OBJECT3D_H
#	include "Object3D.h"
#endif

#ifndef FOREST_GRAPHICS_OBJMODEL_H
#	include "OBJModel.h"
#endif

#ifndef _MEMORY_
#	include <memory>
#endif

using namespace std;

namespace Forest
{
	namespace Graphics
	{
		class Entity : public Object3D
		{
		public:
			Entity(const shared_ptr<OBJModel> m, const Vector3& p, const Vector3& r, const Vector3& s) :
				Object3D(p,r,s)
				{
					m_Model = m;
				}

			~Entity() { }

			const shared_ptr<OBJModel>		Model() const { return m_Model; }
			void Reset()								{ m_Model.reset(); }

		private:
			shared_ptr<OBJModel>	m_Model;
		};
	}
}
