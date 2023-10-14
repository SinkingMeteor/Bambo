#include "Components/TextComponent.h"
#include "BaseSerialization.h"
#include "World.h"
#include "DrawDebugHelpers.h"
#include "BaseSerialization.h"

namespace Bambo
{
	TextComponent::TextComponent() :
		m_internalText(),
		m_shader(),
		m_sortingOrder()
	{}

	void TextComponent::PostConstruct()
	{
		Component::PostConstruct();

		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;
		m_internalText.SetFont(world->GetFontProvider()->Load(BamboPaths::EngineResourcesDir / BamboPaths::EngineDefaultFontPath_A));
		m_shader = world->GetShaderProvider()->Load(BamboPaths::EngineResourcesDir / BamboPaths::EngineDefaultFontShaderPath_A);
		SetText(u8"Привет, мир!");
	}

	void TextComponent::OnRender(const glm::mat4& ownerGlobalMatrix)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

#ifdef WITH_EDITOR
		RectFloat textArea = m_internalText.GetAreaRect();
		glm::vec4 selfWorldPos = ownerGlobalMatrix * glm::vec4{ 1.0f };

		textArea.Left = selfWorldPos.x;
		textArea.Top = selfWorldPos.y;

		DrawDebugRect(world, textArea, Color::Yellow());
#endif

		SpriteRenderer* renderer = world->GetSpriteRenderer();

		if (!m_internalText.GetFont()) return;

		const std::vector<GlyphRenderData>& textRenderData = m_internalText.GetTextData();

		for (size_t i = 0; i < textRenderData.size(); ++i)
		{
			SpriteRenderRequest request{};
			request.Texture = textRenderData[i].Texture;
			request.Rect = textRenderData[i].GlyphTexRect;
			request.SortingOrder = m_sortingOrder;
			request.Shader = m_shader;

			Vector3f glyphWorldPos = textRenderData[i].GlyphWorldPos;
			request.Model = glm::translate(ownerGlobalMatrix, { glyphWorldPos.X, glyphWorldPos.Y, glyphWorldPos.Z });

			renderer->EnqueueSpriteToRender(request);
		}
	}
}