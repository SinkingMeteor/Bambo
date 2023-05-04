#include "Camera.h"

namespace Bambo
{
	Camera::Camera() : 
		m_transform(),
		m_projViewMatrix(),
		m_size(glm::vec2{640.0f, 360.0f})
	{
		m_transform.SetOrigin(GetHalfOfCameraSize());
	}

	Camera::Camera(const RectFloat& cameraRect) :
		m_transform(),
		m_projViewMatrix(),
		m_size(glm::vec2(cameraRect.Width, cameraRect.Height))
	{
		m_transform.SetPosition(glm::vec2(cameraRect.Left, cameraRect.Top));
		m_transform.SetOrigin(GetHalfOfCameraSize());
	}

	Camera::Camera(const glm::vec2& center, const glm::vec2& size) :
		m_transform(),
		m_projViewMatrix(),
		m_size(size)
	{
		m_transform.SetPosition(glm::vec2(center.x - size.x * 0.5f, center.y - size.y * 0.5f));
		m_transform.SetOrigin(GetHalfOfCameraSize());
	}

	void Camera::SetRect(const RectFloat& cameraRect)
	{
		m_transform.SetPosition(glm::vec2(cameraRect.Left, cameraRect.Top));
		m_transform.SetOrigin(GetHalfOfCameraSize());
	}

	glm::vec2 Camera::GetCameraCenter() const
	{
		return m_transform.GetPosition() + m_transform.GetOrigin();
	}

	glm::vec2 Camera::GetCameraSize() const
	{
		return m_size;
	}

	RectFloat Camera::GetCameraRect() const
	{
		glm::vec2 camPosition = m_transform.GetPosition();
		return RectFloat(camPosition.x, camPosition.y, m_size.x, m_size.y);
	}

	void Camera::Zoom(float factor)
	{
		glm::vec2 oldSize = m_size;
		m_size *= factor;
		glm::vec2 deltaSize = oldSize - m_size;
		m_transform.AddToPosition(deltaSize);
		m_transform.SetOrigin(GetHalfOfCameraSize());
	}

	Transform& Camera::GetTransform()
	{
		return m_transform;
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		const float aspectRatio = m_size.x / m_size.y;
		return glm::ortho(0.0f, m_size.x, m_size.y, 0.0f, -1.0f, 1.0f);
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::inverse(m_transform.GetMatrix());
	}

	glm::mat4 Camera::GetProjViewMatrix()
	{
		if (m_transform.IsNeedUpdate())
		{
			m_projViewMatrix = GetProjectionMatrix() * GetViewMatrix();
		}

		return m_projViewMatrix;
	}
}