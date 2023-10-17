#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"
#include "GUIWindow.h"
#include "Framebuffer.h"
#include "WindowManager.h"
#include "Time/TimeManager.h"

namespace BamboEditor
{
	class EditorContext;

	class GameViewportWindow final : public GUIWindow
	{
	public:
		GameViewportWindow(EditorContext* editorContext, SPtr<Bambo::Framebuffer> framebuffer);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		std::string m_windowName;
		SPtr<Bambo::Framebuffer> m_framebuffer;
		EditorContext* m_editorContext;
		float m_mouseScrollFactor = 1.0f;
		bool m_isOpenedInfoPanel;

		ImVec2 ResizeGameViewport();
		void DrawInfoOverlay();
		void DrawMenuBar();
		void ProcessCameraMovement();
		void DrawSelectedItemRhombus();
	};
}