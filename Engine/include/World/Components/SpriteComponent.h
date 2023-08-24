#pragma once
#include "Core/Essentials.h"
#include "Graphics/Texture2D.h"
#include "World/Components/Component.h"

namespace Bambo
{
	struct BAMBO_API SpriteComponent final : public Component
	{
		COMPONENT_BODY(SpriteComponent);

		SpriteComponent();

		SPtr<Texture2D> GetTexture() const { return m_texture; }
		RectInt GetRect() const 
		{
			BAMBO_ASSERT_S(m_texture)
			return m_texture->GetTextureRects()[m_spriteRectIndex];
		}

		int32& GetRectIndexRef() { return m_spriteRectIndex; }
		int32& GetSortingOrderRef() { return m_sortingOrder; }
		glm::vec3& GetOriginRef() { return m_origin; }
		glm::vec3 GetOrigin() const { return m_origin; }
		glm::vec3 GetOriginOffset() const 
		{
			BAMBO_ASSERT_S(m_texture)
			RectInt texRect = m_texture->GetTextureRect();
			return glm::vec3{ -texRect.Width * m_origin.x, -texRect.Height * m_origin.y, 0.0f };
		}

		void SetOrigin(const glm::vec3& origin) { m_origin = origin; }
		void SetTexture(SPtr<Texture2D> texture) { m_texture = texture; }
		void SetRectIndex(int32 rectIndex) { m_spriteRectIndex = rectIndex; }
		void SetSortingOrder(int32 sortingOrder) { m_sortingOrder = sortingOrder; }

		virtual void Serialize(nlohmann::json& node) override;
		virtual void Deserialize(nlohmann::json& node) override;
		
		virtual void OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex) override;
		virtual void PostConstruct() override;
	private:
		SPtr<Texture2D> m_texture{ nullptr };
		glm::vec3 m_origin{ 0.5f, 0.5f, 0.5f };
		int32 m_spriteRectIndex{ 0 };
		int32 m_sortingOrder{ 0 };
	};
}