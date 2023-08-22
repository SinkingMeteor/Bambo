#pragma once
#include "Core/Essentials.h"
#include "Core/Resource/ResourceProvider.h"
#include "Graphics/Texture2D.h"

namespace Bambo 
{
	struct BAMBO_API TextureLoader final
	{
		using result_type = std::shared_ptr<Texture2D>;

		result_type operator()(const std::size_t id, const std::string& path) const
		{
			std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(id);
			texture->LoadFromFile(path);
			return texture;
		}
	};

	using TextureProvider = ResourceProvider<Texture2D, TextureLoader>;
}