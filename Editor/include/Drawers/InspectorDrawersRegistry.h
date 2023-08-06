#pragma once
#include "Core/Essentials.h"
#include "Core/SingletonManager.h"
#include "World/Components/Components.h"

using namespace Bambo;

namespace BamboEditor
{
	class InspectorDrawersRegistry : public Bambo::ISingleton
	{
		SINGLETON_BODY(InspectorDrawersRegistry, 'INSP');	

		using CompDrawerFunc = std::function<void(Bambo::Component*)>;

	public:
		InspectorDrawersRegistry() : m_registry() {};
		void Register(std::size_t id, CompDrawerFunc drawerFunc);
		void Unregister(std::size_t id);
		bool IsRegistered(std::size_t id) const;
		void DrawComponent(std::size_t component, Bambo::Component*);

	private:
		std::unordered_map<std::size_t, CompDrawerFunc> m_registry;
	};
}