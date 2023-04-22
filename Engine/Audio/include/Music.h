#pragma once
#include "pch.h"
#include "AudioSource.h"
#include "StreamingAudio.h"
#include "Utils.h"

namespace Bambo
{
	class BAMBO_API Music final : public AudioSource
	{
	public:
		Music();
		virtual void Play() override;
		virtual void Stop() override;
		virtual void SetLoop(bool isActive) override { m_isLoop = isActive; }
		void SetAudio(std::shared_ptr<StreamingAudio> streamingAudio);
		void Update();
	private:
		std::shared_ptr<StreamingAudio> m_currentAudio;
		std::size_t m_cursor;
	};
}