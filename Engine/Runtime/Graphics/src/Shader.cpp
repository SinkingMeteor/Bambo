#include "Shader.h"

namespace Bambo 
{
	Shader::Shader(const std::size_t assetId) :
		Resource(assetId),
		m_shaderImplementation()
	{
		m_shaderImplementation = ShaderImplementation::CreateInternalShader();
	}
}