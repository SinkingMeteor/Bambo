#pragma once
#include "pch.h"

namespace Bambo
{
	class BAMBO_API AudioListener
	{
	public:
		virtual float GetVolume() const = 0;
		~AudioListener() {}
	};
}