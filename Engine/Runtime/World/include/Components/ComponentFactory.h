#pragma once
#include "Essentials.h"
#include "Window.h"
#include "Component.h"
namespace Bambo
{
	class ComponentFactory
	{
		using CompFactoryFunc = std::function<UPtr<Component>()>;
	public:
		ComponentFactory() = default;
		void Register(std::size_t id, CompFactoryFunc factoryFunc);
		void Unregister(std::size_t id);
		bool IsRegistered(std::size_t id) const;
		UPtr<Component> CreateComponent(std::size_t component);

	private:
		std::unordered_map<std::size_t, CompFactoryFunc> m_factories;
	};
}