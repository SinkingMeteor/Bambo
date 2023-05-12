#pragma once
#include "engpch.h"
#include "Texture2D.h"
namespace Bambo
{
	struct BAMBO_API SpriteComponent final
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
	};
}