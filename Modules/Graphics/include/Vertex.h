#pragma once
#include "pch.h"
#include "Graphics.h"
#include "Color.h"

namespace Bambo 
{
	struct Vertex final
	{
		glm::vec2 Position{};
		glm::vec2 TexCoord{};
		Color Color{};
	};
}