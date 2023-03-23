#pragma once 
#include "pch.h"
#include "Graphics.h"
#include "Utils.h"

namespace Bambo 
{
	class BAMBO_API Matrix 
	{
	public:
		Matrix() = default;
		Matrix(const glm::mat4& mat) : m_matrix(mat) {}
		Matrix(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);
		glm::mat4 GetInternalMatrix() const { return m_matrix; }
		static const glm::mat4 Identity();
	private:
		glm::mat4 m_matrix;
	};

	class BAMBO_API Transform 
	{
	public:
		Transform();
		Transform(const glm::vec2& position);
		Transform(const glm::vec2& position, const glm::vec2& origin);
		Transform(const glm::vec2& position, float rotation);
		Transform(const glm::vec2& position, float rotation, const glm::vec2& scale);
		Transform(const glm::vec2& position, float rotation, const glm::vec2& scale, const glm::vec2& origin);

		glm::vec2 GetPosition() const { return m_position; }
		float GetRotation() const { return m_rotation; }
		glm::vec2 GetScale() const { return m_scale; }
		glm::vec2 GetOrigin() const { return m_origin; }
		Matrix& GetMatrix();

		bool IsNeedUpdate() const { return m_isNeedUpdate; }

		void SetPosition(const glm::vec2& position);
		void AddToPosition(const glm::vec2& addPosition);
		void SetRotation(float angle);
		void AddRotation(float angle);
		void SetScale(const glm::vec2& scale);
		void SetOrigin(const glm::vec2& origin);

	private:
		glm::vec2 m_position;
		float m_rotation;
		glm::vec2 m_scale;

		glm::vec2 m_origin;
		bool m_isNeedUpdate;

		Matrix m_matrix;
	};
}