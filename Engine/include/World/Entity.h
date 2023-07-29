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
		Entity(const flecs::entity& entity, World* world) :
			m_entity(entity),
			m_world(world)
		{}

		template<typename T>
		T* GetComponent();

		template<>
		IDComponent* Entity::GetComponent()
		{
			BAMBO_ASSERT(false, "Can't get id component from GetComponent function. Use getter/setter instead")
				return nullptr;
		}

		template<typename T>
		const T* GetComponentConst() const;
		template<typename T>
		T* AddComponent();
		template<typename T>
		T* AddComponent(const T& component);
		template<typename T>
		bool HasComponent() const;
		template<typename T>
		void RemoveComponent();
	
		IID GetID() const;
		void SetID(IID id);

		flecs::entity GetInternalEntity() const { return m_entity; }
		bool IsDestroyed() const { return !m_entity.is_alive(); }
		bool IsValid() const { return m_entity.is_valid() && m_world; }

	private:
		flecs::entity m_entity;
		World* m_world;
	};

	template<typename T>
	T* Entity::GetComponent()
	{
		BAMBO_ASSERT_S(IsValid())
		BAMBO_ASSERT_S(m_entity.has<T>())

		return m_entity.get_mut<T>();
	}

	template<typename T>
	const T* Entity::GetComponentConst() const
	{
		BAMBO_ASSERT_S(IsValid())
		BAMBO_ASSERT_S(m_entity.has<T>())

		return m_entity.get<T>();
	}

	template<typename T>
	T* Entity::AddComponent()
	{
		BAMBO_ASSERT_S(IsValid())
		BAMBO_ASSERT_S(!m_entity.has<T>())

		return m_entity.add<T>().get_mut<T>();
	}

	template<typename T>
	T* Entity::AddComponent(const T& component)
	{
		BAMBO_ASSERT_S(IsValid())
		BAMBO_ASSERT_S(!m_entity.has<T>())

		return m_entity.set<T>(component).get_mut<T>();
	}

	template<typename T>
	bool Entity::HasComponent() const
	{
		BAMBO_ASSERT_S(IsValid())

		return m_entity.has<T>();
	}

	template<typename T>
	void Entity::RemoveComponent()
	{
		BAMBO_ASSERT_S(IsValid())
		BAMBO_ASSERT_S(m_entity.has<T>())

		m_entity.remove<T>();
	}
}