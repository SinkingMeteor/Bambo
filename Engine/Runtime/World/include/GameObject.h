#pragma once
#include "Essentials.h"
#include "Transform.h"
namespace Bambo
{
	class Component;

	class BAMBO_API GameObject
	{
		friend class World;
		using It = std::vector<IID>::iterator;

	public:
		enum Properties : uint32
		{
			IsEditorOnly = 1 << 0,
			IsDisabled = 1 << 1
		};

		GameObject() = default;
		GameObject(World* world, IID id);

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

		void SetParent(IID newParent);
		IID GetParent() { return m_parent; }

		Transform* GetTransform() { return &m_transform; }
		std::vector<IID>& GetChildren() { return m_children; }
		const std::vector<IID>& GetChildrenConst() const { return m_children; }
		std::vector<UPtr<Component>>& GetComponentsArray() { return m_components; }
		std::size_t GetChildrenCount() const { return m_children.size(); }
		std::string& GetName() { return m_name; }
		void SetName(const std::string& newName) { m_name = newName; }

		void AddChild(IID child);
		void RemoveChild(IID child);

		virtual void Start();
		virtual void Tick(float deltaSeconds);
		virtual void OnRender(const glm::mat4& parentWorldMatrix);
		virtual void End();
		
		bool operator==(const GameObject& go) { return m_id == go.m_id; }
		bool operator!=(const GameObject& go) { return m_id != go.m_id; }

		Properties GetProperties() const { return m_properties; }
		bool HasProperty(Properties property) const { return (m_properties & property) != 0; }
		void AddProperty(Properties property) { m_properties = static_cast<Properties>(static_cast<uint32>(m_properties) | static_cast<uint32>(property)); }
		void RemoveProperty(Properties property) { m_properties = static_cast<Properties>(static_cast<uint32>(m_properties) & ~static_cast<Properties>(property)); }

		void Serialize(nlohmann::json& node);
		void Deserialize(nlohmann::json& node);

	private:
		Transform m_transform;
		std::vector<UPtr<Component>> m_components;
		std::vector<IID> m_children;
		IID m_parent;
		std::string m_name;
		Properties m_properties;

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
		comp->PostConstruct();
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