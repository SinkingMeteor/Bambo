#pragma once
#include "pch.h"
#include "glm.hpp"

namespace Bambo
{
	namespace Serialization
	{
		BAMBO_API void Serialize(const glm::vec3& vec, nlohmann::json& node);
		BAMBO_API void Deserialize(glm::vec3& vec, nlohmann::json& node);

		BAMBO_API void Serialize(const glm::mat4& mat, nlohmann::json& node);
		BAMBO_API void Deserialize(glm::mat4& mat, nlohmann::json& node);
	}
}