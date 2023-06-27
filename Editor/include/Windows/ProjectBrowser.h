#pragma once
#include "Essentials.h"
#include "Windows/GUIWindow.h"
#include "Project.h"
#include "imgui.h"
#include "Texture2D.h"
#include "TextureProvider.h"
#include "EditorPaths.h"

namespace BamboEditor
{
	class ProjectBrowserWindow final : public GUIWindow
	{
	public:
		ProjectBrowserWindow(WPtr<Project> currentProject, const std::function<void()>& onProjectLoadedCallback);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		WPtr<Project> m_currentProject;
		std::function<void()> m_onProjectLoadedCallback;
		std::string m_windowName;
		char m_newProjectName[32];
		std::filesystem::path m_rootDirectory;
		std::filesystem::path m_currentDirectory;

		SPtr<Bambo::Texture2D> m_fileIcon;
		SPtr<Bambo::Texture2D> m_folderIcon;

		float m_thumbnailSize;
		float m_padding;
		float m_sizeFactor;
		bool m_hasProjectAtDirectory;

		void CreateNewProject();
		void OpenProject(const std::filesystem::path& projFilePath);
	};
}