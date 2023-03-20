#include "Common/Transform.h"

namespace Bambo 
{
	Matrix::Matrix(float a00, float a01, float a02,
					float a10, float a11, float a12,
					float a20, float a21, float a22) :
		m_matrix{ a00, a10, 0.f, a20,
				   a01, a11, 0.f, a21,
				   0.f, 0.f, 1.f, 0.f,
				   a02, a12, 0.f, a22 }
	{}

	Transform::Transform() : Transform(glm::vec2(0.0f, 0.0f))
	{}

	Transform::Transform(const glm::vec2& position) : Transform(position, 0.0f, glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f))
	{}

	Transform::Transform(const glm::vec2& position, const glm::vec2& origin) : Transform(position, 0.0f, glm::vec2(0.0f, 0.0f), origin)
	{}

	Transform::Transform(const glm::vec2& position, float rotation) : Transform(position, rotation, glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f))
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

	Matrix& Transform::GetMatrix()
	{
		if (IsNeedUpdate()) 
		{
			float angle = -DegToRad(m_rotation);
			float cosine = std::cos(angle);
			float sine = std::sin(angle);
			float sxc = m_scale.x * cosine;
			float syc = m_scale.y * cosine;
			float sxs = m_scale.x * sine;
			float sys = m_scale.y * sine;
			float tx = -m_origin.x * sxc - m_origin.y * sys + m_position.x;
			float ty = m_origin.x * sxs - m_origin.y * syc + m_position.y;

			m_matrix = Matrix{ sxc, sys, tx, -sxs, syc, ty, 0.0f, 0.0f, 1.0f };
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