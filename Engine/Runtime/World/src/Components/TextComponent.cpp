#include "Components/TextComponent.h"
#include "MathSerialization.h"
#include "World.h"
#include "DrawDebugHelpers.h"

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
		SetText("Hello world");
	}

	void TextComponent::OnRender(std::vector<glm::mat4>& globals, int32 ownerMatIndex)
	{
		if (!m_owner) return;

		World* world = m_owner->GetWorld();
		if (!world) return;

		RectFloat textArea = m_internalText.GetAreaRect();
		glm::vec3 selfWorldPos = m_owner->GetTransform()->GetPosition();
		textArea.Left = selfWorldPos.x;
		textArea.Top = selfWorldPos.y;

		DrawDebugRect(world, textArea, Color::Yellow());

		SpriteRenderer* renderer = world->GetSpriteRenderer();

		if (!m_internalText.GetFont()) return;

		const std::vector<GlyphRenderData>& textRenderData = m_internalText.GetTextData();

		glm::mat4 objectPos = globals[ownerMatIndex];

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
		node["name"] = "TextComponent";
		node["fontID"] = m_internalText.GetFont()->GetAssetInstanceID();
		node["textSize"] = m_internalText.GetTextSize();
		node["text"] = m_internalText.GetText();
		node["sortingOrder"] = m_sortingOrder;
	}

	void TextComponent::Deserialize(nlohmann::json& node)
	{
		BAMBO_ASSERT_S(m_owner)
		BAMBO_ASSERT_S(m_owner->IsValid())
		BAMBO_ASSERT_S(m_owner->GetWorld())

		m_internalText.SetSize(node["textSize"].get<uint32>());
		m_internalText.SetText(node["text"].get<std::u32string>());
		m_sortingOrder = node["sortingOrder"].get<int32>();

		World* world = m_owner->GetWorld();
		FontProvider* fontProvider = world->GetFontProvider();
		std::size_t assetId = node["fontID"].get<std::size_t>();
		m_internalText.SetFont(fontProvider->Load(assetId));
	}
}