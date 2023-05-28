#pragma once
#include "engpch.h"
#pragma warning(push, 0)
#include "flecs.h"
#pragma warning(pop)
#include "Components/Components.h"

namespace Bambo
{
	using EntityManager = flecs::world;
	class World;

	class BAMBO_API Entity final
	{
	public:
		Entity() = default;
		Entity(const flecs::entity& entity) :
			m_entity(entity)
		{}

		template<typename T>
		T* GetComponent();
		template<typename T>
		T* AddComponent();
		template<typename T>
		T* AddComponent(const T& component);
		template<typename T>
		bool HasComponent();
		template<typename T>
		void RemoveComponent();
	
		IID GetID()
		{
			BAMBO_ASSERT_S(m_entity.is_alive())
			BAMBO_ASSERT_S(m_entity.has<IDComponent>())

			return GetComponent<IDComponent>()->ID;
		}

		flecs::entity GetInternalEntity() const { return m_entity; }
		bool IsDestroyed() const { return !m_entity.is_alive(); }

	private:
		flecs::entity m_entity;
	};

	template<typename T>
	T* Entity::GetComponent()
	{
		BAMBO_ASSERT_S(m_entity.is_alive())
		BAMBO_ASSERT_S(m_entity.has<T>())

		return m_entity.get_mut<T>();
	}

	template<typename T>
	T* Entity::AddComponent()
	{
		BAMBO_ASSERT_S(m_entity.is_alive())
		BAMBO_ASSERT_S(!m_entity.has<T>())

		return m_entity.add<T>().get_mut<T>();
	}

	template<typename T>
	T* Entity::AddComponent(const T& component)
	{
		BAMBO_ASSERT_S(m_entity.is_alive())
		BAMBO_ASSERT_S(!m_entity.has<T>())

		return m_entity.set<T>(component).get_mut<T>();
	}

	template<typename T>
	bool Entity::HasComponent()
	{
		BAMBO_ASSERT_S(m_entity.is_alive())

		return m_entity.has<T>();
	}

	template<typename T>
	void Entity::RemoveComponent()
	{
		BAMBO_ASSERT_S(m_entity.is_alive())
		BAMBO_ASSERT_S(m_entity.has<T>())

		m_entity.remove<T>();
	}
}