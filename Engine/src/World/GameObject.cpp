#include "World/GameObject.h"
#include "World/Components/Components.h"
#include "World/World.h"

namespace Bambo
{
	void GameObject::Serialize(nlohmann::json& node)
	{
		node["id"] = (uint64_t)m_id;

		for (size_t i = 0; i < m_components.size(); ++i)
		{
			node["components"].push_back({});
			m_components[i]->Serialize(node["components"].back());
		}

		for (size_t i = 0; i < m_children.size(); ++i)
		{
			node["children"].push_back({});
			m_children[i]->Serialize(node["children"].back());
		}
	}

	void GameObject::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_world)

			nlohmann::json& componentsNode = node["components"];
		ComponentFactory* factory = ComponentFactory::Get();

		for (size_t i = 0; i < componentsNode.size(); ++i)
		{
			nlohmann::json& compNode = componentsNode.at(i);
			std::size_t compHash = HashString(compNode["name"]);

			if (compHash == TransformComponent::GetTypeID())
			{
				GetComponent<TransformComponent>()->Deserialize(compNode);
				continue;
			}
			if (compHash == TagComponent::GetTypeID())
			{
				GetComponent<TagComponent>()->Deserialize(compNode);
				continue;
			}

			BAMBO_ASSERT_S(factory->IsRegistered(compHash))

			UPtr<Component> comp = factory->CreateComponent(compHash);
			comp->Deserialize(compNode);
			m_components.push_back(std::move(comp));
		}

		nlohmann::json& childrenNode = node["children"];
		if (childrenNode.is_null() || childrenNode.size() == 0) return;

		for (size_t i = 0; i < childrenNode.size(); ++i)
		{
			IID id = childrenNode.at(i)["id"].get<uint64_t>();
			GameObject* child = m_world->CreateGameObject(this, id);
			BAMBO_ASSERT_S(child->IsValid())
				child->Deserialize(childrenNode.at(i));
		}
	}


	void GameObject::AddChild(GameObject* child)
	{
		It it = m_children.begin();
		It end = m_children.end();
		for (; it != end; ++it)
		{
			if (child == *it)
			{
				Logger::Get()->Log("GameObject", Verbosity::Warning, "The parent already has the child");
				return;
			}
		}
		m_children.push_back(child);
	}

	void GameObject::RemoveChild(GameObject* child)
	{
		It it = m_children.begin();
		It end = m_children.end();
		for (; it != end; ++it)
		{
			if (child == *it)
			{
				m_children.erase(it);
				return;
			}
		}
	}

	void GameObject::SetParent(GameObject* newParent)
	{
		if (m_parent)
		{
			m_parent->RemoveChild(this);
		}

		m_parent = newParent;

		if (m_parent)
		{
			m_parent->AddChild(this);
		}
	}
}