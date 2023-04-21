#pragma once
#include "pch.h"
#include "AL/al.h"
#include "ALCheck.h"
#include "glm.hpp"
#include "Audio.h"
#include "Utils.h"
namespace Bambo
{
	class BAMBO_API AudioSource
	{
	public:
		AudioSource();
		AudioSource(const AudioSource& source) = delete;
		AudioSource& operator=(const AudioSource& source) = delete;
		virtual ~AudioSource();

		void SetPitch(float value01);
		float GetPitch() const { return m_pitch; }

		void SetVolume(float value01);
		float GetVolume() const { return m_volume; }

		void SetLoop(bool isActive);
		bool IsLooping() const { return m_isLoop; }

		void SetPosiiton(const glm::vec2& newPosition);
		bool IsPlaying() const;

		virtual void Play() = 0;
		virtual void Stop() = 0;

	protected:
		ALuint m_sourceId;
		float m_pitch;
		float m_volume;
		bool m_isLoop;
	};
}