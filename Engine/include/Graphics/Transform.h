#pragma once 
#include "Core/Essentials.h"

namespace Bambo 
{
	class BAMBO_API Transform 
	{
	public:
		Transform();
		Transform(const glm::vec3& position);
		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3& origin);

		glm::vec3& GetPositionRef() { return m_position; m_isNeedUpdate = true; }
		glm::vec3& GetRotationRef() { return m_rotation; m_isNeedUpdate = true; }
		glm::vec3& GetScaleRef() { return m_scale; m_isNeedUpdate = true; }
		glm::vec3& GetOriginRef() { return m_origin; m_isNeedUpdate = true; }

		glm::vec3 GetPosition() const { return m_position; }
		glm::vec3 GetRotation() const { return m_rotation; }
		glm::vec3 GetScale() const { return m_scale; }
		glm::vec3 GetOrigin() const { return m_origin; }

		glm::mat4& GetMatrix();

		bool IsNeedUpdate() const { return m_isNeedUpdate; }

		void SetPosition(const glm::vec3& position);
		void AddToPosition(const glm::vec3& addPosition);
		void SetRotation(const glm::vec3& rotation);
		void AddRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);
		void SetOrigin(const glm::vec3& origin);

	private:
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
		glm::vec3 m_origin;

		bool m_isNeedUpdate;

		glm::mat4 m_matrix;
	};
}