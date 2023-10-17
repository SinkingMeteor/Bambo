#pragma once
#include "Essentials.h"
#include "Components/Component.h"
namespace Bambo
{
	class BAMBO_API Widget : public Component
	{
		COMPONENT_BODY(Widget)
	public:
		Widget() = default;
		virtual ~Widget() = default;

		virtual void Update(float deltaTime) {}
		virtual void Draw() {}

		virtual void OnClick() {};
		virtual void OnHover() {};
		virtual void OnUnhover() {};
	};
}