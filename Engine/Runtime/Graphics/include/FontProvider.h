#pragma once
#include "Essentials.h"
#include "Font.h"
#include "Engine.h"

namespace Bambo
{
	struct BAMBO_API FontLoader final
	{
		using result_type = std::shared_ptr<Font>;

		result_type operator()(Engine* engine, const std::size_t id, const std::string& fontPath) const
		{
			std::shared_ptr<Font> font = std::make_shared<Font>(engine, id);
			font->LoadFromFile(fontPath);
			return font;
		}
	};

	using FontProvider = ResourceProvider<Font, FontLoader>;
}