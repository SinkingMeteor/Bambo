#pragma once
#include "Essentials.h"
#include "Resource/ResourceProvider.h"
#include "Shader.h"

namespace Bambo
{
	struct BAMBO_API ShaderLoader final
	{
		using result_type = std::shared_ptr<Shader>;

		result_type operator()(const std::size_t id, const std::string& shaderPath) const
		{
			std::shared_ptr<Shader> shader = std::make_shared<Shader>(id);
			shader->LoadFromFile(shaderPath);
			return shader;
		}
	};

	using ShaderProvider = ResourceProvider<Shader, ShaderLoader>;
}