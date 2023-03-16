#pragma once
#include "pch.h"
namespace Bambo 
{
	namespace Database 
	{
		namespace Paths 
		{
			std::size_t RESOURCE_PATH = std::hash<std::string>{}("Hello world!");
		}
	}
}