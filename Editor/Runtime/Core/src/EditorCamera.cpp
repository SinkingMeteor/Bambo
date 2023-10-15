#include "EditorCamera.h"
#include "World.h"
#include "Engine.h"

namespace BamboEditor
{
	EditorCamera::EditorCamera() :
		CameraComponent(),
		m_cameraSpeed(100.0f)
	{}

	void EditorCamera::Tick(float deltaSeconds)
	{
		Bambo::Engine* engine = m_owner->GetWorld()->GetWorldContext()->Engine;
		BAMBO_ASSERT_S(engine)

		Bambo::Input* input = engine->GetInputManager();
		BAMBO_ASSERT_S(input)

		Bambo::Transform* transform = m_owner->GetTransform();
		BAMBO_ASSERT_S(transform)

		glm::vec3 velocity{ 0.0f };
		if (input->IsKeyPressed(GLFW_KEY_W))
		{
			velocity.y -= m_cameraSpeed * deltaSeconds;
		}
		if (input->IsKeyPressed(GLFW_KEY_A))
		{
			velocity.x += m_cameraSpeed * deltaSeconds;
		}
		if (input->IsKeyPressed(GLFW_KEY_S))
		{
			velocity.y += m_cameraSpeed * deltaSeconds;
		}
		if (input->IsKeyPressed(GLFW_KEY_D))
		{
			velocity.x -= m_cameraSpeed * deltaSeconds;
		}

		transform->AddToPosition(velocity);
	}
}