#pragma once
#include "engpch.h"

namespace Bambo
{
	class BAMBO_API TagComponent final
	{
	public:
		std::string Tag;

		TagComponent() = default;
		TagComponent(const std::string& tag) : Tag(tag) {}
	};
}