#pragma once
#include "Essentials.h"
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

		template<>
		inline BAMBO_API void Serialize<RectFloat>(const RectFloat& val, nlohmann::json& node)
		{
			Serialize(val.Left, node["left"]);
			Serialize(val.Top, node["top"]);
			Serialize(val.Width, node["width"]);
			Serialize(val.Height, node["height"]);
		}

		template<>
		inline BAMBO_API RectFloat Deserialize<RectFloat>(nlohmann::json& node)
		{
			return RectFloat
			{
				Deserialize<float>(node["left"]),
				Deserialize<float>(node["top"]),
				Deserialize<float>(node["width"]),
				Deserialize<float>(node["height"])
			};
		}

		BAMBO_API void Serialize(const glm::mat4& mat, nlohmann::json& node);
		BAMBO_API void Deserialize(glm::mat4& mat, nlohmann::json& node);
	}
}