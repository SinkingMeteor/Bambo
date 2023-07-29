#pragma once
#include "engpch.h"
#include "glm.hpp"

namespace Bambo
{
	namespace Serialization
	{

		void Serialize(const glm::vec3& vec, nlohmann::json& node);
		void Deserialize(glm::vec3& vec, nlohmann::json& node);

		void Serialize(const glm::mat4& mat, nlohmann::json& node);
		void Deserialize(glm::mat4& mat, nlohmann::json& node);
	}
}