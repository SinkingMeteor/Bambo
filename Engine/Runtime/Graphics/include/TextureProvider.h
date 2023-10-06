#pragma once
#include "Essentials.h"
#include "Resource/ResourceProvider.h"
#include "Texture2D.h"
#include "Engine.h"

namespace Bambo 
{
	struct BAMBO_API TextureLoader final
	{
		using result_type = std::shared_ptr<Texture2D>;

		result_type operator()(Engine* engine, const std::size_t id, const std::string& path) const
		{
			SPtr<Texture2D> texture = std::make_shared<Texture2D>(engine, id);
			texture->LoadFromFile(path);
			return texture;
		}
	};

	using TextureProvider = ResourceProvider<Texture2D, TextureLoader>;
}