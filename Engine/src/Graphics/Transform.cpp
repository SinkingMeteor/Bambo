#include "Graphics/Transform.h"

namespace Bambo 
{
	Transform::Transform() : Transform(glm::vec3(0.0f))
	{}

	Transform::Transform(const glm::vec3& position) : Transform(position, glm::vec3{0.0f}, glm::vec3{1.0f}, glm::vec3{0.0f})
	{}

	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3& origin) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale),
		m_origin(origin),
		m_isNeedUpdate(true),
		m_matrix()
	{}

	glm::mat4& Transform::GetMatrix()
	{
		if (IsNeedUpdate()) 
		{
			glm::mat4 rotation{ glm::quat(m_rotation) };
			m_matrix = glm::translate(m_matrix, glm::vec3{ m_position.x + m_origin.x, m_position.y + m_origin.y, m_position.z + m_origin.z });
			m_matrix *= rotation;
			m_matrix = glm::scale(m_matrix, glm::vec3{ m_scale.x, m_scale.y, 1.0f });

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

	void Transform::SetOrigin(const glm::vec3& origin)
	{
		m_origin = origin;
		m_isNeedUpdate = true;
	}
}