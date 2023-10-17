#pragma once
#include "Essentials.h"
#include "Texture2D.h"
#include "Components/Component.h"
#include "Sprite.h"

namespace Bambo
{
	struct BAMBO_API SpriteComponent final : public Component
	{
		COMPONENT_BODY(SpriteComponent);

		SpriteComponent();

		Sprite& GetSprite() { return m_sprite; }
		int32& GetSortingOrderRef() { return m_sortingOrder; }
		void SetSortingOrder(int32 sortingOrder) { m_sortingOrder = sortingOrder; }

		virtual void Serialize(nlohmann::json& node) override;
		virtual void Deserialize(nlohmann::json& node) override;
		
		virtual void OnRender(const glm::mat4& ownerGlobalMatrix) override;
		virtual void PostConstruct() override;
	private:
		Sprite m_sprite;
		int32 m_sortingOrder{ 0 };
	};
}