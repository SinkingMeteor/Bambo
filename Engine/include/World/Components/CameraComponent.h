#pragma once
#include "Core/Essentials.h"
#include "World/Components/Component.h"
#include "Graphics/Rect.h"
#include "Graphics/Camera.h"

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
		virtual void Tick(float deltaSeconds) override;
	};


}