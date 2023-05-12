#pragma once
#include "engpch.h"
#include "glm.hpp"
#include "gtc/quaternion.hpp"

namespace Bambo
{
	class BAMBO_API TransformComponent final
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
	};
}