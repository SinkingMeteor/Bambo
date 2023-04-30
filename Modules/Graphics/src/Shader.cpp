#include "Shader.h"

namespace Bambo 
{
	Shader::Shader() :
		m_shaderImplementation()
	{
		m_shaderImplementation = ShaderImplementation::CreateInternalShader();
	}
}