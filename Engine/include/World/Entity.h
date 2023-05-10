#pragma once
#include "engpch.h"
#include "flecs.h"
namespace Bambo
{
	using EntityManager = flecs::world;
	class World;

	class BAMBO_API Entity final
	{
	public:
		Entity(const flecs::entity& entity);

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
	private:
		flecs::entity m_entity;
	};

	template<typename T>
	T* Entity::GetComponent()
	{
		BAMBO_ASSERT_S(m_entity.is_alive())
		BAMBO_ASSERT_S(m_entity.has<T>())

		return m_entity.get<T>();
	}

	template<typename T>
	T* Entity::AddComponent()
	{
		BAMBO_ASSERT_S(m_entity.is_alive())
		BAMBO_ASSERT_S(!m_entity.has<T>())

		return m_entity.add<T>().get<T>();
	}

	template<typename T>
	T* Entity::AddComponent(const T& component)
	{
		BAMBO_ASSERT_S(m_entity.is_alive())
		BAMBO_ASSERT_S(!m_entity.has<T>())

		return m_entity.set<T>(component).get<T>();
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