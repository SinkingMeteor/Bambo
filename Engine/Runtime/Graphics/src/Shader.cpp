#include "Shader.h"

namespace Bambo 
{
	Shader::Shader(const std::size_t assetId) :
		m_assetId(assetId),
		m_shaderImplementation()
	{
		m_shaderImplementation = ShaderImplementation::CreateInternalShader();
	}
}