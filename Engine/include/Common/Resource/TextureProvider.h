#pragma once

#include "Common/Resource/ResourceProvider.h"

namespace Bambo 
{
	struct SlicedTexture
	{
		Texture2D Texture{};
	};

	struct TextureLoader
	{
		using result_type = std::shared_ptr<SlicedTexture>;

		result_type operator()(const std::string& path) const
		{
			std::shared_ptr texture = std::make_shared<SlicedTexture>();
			return texture;
		}
	};

	using TextureProvider = ResourceProvider<SlicedTexture, TextureLoader>;
}