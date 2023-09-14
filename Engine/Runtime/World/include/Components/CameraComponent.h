#pragma once
#include "Essentials.h"
#include "Components/Component.h"
#include "Rect.h"
#include "Camera.h"

namespace Bambo
{
	struct BAMBO_API CameraComponent final : public Component
	{
		COMPONENT_BODY(CameraComponent)

		CameraComponent() = default;
		
		Camera* GetCamera() { return &m_camera; }
	private:
		Camera m_camera;

		virtual void Serialize(nlohmann::json& node) override;
		virtual void Deserialize(nlohmann::json& node) override;
		virtual void OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex) override;
	};


}