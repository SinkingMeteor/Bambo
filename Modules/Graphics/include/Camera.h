#pragma once
#include "pch.h"
#include "glm.hpp"
#include "Rect.h"
#include "Transform.h"
#include "Vectors.h"
#include "Interfaces/ITransformable.h"

namespace Bambo
{
	enum class BAMBO_API CameraProjectionType
	{
		Orthographic,
		Perspective
	};

	class BAMBO_API Camera final
	{
	public:
		Camera();
		Camera(const Camera& camera) = default;
		Camera& operator=(const Camera& camera) = default;

		void SetViewportSize(uint32 width, uint32 height);
		const glm::mat4& GetProjectionMatrix();

		void SetProjectionType(CameraProjectionType projectionType) { m_projection = projectionType; m_isNeedToUpdate = true; }
		void SetOrthographicSize(float size) { m_orthoSize = size; m_isNeedToUpdate = true; }
		void SetFieldOfView(float fov) { m_fieldOfView = fov; m_isNeedToUpdate = true; }

		float GetOrthographicSize() const { return m_orthoSize; }
		float GetFieldOfView() const { return m_fieldOfView; }

	private:
		glm::mat4 m_projectionMatrix;
		CameraProjectionType m_projection;

		float m_aspectRatio;

		float m_orthoSize;
		float m_orthoNear;
		float m_orthoFar;

		float m_fieldOfView;
		float m_perspectiveNear;
		float m_perspectiveFar;

		bool m_isNeedToUpdate;
	};
}