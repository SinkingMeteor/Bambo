#pragma once
#include "pch.h"
#include "GUIWindow.h"
#include "Project.h"
#include "imgui.h"
#include "TextureProvider.h"
#include "Texture2D.h"
#include "Utils.h"
#include "EditorPaths.h"
#include "EditorContext.h"

namespace BamboEditor
{
	class ContentBrowserWindow final : public GUIWindow
	{
	public:
		ContentBrowserWindow(EditorContext* editorContext);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		std::string m_windowName;
		std::filesystem::path m_currentDirectory;
		std::filesystem::path m_rootDirectory;

		SPtr<Bambo::Texture2D> m_fileIcon;
		SPtr<Bambo::Texture2D> m_folderIcon;

		float m_thumbnailSize = 32.0f;
		float m_padding = 16.0f;

		bool m_isOpenedSettingsPanel = false;
	
		void DrawSettingsOverlay();
	};
}