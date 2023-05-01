#pragma once
#include "pch.h"

namespace Bambo 
{
	struct BAMBO_API WindowSettings
	{
	public:
		uint Width{1};
		uint Height{1};
		std::string Title{};
	};
}