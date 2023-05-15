#pragma once
#include "engpch.h"
#include "glm.hpp"
#include "Rect.h"
#include "Camera.h"

namespace Bambo
{
	struct BAMBO_API CameraComponent final
	{
		Camera Camera;

		CameraComponent() = default;
		CameraComponent(const CameraComponent& camera) = default;
	};
}