#pragma once
#include "Core/Essentials.h"
#include "Graphics/Texture2D.h"
#include "World/Components/Component.h"

namespace Bambo
{
	struct BAMBO_API SpriteComponent final : public Component
	{
		COMPONENT_BODY(SpriteComponent);

		SPtr<Texture2D> Texture{ nullptr };
		int32 SpriteRectIndex{ 0 };

		SpriteComponent() = default;

		virtual void Serialize(nlohmann::json& node) override;
		virtual void Deserialize(nlohmann::json& node);
	};
}