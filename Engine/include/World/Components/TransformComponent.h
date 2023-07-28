#pragma once
#include "engpch.h"
#include "glm.hpp"
#include "gtc/quaternion.hpp"
#include "Serialization/MathSerialization.h"

namespace Bambo
{
	class BAMBO_API TransformComponent final : public Component
	{
	public:
		glm::vec3 Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale{ 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 & position) : Position(position) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation{ glm::quat(Rotation) };
			return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}

		virtual void Serialize(nlohmann::json& node) override
		{
			node["name"] = "TransformComponent";
			Serialization::Serialize(Position, node["Position"]);
			Serialization::Serialize(Rotation, node["Rotation"]);
			Serialization::Serialize(Scale, node["Scale"]);
		}

		virtual void Deserialize(nlohmann::json& node) override
		{
			Serialization::Deserialize(Position, node["Position"]);
			Serialization::Deserialize(Rotation, node["Rotation"]);
			Serialization::Deserialize(Scale, node["Scale"]);
		}
	};
}