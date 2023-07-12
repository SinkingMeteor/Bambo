#pragma once
#include "engpch.h"
#include "Essentials.h"

namespace Bambo
{
	bool FromJson(rttr::instance& instance, nlohmann::json& jsonNode);
	void ToJson(rttr::instance& instance, nlohmann::json& jsonNode);
}