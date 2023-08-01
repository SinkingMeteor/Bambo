#pragma once
#include "Core/Essentials.h"
#include "Core/Color.h"

namespace Bambo 
{
	struct BAMBO_API QuadVertex
	{
		glm::vec3 Position{};
		glm::vec2 TexCoord{};
		Color Color{};
	};
}