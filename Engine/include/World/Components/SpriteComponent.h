#pragma once
#include "Core/Essentials.h"
#include "Graphics/Texture2D.h"

namespace Bambo
{
	struct BAMBO_API SpriteComponent final : public Component
	{
		SPtr<Texture2D> Texture{ nullptr };
		uint32 SpriteRectIndex{ 0 };

		SpriteComponent() = default;

		SpriteComponent(SPtr<Texture2D> texture) : 
			Texture(texture),
			SpriteRectIndex(0)
		{}

		SpriteComponent(SPtr<Texture2D> texture, uint32 rectIndex) :
			Texture(texture),
			SpriteRectIndex(rectIndex)
		{}

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