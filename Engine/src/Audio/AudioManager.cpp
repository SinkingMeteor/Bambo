#include "Audio/AudioManager.h"

namespace Bambo
{
	void AudioManager::Initialize()
	{
		m_device = new AudioDevice();
	}

	void AudioManager::Dispose()
	{
		delete m_device;
	}
}