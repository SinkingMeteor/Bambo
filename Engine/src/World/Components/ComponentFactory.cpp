#include "World/Components/ComponentFactory.h"

namespace Bambo
{
	void ComponentFactory::Register(std::size_t id, CompFactoryFunc factoryFunc)
	{
		BAMBO_ASSERT(!IsRegistered(id), "Component factory func is already registered")
		m_factories[id] = factoryFunc;
	}

	void ComponentFactory::Unregister(std::size_t id)
	{
		BAMBO_ASSERT(IsRegistered(id), "Component factory func was not registered")
		m_factories.erase(id);
	}

	bool ComponentFactory::IsRegistered(std::size_t id) const
	{
		auto it = m_factories.find(id);
		return it != m_factories.end();
	}

	UPtr<Component> ComponentFactory::CreateComponent(std::size_t id)
	{
		BAMBO_ASSERT(IsRegistered(id), "Component factory func was not registered")
		return m_factories[id]();
	}
}