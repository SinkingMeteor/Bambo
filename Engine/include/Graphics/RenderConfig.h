#pragma once
#include "Core/Essentials.h"
#include "Graphics/Shader.h"
#include "Graphics/Transform.h"
#include "Graphics/Texture2D.h"
#include "Graphics/Camera.h"

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