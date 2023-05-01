#pragma once
#include "pch.h"

namespace Bambo 
{
	struct BAMBO_API WindowSettings
	{
	public:
		uint32 Width{1};
		uint32 Height{1};
		std::string Title{};
	};
}