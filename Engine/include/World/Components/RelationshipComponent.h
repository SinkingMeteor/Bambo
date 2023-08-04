#pragma once
#include "pch.h"
#include "Component.h"

namespace Bambo
{
	class BAMBO_API RelationshipComponent : public Component
	{
		COMPONENT_BODY(RelationshipComponent)

		using It = std::vector<RelationshipComponent*>::iterator;
	public:
		RelationshipComponent() = default;

		void SetParent(RelationshipComponent* newParent)
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

		RelationshipComponent* GetParent() { return m_parent; }
		std::vector<RelationshipComponent*>& GetChildren() { return m_children; }
		const std::vector<RelationshipComponent*>& GetChildrenConst() const { return m_children; }
		std::size_t GetChildrenCount() const { return m_children.size(); }

		void AddChild(RelationshipComponent* child)
		{
			It it = m_children.begin();
			It end = m_children.end();
			for (; it != end; ++it)
			{
				if (child == *it)
				{
					Logger::Get()->Log("RelationshipComponent", Verbosity::Warning, "The parent already has the child");
					return;
				}
			}
			m_children.push_back(child);
		}

		void RemoveChild(RelationshipComponent* child)
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

	private:
		RelationshipComponent* m_parent;
		std::vector<RelationshipComponent*> m_children;
	};
}