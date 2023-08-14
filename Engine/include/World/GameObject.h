#pragma once
#include "Core/Essentials.h"
#include "Components/ComponentFactory.h"
#include "Graphics/Transform.h"
namespace Bambo
{
	class Component;

	class BAMBO_API GameObject
	{
		friend class World;
		using It = std::vector<GameObject*>::iterator;

	public:
		GameObject() = default;
		GameObject(World* world, IID id) :
			m_transform(),
			m_components(),
			m_children(),
			m_parent(nullptr),
			m_name("GameObject"),
			m_id(id),
			m_world(world)
		{}

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		virtual ~GameObject() = default;

		template<typename T>
		T* GetComponent();
		template<typename T>
		const T* GetComponentConst() const;

		template<typename T>
		T* AddComponent();
		template<typename T>
		bool HasComponent() const;
		template<typename T>
		void RemoveComponent();
	
		IID GetID() const { return m_id; }
		void SetID(IID id) { m_id = id; }
		World* GetWorld() { return m_world; }

		bool IsValid() const { return m_world; }

	public:

		void SetParent(GameObject* newParent);
		GameObject* GetParent() { return m_parent; }

		Transform* GetTransform() { return &m_transform; }
		std::vector<GameObject*>& GetChildren() { return m_children; }
		const std::vector<GameObject*>& GetChildrenConst() const { return m_children; }
		std::vector<UPtr<Component>>& GetComponentsArray() { return m_components; }
		std::size_t GetChildrenCount() const { return m_children.size(); }
		std::string& GetName() { return m_name; }
		void SetName(const std::string& newName) { m_name = newName; }

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		
		bool operator==(const GameObject& go)
		{
			return m_id == go.m_id;
		}

		bool operator!=(const GameObject& go)
		{
			return m_id != go.m_id;
		}

		void Serialize(nlohmann::json& node);
		void Deserialize(nlohmann::json& node);

	private:
		Transform m_transform;
		std::vector<UPtr<Component>> m_components;
		std::vector<GameObject*> m_children;
		GameObject* m_parent;
		std::string m_name;

		IID m_id;
		World* m_world;
	};

	template<typename T>
	T* GameObject::GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value);
		BAMBO_ASSERT_S(this && IsValid())

		std::size_t id = T::GetTypeID();
		for (size_t i = 0; i < m_components.size(); ++i)
		{
			if (id == m_components[i]->GetID())
			{
				return Cast<T>(m_components[i].get());
			}
		}

		return nullptr;
	}

	template<typename T>
	const T* GameObject::GetComponentConst() const
	{
		static_assert(std::is_base_of<Component, T>::value);
		BAMBO_ASSERT_S(this && IsValid())
		
		std::size_t id = T::GetTypeID();
		for (size_t i = 0; i < m_components.size(); ++i)
		{
			if (id == m_components[i]->GetID())
			{
				return Cast<T>(m_components[i].get());
			}
		}

		return nullptr;
	}

	template<typename T>
	T* GameObject::AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value);
		BAMBO_ASSERT_S(this && IsValid())
		BAMBO_ASSERT_S(!HasComponent<T>())

		UPtr<T> comp = std::make_unique<T>();
		comp->SetOwner(this);
		m_components.push_back(std::move(comp));

		return Cast<T>(m_components.back().get());
	}

	template<typename T>
	bool GameObject::HasComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value);
		BAMBO_ASSERT_S(this && IsValid())

			const T* ptr = GetComponentConst<T>();
		return ptr != nullptr;
	}

	template<typename T>
	void GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of<Component, T>::value);
		BAMBO_ASSERT_S(this && IsValid())
		BAMBO_ASSERT_S(HasComponent<T>())

		BAMBO_NOT_IMPLEMENTED();
	}
}