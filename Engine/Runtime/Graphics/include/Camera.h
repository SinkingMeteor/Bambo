#pragma once
#include "Essentials.h"
#include "Rect.h"
#include "Transform.h"
#include "Vectors.h"

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
		void SetAspectRatio(float a) { m_aspectRatio = a; m_isNeedToUpdate = true; }
		void SetOrthographicSize(float size) { m_orthoSize = size; m_isNeedToUpdate = true; }
		void SetOrthographicNear(float onear) { m_orthoNear = onear; m_isNeedToUpdate = true; }
		void SetOrthographicFar(float ofar) { m_orthoFar = ofar; m_isNeedToUpdate = true; }

		void SetFieldOfView(float fov) { m_fieldOfView = fov; m_isNeedToUpdate = true; }
		void SetPerspectiveNear(float pnear) { m_perspectiveNear = pnear; m_isNeedToUpdate = true; }
		void SetPerspectiveFar(float pfar) { m_perspectiveFar = pfar; m_isNeedToUpdate = true; }

		float GetOrthographicSize() const { return m_orthoSize; }
		float GetOrthoNear() const { return m_orthoNear; }
		float GetOrthoFar() const { return m_orthoFar; }

		float GetFieldOfView() const { return m_fieldOfView; }
		float GetPespectiveNear() const { return m_perspectiveNear; }
		float GetPespectiveFar() const { return m_perspectiveFar; }

		CameraProjectionType GetProjectionType() const { return m_projection; }

		float GetAspectRatio() const { return m_aspectRatio; }


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