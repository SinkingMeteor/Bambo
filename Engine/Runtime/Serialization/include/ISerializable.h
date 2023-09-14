#pragma once
#include "pch.h"

namespace Bambo
{
	class ISerializable
	{
	public:
		virtual ~ISerializable() = default;
		virtual void Serialize(nlohmann::json& node) = 0;
		virtual void Deserialize(nlohmann::json& node) = 0;
	};
}