#include "MathSerialization.h"

namespace Bambo
{
	namespace Serialization
	{
		void Serialize(const glm::vec3& vec, nlohmann::json& node)
		{
			node["x"] = vec.x;
			node["y"] = vec.y;
			node["z"] = vec.z;
		}

		void Deserialize(glm::vec3& vec, nlohmann::json& node)
		{
			vec = glm::vec3
			{
				node["x"].get<float>(),
				node["y"].get<float>(),
				node["z"].get<float>()
			};
		}

		void Serialize(const glm::mat4& mat, nlohmann::json& node)
		{
			node["x0"] = mat[0].x;
			node["y0"] = mat[0].y;
			node["z0"] = mat[0].z;
			node["w0"] = mat[0].w;

			node["x1"] = mat[1].x;
			node["y1"] = mat[1].y;
			node["z1"] = mat[1].z;
			node["w1"] = mat[1].w;

			node["x2"] = mat[2].x;
			node["y2"] = mat[2].y;
			node["z2"] = mat[2].z;
			node["w2"] = mat[2].w;

			node["x3"] = mat[3].x;
			node["y3"] = mat[3].y;
			node["z3"] = mat[3].z;
			node["w3"] = mat[3].w;
		}

		void Deserialize(glm::mat4& mat, nlohmann::json& node)
		{
			mat = glm::mat4
			{
				node["x0"].get<float>(),
				node["y0"].get<float>(),
				node["z0"].get<float>(),
				node["w0"].get<float>(),

				node["x1"].get<float>(),
				node["y1"].get<float>(),
				node["z1"].get<float>(),
				node["w1"].get<float>(),

				node["x2"].get<float>(),
				node["y2"].get<float>(),
				node["z2"].get<float>(),
				node["w2"].get<float>(),

				node["x3"].get<float>(),
				node["y3"].get<float>(),
				node["z3"].get<float>(),
				node["w3"].get<float>()
			};
		}
	}
}