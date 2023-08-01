#include "Audio/AudioDevice.h"
#include "Core/Log.h"
namespace Bambo
{
	AudioDevice::AudioDevice() :
		m_device(nullptr),
		m_context(nullptr)
	{
		m_device = alcOpenDevice(nullptr);

		if (!m_device)
		{
			Logger::Get()->Log("Audio device log", Verbosity::Error, "ERROR: %s", "Can't create an openAL device");
			return;
		}

		m_context = alcCreateContext(m_device, nullptr);
	
		if (!m_context)
		{
			Logger::Get()->Log("Audio device log", Verbosity::Error, "ERROR: %s", "Can't create an openAL context");
			return;
		}

		if (!alcMakeContextCurrent(m_context))
		{
			Logger::Get()->Log("Audio device log", Verbosity::Error, "ERROR: %s", "Can't set current openAL context");
			return;
		}
	}

	AudioDevice::~AudioDevice()
	{
		alcMakeContextCurrent(nullptr);
		if (m_context) alcDestroyContext(m_context);
		if (m_device) alcCloseDevice(m_device);
	}
}