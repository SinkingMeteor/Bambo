#pragma once
#include "Core/Essentials.h"
#include "EditorEssentials.h"
#include "Windows/GUIWindow.h"
#include "Graphics/Framebuffer.h"
#include "Window/WindowManager.h"
#include "Core/Time/TimeManager.h"

namespace BamboEditor
{
	class GameViewportWindow final : public GUIWindow
	{
	public:
		GameViewportWindow(SPtr<Bambo::Framebuffer> framebuffer);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		std::string m_windowName;
		SPtr<Bambo::Framebuffer> m_framebuffer;
		bool m_isOpenedInfoPanel;

		ImVec2 ResizeGameViewport();
		void DrawInfoOverlay();
		void DrawMenuBar();
	};
}