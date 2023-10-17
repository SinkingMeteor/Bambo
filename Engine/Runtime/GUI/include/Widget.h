#pragma once
#include "Essentials.h"
#include "Components/Component.h"
namespace Bambo
{
	class BAMBO_API Widget : public Component
	{
		COMPONENT_BODY(Widget)
	public:
		Widget();
		virtual ~Widget() = default;

		virtual void Update(float deltaTime) {}
		virtual void OnRender(const glm::mat4& ownerGlobalMatrix) override {}

		virtual void OnClick() {};
		virtual void OnHover() {};
		virtual void OnUnhover() {};
	protected:
		RectFloat m_rect;
	};
}