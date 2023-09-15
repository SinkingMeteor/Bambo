#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"
#include "GUIWindow.h"
#include "Project.h"
#include "TextureProvider.h"
#include "Texture2D.h"
#include "EditorPaths.h"
#include "EditorContext.h"
#include "FileBrowserWidget.h"

namespace BamboEditor
{
	class ContentBrowserWindow final : public GUIWindow
	{
	public:
		ContentBrowserWindow(EditorContext* editorContext);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		EditorContext* m_editorContext;
		FileBrowserWidget m_fileBrowserWidget;
		std::string m_windowName;
		bool m_isOpenedSettingsPanel = false;
	
		void DrawContentTree();
		void DrawFolderContent();
		void DrawPath(const std::filesystem::path& pathToDraw, bool isDirectory);
	};
}