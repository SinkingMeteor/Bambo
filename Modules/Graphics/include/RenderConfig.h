#pragma once
#include "pch.h"
#include "Graphics.h"
#include "Shader.h"
#include "Transform.h"
#include "Texture2D.h"
#include "Camera.h"

namespace Bambo 
{
	enum class BAMBO_API PrimitiveType 
	{
		Triangle = GL_TRIANGLES,
		TriangleStrip = GL_TRIANGLE_STRIP
	};

	struct BAMBO_API RenderConfig final 
	{
	public:
		PrimitiveType Primitive;
		std::shared_ptr<Shader> Shader;
	
		RenderConfig() :
			Primitive(PrimitiveType::TriangleStrip),
			Shader(nullptr)
		{}
	};
}