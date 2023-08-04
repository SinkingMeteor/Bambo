#pragma once
#include "Core/Essentials.h"
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

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation{ glm::quat(Rotation) };
			return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}
	};
}