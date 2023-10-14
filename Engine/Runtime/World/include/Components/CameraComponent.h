#pragma once
#include "Essentials.h"
#include "Components/Component.h"
#include "Rect.h"
#include "Camera.h"

namespace Bambo
{
	struct BAMBO_API CameraComponent : public Component
	{
		COMPONENT_BODY(CameraComponent)

		CameraComponent() = default;
		
		Camera* GetCamera() { return &m_camera; }
	private:
		Camera m_camera;

		virtual void OnRender(const glm::mat4& ownerGlobalMatrix) override;
	};


}