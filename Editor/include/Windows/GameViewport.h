#pragma once
#include "pch.h"
#include "GUIWindow.h"
#include "imgui.h"
#include "Framebuffer.h"
#include "WindowManager.h"

namespace BamboEditor
{
	class GameViewportWindow final : public GUIWindow
	{
	public:
		GameViewportWindow(SPtr<Bambo::Framebuffer> framebuffer);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() override { return m_windowName; }
	private:
		std::string m_windowName;
		SPtr<Bambo::Framebuffer> m_framebuffer;

		ImVec2 ResizeGameViewport();
	};
}