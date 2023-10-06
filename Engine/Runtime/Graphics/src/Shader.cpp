#include "Shader.h"
#include "Engine.h"

namespace Bambo 
{
	Shader::Shader(Engine* engine, const std::size_t assetId) :
		Resource(assetId, engine),
		m_shaderImplementation()
	{
		m_shaderImplementation = ShaderImplementation::CreateInternalShader(engine->GetRenderManager()->GetCurrentRenderAPI());
	}
}