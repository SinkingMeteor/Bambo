#include "World/Entity.h"
#include "World/World.h"

namespace Bambo
{
	IID Entity::GetID() const
	{
		BAMBO_ASSERT_S(m_entity.is_valid())
		BAMBO_ASSERT_S(m_entity.has<IDComponent>())

		return GetComponentConst<IDComponent>()->ID;
	}

	void Entity::SetID(IID id)
	{
		BAMBO_ASSERT_S(m_entity.is_valid())
		BAMBO_ASSERT_S(m_entity.has<IDComponent>())

		IID oldId = m_entity.get_mut<IDComponent>()->ID;
		m_entity.get_mut<IDComponent>()->ID = id;
		m_world->ChangeID(*this, oldId, id);
	}

}