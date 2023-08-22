#include "World/Components/CameraComponent.h"
#include "World/World.h"

namespace Bambo
{
	void CameraComponent::Serialize(nlohmann::json& node)
	{
		node["name"] = "CameraComponent";
		node["aspectRatio"] = m_camera.GetAspectRatio();
		node["projType"] = static_cast<int32>(m_camera.GetProjectionType());

		node["orthoSize"] = m_camera.GetOrthographicSize();
		node["orthoNear"] = m_camera.GetOrthoNear();
		node["orthoFar"] = m_camera.GetOrthoFar();

		node["fov"] = m_camera.GetFieldOfView();
		node["perspectiveNear"] = m_camera.GetPespectiveNear();
		node["perspectiveFar"] = m_camera.GetPespectiveFar();
	}

	void CameraComponent::Deserialize(nlohmann::json& node)
	{
		m_camera.SetProjectionType((node["projType"].get<CameraProjectionType>()));
		m_camera.SetOrthographicSize(node["orthoSize"].get<float>());
		m_camera.SetOrthographicNear(node["orthoNear"].get<float>());
		m_camera.SetOrthographicFar(node["orthoFar"].get<float>());
		m_camera.SetAspectRatio(node["aspectRatio"].get<float>());

		m_camera.SetFieldOfView(node["fov"].get<float>());
		m_camera.SetPerspectiveNear(node["perspectiveNear"].get<float>());
		m_camera.SetPerspectiveFar(node["perspectiveFar"].get<float>());
	}

	void CameraComponent::OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

		const glm::mat4& projMat = m_camera.GetProjectionMatrix();
		glm::mat4 viewMat = glm::inverse(m_owner->GetTransform()->GetMatrix());
		float height = m_camera.GetOrthographicSize();
		float width = m_camera.GetAspectRatio() * height;
		viewMat = glm::translate(viewMat, glm::vec3(width * 0.5f, height * 0.5f, 0.0f));

		world->GetRenderer()->SetProjViewMatrix(projMat * viewMat);
	}

}