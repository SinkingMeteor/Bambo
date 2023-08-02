#pragma once

namespace BamboEditor
{
	class Widget
	{
	public:
		Widget() = default;
		virtual ~Widget() = default;
		virtual void Draw() = 0;
	};
}