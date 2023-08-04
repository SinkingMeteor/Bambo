#pragma once
#include "pch.h"
#include "Core/IID.h"

namespace Bambo
{
	class BAMBO_API IDComponent final : public Component
	{
		COMPONENT_BODY(IDComponent)

	public:
		IID ID;

		IDComponent() = default;
	};
}