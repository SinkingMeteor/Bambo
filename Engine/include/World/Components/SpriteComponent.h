#pragma once
#include "Core/Essentials.h"
#include "Graphics/Texture2D.h"

namespace Bambo
{
	struct BAMBO_API SpriteComponent final : public Component
	{
		COMPONENT_BODY(SpriteComponent)

		SPtr<Texture2D> Texture{ nullptr };
		uint32 SpriteRectIndex{ 0 };

		SpriteComponent() = default;
	};
}