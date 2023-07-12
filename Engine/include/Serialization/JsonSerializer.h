#pragma once
#include "engpch.h"
#include "Essentials.h"

namespace Bambo
{
	void ToJson(rttr::instance& instance, nlohmann::json& jsonNode);
}