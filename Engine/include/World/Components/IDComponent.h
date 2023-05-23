#pragma once
#include "engpch.h"
#include "IID.h"

namespace Bambo
{
	class BAMBO_API IDComponent final
	{
	public:
		IID ID;

		IDComponent() = default;
		IDComponent(IID id) : ID(id) {}
		IDComponent(const IDComponent& id) = default;
	};
}