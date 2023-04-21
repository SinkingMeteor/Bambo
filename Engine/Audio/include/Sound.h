#pragma once
#include "pch.h"
#include "ALCheck.h"
#include "AudioSource.h"

namespace Bambo
{
	class BAMBO_API Sound : public AudioSource
	{
	public:
		Sound();

		void SetAudio(std::shared_ptr<Audio> audioResource);
		virtual void Play() override;
		virtual void Stop() override;

	private:
		std::shared_ptr<Audio> m_currentAudio;
	};
}