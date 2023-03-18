#include "pch.h"
#include "Graphics/Shader.h"
#include "Common/Transform.h"
#include "Graphics/Texture2D.h"

namespace Bambo 
{
	enum class PrimitiveType 
	{
		Triangle = GL_TRIANGLES,
		Quads = GL_QUADS
	};

	struct BAMBO_API RenderConfig 
	{
	public:
		RenderConfig() = default;
		RenderConfig& RenderConfig(const RenderConfig& config) = default;
		RenderConfig& operator=(const RenderConfig& config) = default;

		PrimitiveType Primitive{PrivitiveType::Quads};
		Matrix ModelMatrix;
		std::shared_ptr<Texture2D> Texture;
		std::shared_ptr<Shader> Shader;
	};
}