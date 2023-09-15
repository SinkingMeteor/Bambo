#include "InspectorDrawersRegistry.h"

namespace BamboEditor
{
	void InspectorDrawersRegistry::Register(std::size_t id, CompDrawerFunc factoryFunc)
	{
		BAMBO_ASSERT(!IsRegistered(id), "Component drawer func is already registered")
			m_registry[id] = factoryFunc;
	}

	void InspectorDrawersRegistry::Unregister(std::size_t id)
	{
		BAMBO_ASSERT(IsRegistered(id), "Component drawer func was not registered")
			m_registry.erase(id);
	}

	bool InspectorDrawersRegistry::IsRegistered(std::size_t id) const
	{
		auto it = m_registry.find(id);
		return it != m_registry.end();
	}

	void InspectorDrawersRegistry::DrawComponent(std::size_t id, Bambo::Component* component)
	{
		BAMBO_ASSERT(IsRegistered(id), "Component drawer func was not registered")
		m_registry[id](component);
	}
}