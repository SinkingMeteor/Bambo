#pragma once
#include "pch.h"
#include "ALCheck.h"

namespace Bambo
{
	bool CalculateAudioFormat(int channels, int bps, ALenum& format);
}