#include "Graphics/Camera.h"

namespace Bambo
{
	Camera::Camera() : 
		m_projectionMatrix(),
		m_projection(CameraProjectionType::Orthographic),
		m_aspectRatio(0.0f),
		m_orthoSize(360.0f),
		m_orthoNear(-1.0f),
		m_orthoFar(1.0f),
		m_fieldOfView(glm::radians(45.0f)),
		m_perspectiveNear(0.01f),
		m_perspectiveFar(1000.0f),
		m_isNeedToUpdate(true)
	{}

	void Camera::SetViewportSize(uint32 width, uint32 height)
	{
		m_isNeedToUpdate = true;

		BAMBO_ASSERT_S(height != 0)

		m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	}

	const glm::mat4& Camera::GetProjectionMatrix()
	{
		if (!m_isNeedToUpdate) return m_projectionMatrix;

		m_isNeedToUpdate = false;

		if (m_projection == CameraProjectionType::Orthographic)
		{
			m_projectionMatrix = glm::ortho(0.0f, m_orthoSize * m_aspectRatio, m_orthoSize, 0.0f, m_orthoNear, m_orthoFar);

		}
		else
		{
			m_projectionMatrix = glm::perspective(-m_fieldOfView, m_aspectRatio, m_perspectiveNear, m_perspectiveFar);
		}

		return m_projectionMatrix;
	}
}