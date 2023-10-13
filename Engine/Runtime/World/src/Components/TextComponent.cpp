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

	void TextComponent::OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

		glm::mat4 objectPos = globals[ownerMatIndex];

#ifdef WITH_EDITOR
		RectFloat textArea = m_internalText.GetAreaRect();
		glm::vec4 selfWorldPos = objectPos * glm::vec4{ 1.0f };

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
			request.Model = glm::translate(objectPos, { glyphWorldPos.X, glyphWorldPos.Y, glyphWorldPos.Z });

			renderer->EnqueueSpriteToRender(request);
		}
	}

	void TextComponent::Serialize(nlohmann::json& node)
	{
		Serialization::Serialize("TextComponent", node["name"]);
		Serialization::Serialize(m_internalText.GetFont()->GetAssetInstanceID(), node["fontID"]);
		Serialization::Serialize(m_internalText.GetTextSize(), node["textSize"]);
		Serialization::Serialize(m_internalText.GetText8(), node["text"]);
		Serialization::Serialize(m_sortingOrder, node["sortingOrder"]);
	}

	void TextComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		m_internalText.SetSize(Serialization::Deserialize<uint32>(node["textSize"]));
		m_internalText.SetText(Serialization::Deserialize<std::string>(node["text"]));
		m_sortingOrder = Serialization::Deserialize<int32>(node["sortingOrder"]);

		World* world = m_owner->GetWorld();
		FontProvider* fontProvider = world->GetFontProvider();

		std::size_t assetId = Serialization::Deserialize<std::size_t>(node["fontID"]);
		m_internalText.SetFont(fontProvider->Load(assetId));
	}
}