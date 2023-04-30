#pragma once
#include "pch.h"
#include "Graphics.h"
#include "Color.h"

namespace Bambo 
{
	struct BAMBO_API Vertex
	{
		glm::vec2 Position{};
		glm::vec2 TexCoord{};
		Color Color{};
	};
}