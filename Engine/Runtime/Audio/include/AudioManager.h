#pragma once
#include "Essentials.h"
#include "SingletonManager.h"
#include "AudioDevice.h"

namespace Bambo
{
	class AudioManager : public ISingleton
	{
		SINGLETON_BODY(AudioManager, 'AUDM')
	public:
		void Initialize();
		void Dispose();
	private:
		AudioDevice* m_device;
	};
}