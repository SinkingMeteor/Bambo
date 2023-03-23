#pragma once
#include "pch.h"
#include "Graphics.h"
#include "Resource/ResourceProvider.h"
#include "Texture2D.h"
namespace Bambo 
{
	struct BAMBO_API TextureLoader
	{
		using result_type = std::shared_ptr<Texture2D>;

		result_type operator()(const std::string& path) const
		{
			std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>();
			texture->LoadFromFile(path);
			return texture;
		}
	};

	using TextureProvider = ResourceProvider<Texture2D, TextureLoader>;
}