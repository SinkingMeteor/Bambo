#pragma once
#include "engpch.h"
#include "glm.hpp"
#include "Rect.h"

namespace Bambo
{
	struct BAMBO_API CameraComponent final
	{
		glm::vec2 Size{ 0.0f, 0.0f };                       
		RectFloat Viewport{ {0.0f, 0.0f}, {1.0f, 1.0f} };

		CameraComponent() = default;
		CameraComponent(const glm::vec2& size) :
			Size(size)
		{}

		CameraComponent(const CameraComponent& camera) = default;

		glm::mat4 GetViewMatrix(const glm::mat4& cameraTransform) const
		{
			return glm::inverse(cameraTransform);
		}

		glm::mat4 GetProjectionMatrix() const
		{
			const float aspectRatio = Size.x / Size.y;
			return glm::ortho(0.0f, Size.x, Size.y, 0.0f, -1.0f, 1.0f);
		}
	};
}