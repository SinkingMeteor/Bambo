#pragma once
#include "pch.h"
#include "Common/Resource/ResourceProvider.h"
#include "Graphics/Shader.h"

namespace Bambo
{
	struct BAMBO_API ShaderLoader
	{
		using result_type = std::shared_ptr<Shader>;

		result_type operator()(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) const
		{
			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			shader->LoadFromFile(vertexShaderPath, fragmentShaderPath);
			return shader;
		}
	};

	using ShaderProvider = ResourceProvider<Shader, ShaderLoader>;
}