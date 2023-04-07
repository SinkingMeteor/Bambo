#pragma once
#include "pch.h"
namespace Bambo 
{
	struct BAMBO_API WindowSettings
	{
	public:
		int Width{1};
		int Height{1};
		std::string Title{};
	};
}