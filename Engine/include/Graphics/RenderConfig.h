#pragma once
#include "pch.h"
#include "Graphics/Shader.h"
#include "Common/Transform.h"
#include "Graphics/Texture2D.h"

namespace Bambo 
{
	enum class BAMBO_API PrimitiveType 
	{
		Triangle = GL_TRIANGLES,
		TriangleStrip = GL_TRIANGLE_STRIP
	};

	struct BAMBO_API RenderConfig 
	{
	public:
		RenderConfig() : 
			Primitive(PrimitiveType::TriangleStrip),
			ModelMatrix(Matrix::Identity()),
			Texture(nullptr),
			Shader(nullptr)
		{}

		PrimitiveType Primitive{PrimitiveType::TriangleStrip};
		Matrix ModelMatrix{};
		std::shared_ptr<Texture2D> Texture;
		std::shared_ptr<Shader> Shader;
	};
}