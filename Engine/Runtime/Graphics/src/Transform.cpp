#include "Transform.h"
#include "BMath.h"
namespace Bambo 
{
	Transform::Transform() : Transform(glm::vec3{ 0.0f })
	{}

	Transform::Transform(const glm::vec3& position) : Transform(position, glm::vec3{0.0f}, glm::vec3{1.0f})
	{}

	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale),
		m_isNeedUpdate(true),
		m_matrix()
	{}

	glm::mat4& Transform::GetMatrix()
	{
		if (IsNeedUpdate()) 
		{
			glm::vec3 radVec = m_rotation * BMath::DEG2RAD;
			glm::mat4 rotationMat{ glm::quat(radVec)};
			m_matrix = glm::translate(glm::mat4{1.0f}, m_position);
			m_matrix = m_matrix * rotationMat;
			m_matrix = glm::scale(m_matrix, glm::vec3{ m_scale.x, m_scale.y, m_scale.z });

			m_isNeedUpdate = false;
		}

		return m_matrix;
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		m_position = position;
		m_isNeedUpdate = true;
	}

	void Transform::AddToPosition(const glm::vec3& addPosition)
	{
		m_position += addPosition;
		m_isNeedUpdate = true;
	}

	void Transform::SetRotation(const glm::vec3& angle)
	{
		m_rotation = angle;
		m_isNeedUpdate = true;
	}

	void Transform::AddRotation(const glm::vec3& angle)
	{
		m_rotation += angle;
		m_isNeedUpdate = true;
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_scale = scale;
		m_isNeedUpdate = true;
	}

}