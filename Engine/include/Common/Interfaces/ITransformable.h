#pragma once
#include "Common/Transform.h"
namespace Bambo 
{
	class ITransformable 
	{
	public:
		virtual Transform& GetTransform() = 0;
		virtual ~ITransformable() {}
	};
}