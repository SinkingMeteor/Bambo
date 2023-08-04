#pragma once
#include "Core/Essentials.h"

namespace Bambo
{

#define COMPONENT_BODY(Name) public: \
	static std::size_t GetTypeID() \
	{	\
		static std::size_t id = std::hash<std::string_view>{}(#Name); \
		return id; \
	}	\
	virtual std::size_t GetID() const override \
	{	\
		return GetTypeID(); \
	}	\

	


class GameObject;

	class Component
	{
		friend class GameObject;
	public:
		virtual ~Component() = default;
		
		Component(const Component&) = delete;
		Component(Component&&) = delete;

		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;

		virtual std::size_t GetID() const { return 0; }
		GameObject* GetOwner() { return m_owner; }
	protected:
		Component() = default;
		GameObject* m_owner;

		void SetOwner(GameObject* owner) { m_owner = owner; }
	};
}
