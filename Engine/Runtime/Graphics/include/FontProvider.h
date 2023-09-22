#pragma once
#include "Essentials.h"
#include "Font.h"


namespace Bambo
{
	struct BAMBO_API FontLoader final
	{
		using result_type = std::shared_ptr<Font>;

		result_type operator()(const std::size_t id, const std::string& fontPath) const
		{
			std::shared_ptr<Font> font = std::make_shared<Font>(id);
			font->LoadFromFile(shaderPath);
			return shader;
		}
	};

	using FontProvider = ResourceProvider<Shader, ShaderLoader>;
}