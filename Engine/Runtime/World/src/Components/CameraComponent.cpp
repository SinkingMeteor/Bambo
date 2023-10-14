#include "Components/CameraComponent.h"
#include "BaseSerialization.h"
#include "World.h"

namespace Bambo
{
	void CameraComponent::OnRender(const glm::mat4& ownerGlobalMatrix)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

		const glm::mat4& projMat = m_camera.GetProjectionMatrix();

		float height = m_camera.GetOrthographicSize();
		float width = m_camera.GetAspectRatio() * height;
		const glm::vec3 cameraOffset = glm::vec3(width * 0.5f, height * 0.5f, 0.0f);

		m_owner->GetTransform()->AddToPosition(cameraOffset);
		glm::mat4 viewMat = m_owner->GetTransform()->GetMatrix();
		m_owner->GetTransform()->AddToPosition(-cameraOffset);

		viewMat = projMat * viewMat;
		world->GetCameraManager()->SetProjViewMatrix(viewMat);
	}

}