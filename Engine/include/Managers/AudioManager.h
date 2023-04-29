#pragma once
#include "engpch.h"
#include "Managers/Singleton.h"
#include "AudioDevice.h"

namespace Bambo
{
	class AudioManager : public Singleton<AudioManager>
	{
	public:
		void Initialize();
		void Dispose();
	private:
		AudioDevice* m_device;
	};
}