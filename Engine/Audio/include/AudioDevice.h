#pragma once
#include "pch.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "Utils.h"
namespace Bambo
{
	class BAMBO_API AudioDevice
	{
	public:
		AudioDevice();
		~AudioDevice();
	private:
		ALCdevice* m_device;
		ALCcontext* m_context;
	};
}