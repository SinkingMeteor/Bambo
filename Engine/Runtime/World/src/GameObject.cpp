#include "GameObject.h"
#include "Components/Components.h"
#include "World.h"
#include "BaseSerialization.h"

namespace Bambo
{
	GameObject::GameObject(World* world, IID id) :
		m_transform(),
		m_components(),
		m_children(),
		m_parent(),
		m_name("GameObject"),
		m_properties(),
		m_id(id),
		m_world(world)
	{}

	void GameObject::Serialize(nlohmann::json& node)
	{
		if (HasProperty(IsEditorOnly)) return;

		node["id"] = (uint64_t)m_id;
		node["name"] = m_name;

		nlohmann::json& transformNode = node["transform"];
		Serialization::Serialize(m_transform.GetPosition(), transformNode["position"]);
		Serialization::Serialize(m_transform.GetRotation(), transformNode["rotation"]);
		Serialization::Serialize(m_transform.GetScale(), transformNode["scale"]);

		for (size_t i = 0; i < m_components.size(); ++i)
		{
			Bambo::Component* component = nullptr;

			if (m_components[i]->GetID() == Bambo::SpriteComponent::GetTypeID() ||
				m_components[i]->GetID() == Bambo::Area2DComponent::GetTypeID())
			{
				component = m_components[i].get();
			}

			if (!component) continue;

			node["components"].push_back({});
			component->Serialize(node["components"].back());
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
		m_name = node["name"];

		nlohmann::json& transformNode = node["transform"];
		m_transform.SetPosition(Serialization::Deserialize<glm::vec3>(transformNode["position"]));
		m_transform.SetRotation(Serialization::Deserialize<glm::vec3>(transformNode["rotation"]));
		m_transform.SetScale(Serialization::Deserialize<glm::vec3>(transformNode["scale"]));

		for (size_t i = 0; i < componentsNode.size(); ++i)
		{
			nlohmann::json& compNode = componentsNode.at(i);
			std::size_t compHash = HashString(compNode["name"]);

			UPtr<Component> comp{};

			if (compHash == Bambo::SpriteComponent::GetTypeID())
			{
				comp = std::make_unique<SpriteComponent>();
			}
			else if (compHash == Bambo::Area2DComponent::GetTypeID())
			{
				comp = std::make_unique<Area2DComponent>();
			}
			else
			{
				continue;
			}

			BAMBO_ASSERT_S(comp.get())

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
		if (HasProperty(IsDisabled)) return;

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