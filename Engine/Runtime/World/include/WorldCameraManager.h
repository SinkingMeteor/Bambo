#pragma once
#include "Essentials.h"
namespace Bambo
{
	class BAMBO_API WorldCameraManager final
	{
	public:
		WorldCameraManager() : m_projectionMatrix(1.0f), m_viewMatrix(1.0f) {}

		void SetViewMatrix(const glm::mat4& mat) { m_viewMatrix = mat; }
		const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
		void SetProjectionMatrix(const glm::mat4& mat) { m_projectionMatrix = mat; }
		const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }

	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
	};
}