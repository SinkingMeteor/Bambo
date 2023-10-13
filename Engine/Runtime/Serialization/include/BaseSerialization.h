#pragma once
#include "pch.h"
#include "glm.hpp"

namespace Bambo
{
	namespace Serialization
	{
		template<typename T>
		inline BAMBO_API void Serialize(const T& val, nlohmann::json& node)
		{
			node = val;
		}

		template<typename T>
		inline BAMBO_API T Deserialize(nlohmann::json& node)
		{
			return node.get<T>();
		}

		template<>
		inline BAMBO_API void Serialize<glm::vec3>(const glm::vec3& val, nlohmann::json& node)
		{
			Serialize(val.x, node["x"]);
			Serialize(val.y, node["y"]);
			Serialize(val.z, node["z"]);
		}

		template<>
		inline BAMBO_API glm::vec3 Deserialize<glm::vec3>(nlohmann::json& node)
		{
			return glm::vec3
			{
				Deserialize<float>(node["x"]),
				Deserialize<float>(node["y"]),
				Deserialize<float>(node["z"])
			};
		}

		BAMBO_API void Serialize(const glm::mat4& mat, nlohmann::json& node);
		BAMBO_API void Deserialize(glm::mat4& mat, nlohmann::json& node);
	}
}