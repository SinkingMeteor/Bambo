#pragma once
#include "Essentials.h"
#include "Component.h"
#include "Font.h"
#include "Shader.h"
#include "Text.h"

namespace Bambo
{
	struct BAMBO_API TextComponent final : public Component
	{
		COMPONENT_BODY(TextComponent);

		TextComponent();

		int32& GetSortingOrderRef() { return m_sortingOrder; }
		void SetFont(SPtr<Font> font) { m_internalText.SetFont(font); }
		void SetText(const std::u32string& text) { m_internalText.SetText(text); }
		void SetText(const std::string& text) { m_internalText.SetText(text); }
		void SetSortingOrder(int32 sortingOrder) { m_sortingOrder = sortingOrder; }
		Text& GetInternalText() { return m_internalText; }

		virtual void OnRender(const glm::mat4& ownerGlobalMatrix) override;
		virtual void PostConstruct() override;
	private:
		Text m_internalText;
		SPtr<Shader> m_shader;
		int32 m_sortingOrder{ 0 };
	};
}