#include "GameObject.h"
#include "Components/Components.h"
#include "World.h"
#include "BaseSerialization.h"

namespace Bambo
{
	void GameObject::Serialize(nlohmann::json& node)
	{
		node["id"] = (uint64_t)m_id;
		node["name"] = m_name;

		nlohmann::json& transformNode = node["transform"];
		Serialization::Serialize(m_transform.GetPosition(), transformNode["position"]);
		Serialization::Serialize(m_transform.GetRotation(), transformNode["rotation"]);
		Serialization::Serialize(m_transform.GetScale(), transformNode["scale"]);

		for (size_t i = 0; i < m_components.size(); ++i)
		{
			node["components"].push_back({});
			m_components[i]->Serialize(node["components"].back());
		}

		for (size_t i = 0; i < m_children.size(); ++i)
		{
			node["children"].push_back({});
			GameObject* child = m_world->GetGameObject(m_children[i]);

			BAMBO_ASSERT_S(child)

			child->Serialize(node["children"].back());
		}
	}

	void GameObject::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_world)

		nlohmann::json& componentsNode = node["components"];
		ComponentFactory* factory = m_world->GetWorldContext()->Engine->GetComponentFactory();
		m_name = node["name"];

		nlohmann::json& transformNode = node["transform"];
		m_transform.SetPosition(Serialization::Deserialize<glm::vec3>(transformNode["position"]));
		m_transform.SetRotation(Serialization::Deserialize<glm::vec3>(transformNode["rotation"]));
		m_transform.SetScale(Serialization::Deserialize<glm::vec3>(transformNode["scale"]));

		for (size_t i = 0; i < componentsNode.size(); ++i)
		{
			nlohmann::json& compNode = componentsNode.at(i);
			std::size_t compHash = HashString(compNode["name"]);

		
			BAMBO_ASSERT_S(factory->IsRegistered(compHash))

			UPtr<Component> comp = factory->CreateComponent(compHash);
			comp->SetOwner(this);
			comp->PostConstruct();
			comp->Deserialize(compNode);
			m_components.push_back(std::move(comp));
		}

		nlohmann::json& childrenNode = node["children"];
		if (childrenNode.is_null() || childrenNode.size() == 0) return;

		for (size_t i = 0; i < childrenNode.size(); ++i)
		{
			IID id = childrenNode.at(i)["id"].get<uint64_t>();
			GameObject* child = m_world->CreateGameObject(m_id, id);
			BAMBO_ASSERT_S(child->IsValid())
			child->Deserialize(childrenNode.at(i));
		}
	}


	void GameObject::AddChild(IID child)
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

	void GameObject::RemoveChild(IID child)
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

	void GameObject::SetParent(IID newParent)
	{
		if (m_parent.IsValid())
		{
			GameObject* oldParent = m_world->GetGameObject(m_parent);
			oldParent->RemoveChild(m_id);
		}

		m_parent = newParent;

		if (m_parent.IsValid())
		{
			GameObject* newParent = m_world->GetGameObject(m_parent);
			newParent->AddChild(m_id);
		}
	}

	void GameObject::Start()
	{
		for (size_t i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Start();
		}

	}

	void GameObject::OnRender(std::vector<glm::mat4>& globals, int32 parentMatIndex)
	{
		globals.push_back(globals[parentMatIndex] * m_transform.GetMatrix());
		int32 selfIndex = globals.size() - 1;

		for (size_t i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->OnRender(globals, selfIndex);
		}

		for (size_t i = 0; i < m_children.size(); ++i)
		{
			GameObject* childGo = m_world->GetGameObject(m_children[i]);
			childGo->OnRender(globals, selfIndex);
		}
	}

	void GameObject::Tick(float deltaSeconds)
	{
		BAMBO_ASSERT_S(m_parent.IsValid())

		for (size_t i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Tick(deltaSeconds);
		}

		for (size_t i = 0; i < m_children.size(); ++i)
		{
			GameObject* childGo = m_world->GetGameObject(m_children[i]);
			childGo->Tick(deltaSeconds);
		}
	}
	void GameObject::End()
	{
		for (size_t i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->End();
		}
	}
}