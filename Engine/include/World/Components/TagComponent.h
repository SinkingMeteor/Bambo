#pragma once
#include "Core/Essentials.h"

namespace Bambo
{
	class BAMBO_API TagComponent final : public Component
	{
		COMPONENT_BODY(TagComponent)

	public:
		std::string Tag;

		TagComponent() = default;
	};
}