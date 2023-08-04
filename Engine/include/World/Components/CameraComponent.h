#pragma once
#include "Core/Essentials.h"
#include "Graphics/Rect.h"
#include "Graphics/Camera.h"

namespace Bambo
{
	struct BAMBO_API CameraComponent final : public Component
	{
		COMPONENT_BODY(CameraComponent)

		Camera Camera;

		CameraComponent() = default;
	};


}