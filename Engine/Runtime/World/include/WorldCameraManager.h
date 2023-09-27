#pragma once
#include "Essentials.h"
namespace Bambo
{
	class BAMBO_API WorldCameraManager final
	{
	public:
		WorldCameraManager() : m_projViewMatrix(1.0f) {}

		void SetProjViewMatrix(const glm::mat4& mat) { m_projViewMatrix = mat; }
		const glm::mat4& GetProjViewMatrix() const { return m_projViewMatrix; }

	private:
		glm::mat4 m_projViewMatrix;
	};
}