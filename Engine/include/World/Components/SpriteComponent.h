#pragma once
#include "Core/Essentials.h"
#include "Graphics/Texture2D.h"

namespace Bambo
{
	struct BAMBO_API SpriteComponent final : public Component
	{
		COMPONENT_BODY(SpriteComponent)

		SPtr<Texture2D> Texture{ nullptr };
		int32 SpriteRectIndex{ 0 };

		SpriteComponent() = default;

		virtual void Serialize(nlohmann::json& node) override
		{
			node["name"] = "SpriteComponent";
			//node["texture"] = Texture->
			node["rectId"] = SpriteRectIndex;
		}

		virtual void Deserialize(nlohmann::json& node) override
		{
			SpriteRectIndex = node["rectId"].get<uint32>();
		}
	};
}