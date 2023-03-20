#pragma once
#include "pch.h"
#include "Graphics/Color.h"
namespace Bambo 
{
	struct Vertex 
	{
		glm::vec2 Position{};
		glm::vec2 TexCoord{};
		Color Color{};
	};
}