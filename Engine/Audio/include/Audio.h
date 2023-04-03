#pragma once
#include "pch.h"
#include "AL/al.h"
namespace Bambo
{
	class BAMBO_API Audio
	{
	public:
		Audio(const Audio& audio) = delete;
		Audio& operator=(const Audio& audio) = delete;
		void LoadFromFile(const std::string& filePath);
	};
}