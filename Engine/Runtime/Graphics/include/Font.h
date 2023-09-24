#pragma once
#include "Essentials.h"
#include "Resource/Resource.h"
#include "FontImplementation.h"

namespace Bambo
{

	class BAMBO_API Font final : public Resource
	{
	public:
		Font(std::size_t instanceID);
		void LoadFromFile(const std::string& fontFile);
	private:
		UPtr<FontImplementation> m_fontImplementation;
	};
}