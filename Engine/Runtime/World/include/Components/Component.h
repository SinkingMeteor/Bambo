#pragma once
#include "Essentials.h"
#include "ISerializable.h"

namespace Bambo
{

#define COMPONENT_BODY(Name) public: \
	static std::size_t GetTypeID() \
	{	\
		static std::size_t id = HashString(#Name); \
		return id; \
	}	\
	virtual const std::string& GetName() const override \
	{	\
		static std::string name{#Name}; \
		return name; \
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

		bool IsValid() const { return m_isValid; }

		virtual void PostConstruct() 
		{
			m_isValid = true;
		}
		virtual void Start() {}
		virtual void Tick(float deltaSeconds) {}
		virtual void OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex) {}
		virtual void End() 
		{
			m_isValid = false;
		}

		virtual const std::string& GetName() const { return "Unknown component"; }
		virtual void Serialize(nlohmann::json& node) {}
		virtual void Deserialize(nlohmann::json& node) {}


		virtual std::size_t GetID() const { return 0; }
		GameObject* GetOwner() { return m_owner; }
	protected:
		bool m_isValid;

		Component() = default;
		GameObject* m_owner;

		void SetOwner(GameObject* owner) { m_owner = owner; }
	};
}
