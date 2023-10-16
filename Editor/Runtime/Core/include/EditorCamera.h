#pragma once
#include "Essentials.h"
#include "Components/CameraComponent.h"

namespace BamboEditor
{
	class EditorCamera final : public Bambo::CameraComponent
	{
		COMPONENT_BODY(EditorCamera)

	public:
		EditorCamera();
		virtual void Tick(float deltaSeconds) override;

		float& GetCameraSpeedRef() { return m_cameraSpeed; }
		float GetCameraSpeed() const { return m_cameraSpeed; }
		void SetCameraSpeed(float speed) { m_cameraSpeed = speed; }

		void SetMovementEnabled(bool isEnabled) { m_movementEnabled = isEnabled; }

	private:
		float m_cameraSpeed;
		bool m_movementEnabled;
	};
}