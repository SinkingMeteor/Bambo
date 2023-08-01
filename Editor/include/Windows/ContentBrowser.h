#pragma once
#include "Core/Essentials.h"
#include "EditorEssentials.h"
#include "GUIWindow.h"
#include "Project.h"
#include "Graphics/TextureProvider.h"
#include "Graphics/Texture2D.h"
#include "EditorPaths.h"
#include "EditorContext.h"

namespace BamboEditor
{
	class ContentBrowserWindow final : public GUIWindow
	{
	public:
		ContentBrowserWindow(EditorContext* editorContext, SPtr<Bambo::Texture2D> fileIcon, SPtr<Bambo::Texture2D> folderIcon);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		std::string m_windowName;
		std::filesystem::path m_currentDirectory;
		std::filesystem::path m_rootDirectory;

		std::string m_selectedContentItem;

		SPtr<Bambo::Texture2D> m_fileIcon;
		SPtr<Bambo::Texture2D> m_folderIcon;

		float m_itemScale = 24.0f;
		int32 m_columnsCount = 1;

		bool m_isOpenedSettingsPanel = false;
	
		void DrawSettingsOverlay();
		void DrawContentTree();
		void DrawFolderContent();
		void DrawPath(const std::filesystem::path& pathToDraw, bool isDirectory);
	};
}