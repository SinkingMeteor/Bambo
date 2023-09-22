#pragma once
#include "Essentials.h"
#include "RenderAPI.h"

namespace Bambo
{
	class BAMBO_API FontImplementation
	{
	public:
		FontImplementation() = default;
		FontImplementation(const FontImplementation&) = delete;
		FontImplementation& operator=(const FontImplementation&) = delete;
		virtual ~FontImplementation() {}

		virtual void LoadFromFile(const std::string& filePath);

		static UPtr<FontImplementation> CreateBamboFont();
	};
}