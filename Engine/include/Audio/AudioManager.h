#pragma once
#include "Core/Essentials.h"
#include "Core/SingletonManager.h"
#include "Audio/AudioDevice.h"

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