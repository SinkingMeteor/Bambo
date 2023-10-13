#pragma once
#include "Essentials.h"
#include "Component.h"

namespace Bambo
{
	struct BAMBO_API Area2DComponent final : public Component
	{
		COMPONENT_BODY(Area2DComponent);

		Area2DComponent() = default;

		RectFloat* GetRectPtr() { return &m_rect; }
		glm::vec3* GetOriginPtr() { return &m_origin; }

		void SetOrigin(const glm::vec3& origin) { m_origin = origin; }
		void SetRect(const RectFloat& rect) { m_rect = rect; }

		glm::vec3 GetOriginOffset() const
		{
			return glm::vec3{ -m_rect.Width * m_origin.x, m_rect.Height * m_origin.y, 0.0f };
		}

		virtual void Serialize(nlohmann::json& node) override;
		virtual void Deserialize(nlohmann::json& node) override;

		virtual void OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex) override;
	private:
		RectFloat m_rect{ 0, 0, 200.0f, 200.0f };
		glm::vec3 m_origin{ 0.5f, 0.5f, 0.5f };
	};
}