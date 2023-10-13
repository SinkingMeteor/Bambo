#include "Components/CameraComponent.h"
#include "BaseSerialization.h"
#include "World.h"

namespace Bambo
{
	void CameraComponent::Serialize(nlohmann::json& node)
	{
		Serialization::Serialize("CameraComponent", node["name"]);
		Serialization::Serialize(m_camera.GetAspectRatio(), node["aspectRatio"]);
		Serialization::Serialize(static_cast<int32>(m_camera.GetProjectionType()), node["projType"]);
		Serialization::Serialize(m_camera.GetOrthographicSize(), node["orthoSize"]);
		Serialization::Serialize(m_camera.GetOrthoNear(), node["orthoNear"]);
		Serialization::Serialize(m_camera.GetOrthoFar(), node["orthoFar"]);
		Serialization::Serialize(m_camera.GetFieldOfView(), node["fov"]);
		Serialization::Serialize(m_camera.GetPespectiveNear(), node["perspectiveNear"]);
		Serialization::Serialize(m_camera.GetPespectiveFar(), node["perspectiveFar"]);
	}

	void CameraComponent::Deserialize(nlohmann::json& node)
	{
		m_camera.SetProjectionType(Serialization::Deserialize<CameraProjectionType>(node["projType"]));
		m_camera.SetOrthographicSize(Serialization::Deserialize<float>(node["orthoSize"]));
		m_camera.SetOrthographicNear(Serialization::Deserialize<float>(node["orthoNear"]));
		m_camera.SetOrthographicFar(Serialization::Deserialize<float>(node["orthoFar"]));
		m_camera.SetAspectRatio(Serialization::Deserialize<float>(node["aspectRatio"]));
		m_camera.SetFieldOfView(Serialization::Deserialize<float>(node["fov"]));
		m_camera.SetPerspectiveNear(Serialization::Deserialize<float>(node["perspectiveNear"]));
		m_camera.SetPerspectiveFar(Serialization::Deserialize<float>(node["perspectiveFar"]));
	}

	void CameraComponent::OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex)
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