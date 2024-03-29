#pragma once
#include "Essentials.h"
#include "AL/al.h"
#include "AL/alc.h"
namespace Bambo
{
	class BAMBO_API AudioDevice final
	{
	public:
		AudioDevice();
		AudioDevice(const AudioDevice& device) = delete;
		AudioDevice& operator=(const AudioDevice& device) = delete;
		~AudioDevice();

	private:
		ALCdevice* m_device;
		ALCcontext* m_context;

		friend class AudioListener;
	};
}