#pragma once
#include "Essentials.h"
#include "Resource/ResourceProvider.h"
#include "Shader.h"
#include "Engine.h"

namespace Bambo
{
	struct BAMBO_API ShaderLoader final
	{
		using result_type = std::shared_ptr<Shader>;

		result_type operator()(Engine* engine, const std::size_t id, const std::string& shaderPath) const
		{
			SPtr<Shader> shader = std::make_shared<Shader>(engine->GetRenderManager()->GetCurrentRenderAPI(), id);
			shader->LoadFromFile(shaderPath);
			return shader;
		}

	};

	using ShaderProvider = ResourceProvider<Shader, ShaderLoader>;
}