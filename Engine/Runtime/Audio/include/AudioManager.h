#pragma once
#include "Essentials.h"
#include "AudioDevice.h"

namespace Bambo
{
	class AudioManager final
	{
	public:
		AudioManager() = default;
		AudioManager(const AudioManager&) = delete;
		AudioManager& operator=(const AudioManager&) = delete;

		void Initialize();
		void Dispose();
	private:
		AudioDevice* m_device;
	};
}