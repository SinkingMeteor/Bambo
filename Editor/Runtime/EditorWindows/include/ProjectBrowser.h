#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"
#include "GUIWindow.h"
#include "Project.h"
#include "Texture2D.h"
#include "TextureProvider.h"
#include "EditorPaths.h"
#include "EditorContext.h"
#include "FileBrowserWidget.h"

namespace BamboEditor
{
	class ProjectBrowserWindow final : public GUIWindow
	{
	public:
		ProjectBrowserWindow(EditorContext* editorContext, const std::function<void()>& onProjectLoadedCallback);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		EditorContext* m_editorContext;
		FileBrowserWidget m_fileBrowserWidget;
		std::function<void()> m_onProjectLoadedCallback;
		std::string m_windowName;
		char m_newProjectName[32];
		std::vector<std::string> m_disksList;

		void CreateNewProject();
		void OpenProject(const std::filesystem::path& projFilePath);
		void OnFileClicked(const std::filesystem::path& filePath);
		void DrawDiskList();
		void DrawReturnArrow();
		void DrawCreateProject();
	};
}