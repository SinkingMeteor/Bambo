#include "Transform.h"

namespace Bambo 
{
	Transform::Transform() : Transform(glm::vec2(0.0f, 0.0f))
	{}

	Transform::Transform(const glm::vec2& position) : Transform(position, 0.0f, glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f))
	{}

	Transform::Transform(const glm::vec2& position, const glm::vec2& origin) : Transform(position, 0.0f, glm::vec2(1.0f, 1.0f), origin)
	{}

	Transform::Transform(const glm::vec2& position, float rotation) : Transform(position, rotation, glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f))
	{}

	Transform::Transform(const glm::vec2& position, float rotation, const glm::vec2& scale) : Transform(position, rotation, scale, glm::vec2(0.0f, 0.0f))
	{}

	Transform::Transform(const glm::vec2& position, float rotation, const glm::vec2& scale, const glm::vec2& origin) : 
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
			m_matrix = glm::mat4{ 1.0f };
			m_matrix = glm::translate(m_matrix, glm::vec3{ m_position.x + m_origin.x, m_position.y + m_origin.y, 0.0f });
			m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation), glm::vec3{ 0.0f, 0.0f, 1.0f });
			m_matrix = glm::scale(m_matrix, glm::vec3{ m_scale.x, m_scale.y, 1.0f });

			m_isNeedUpdate = false;
		}

		return m_matrix;
	}

	void Transform::SetPosition(const glm::vec2& position)
	{
		m_position = position;
		m_isNeedUpdate = true;
	}

	void Transform::AddToPosition(const glm::vec2& addPosition)
	{
		m_position += addPosition;
		m_isNeedUpdate = true;
	}

	void Transform::SetRotation(float angle)
	{
		m_rotation = angle;
		m_isNeedUpdate = true;
	}

	void Transform::AddRotation(float angle)
	{
		m_rotation += angle;
		m_isNeedUpdate = true;
	}

	void Transform::SetScale(const glm::vec2& scale)
	{
		m_scale = scale;
		m_isNeedUpdate = true;
	}

	void Transform::SetOrigin(const glm::vec2& origin)
	{
		m_origin = origin;
		m_isNeedUpdate = true;
	}
}