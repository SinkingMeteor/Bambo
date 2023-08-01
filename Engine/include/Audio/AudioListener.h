#pragma once
#include "pch.h"
#include "AL/al.h"
#include "ALCheck.h"
#include "AudioDevice.h"
#include "glm.hpp"
namespace Bambo
{
	class BAMBO_API AudioListener final
	{
	public:
		AudioListener(std::shared_ptr<AudioDevice> device);
		AudioListener(const AudioListener& listener) = delete;
		AudioListener& operator=(const AudioListener& listener) = delete;

		void SetPosition(const glm::vec2& position);
		glm::vec2 GetPosition() const;

		void SetOrientation(const glm::vec3& upVector, const glm::vec3& direction);
		void SetVolume(float value01);
	private:
		std::shared_ptr<AudioDevice> m_device;
	};
}