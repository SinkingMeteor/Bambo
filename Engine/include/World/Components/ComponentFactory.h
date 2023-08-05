#pragma once
#include "Core/Essentials.h"
#include "Window/Window.h"
#include "Core/SingletonManager.h"
#include "Component.h"
namespace Bambo
{
	using CompFactoryFunc = std::function<UPtr<Component>()>;

	class ComponentFactory : public ISingleton
	{
		SINGLETON_BODY(ComponentFactory, 'CMPF')
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