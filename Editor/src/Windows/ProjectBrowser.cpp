#include "Windows/ProjectBrowser.h"

namespace
{
	const std::string TARGET_EXTENSION = "bambo";
}

DECLARE_LOG_CATEGORY_STATIC(ProjectBrowserLog)

namespace BamboEditor
{
	ProjectBrowserWindow::ProjectBrowserWindow(EditorContext* editorContext, const std::function<void()>& onProjectLoadedCallback) :
		m_editorContext(editorContext),
		m_fileBrowserWidget(),
		m_onProjectLoadedCallback(onProjectLoadedCallback),
		m_windowName("Project Browser"),
		m_newProjectName(),
		m_disksList()
	{
		Bambo::GetAvalaibleDisks(m_disksList);
		BAMBO_ASSERT_S(m_disksList.size > 0)
		m_fileBrowserWidget.SetRootPath(m_disksList[0]);
		m_fileBrowserWidget.OnFileClick().Bind(*this, &ProjectBrowserWindow::OnFileClicked);
	}

	void ProjectBrowserWindow::OnGUI()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 viewportSize = viewport->Size;
		ImVec2 windowPos{ 0.0f, 0.0f };

		ImGui::SetNextWindowSize(viewportSize);
		ImGui::SetNextWindowPos(windowPos);

		ImGui::Begin(m_windowName.c_str(), nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);
		ImGui::Text(m_fileBrowserWidget.GetCurrentPath().string().c_str());

		DrawDiskList();
		DrawReturnArrow();
		DrawCreateProject();

		m_fileBrowserWidget.Draw();

		ImGui::End();
	}

	void ProjectBrowserWindow::OnFileClicked(const std::filesystem::path& filePath)
	{
		bool isProject = Bambo::HasExtension(filePath.filename().string(), TARGET_EXTENSION);
		if (isProject)
		{
			OpenProject(filePath);
		}
	}

	void ProjectBrowserWindow::DrawCreateProject()
	{
		if (!m_fileBrowserWidget.HasFileWithExtension(TARGET_EXTENSION))
		{
			ImGui::SameLine(0.0f, 25.0f);

			ImGui::Text("Project Name: ");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(200.0f);
			ImGui::PushID("Project Name");
			ImGui::InputText("", m_newProjectName, 32);
			ImGui::PopID();
			ImGui::SameLine(0.0f, 25.0f);
			if (ImGui::Button("Create New Here"))
			{
				CreateNewProject();
			}
		}
	}

	void ProjectBrowserWindow::DrawDiskList()
	{
		static int currentDisk = 0;
		int prevDisk = currentDisk;

		std::vector<const char*> disks{};
		disks.reserve(m_disksList.size());

		for (size_t i = 0; i < m_disksList.size(); ++i)
		{
			disks.push_back(m_disksList[i].c_str());
		}

		ImGui::SetNextItemWidth(50.0f);
		ImGui::PushID("Disks");
		ImGui::ListBox("", &currentDisk, disks.data(), disks.size(), 1);
		ImGui::PopID();

		if (currentDisk != prevDisk)
		{
			m_fileBrowserWidget.SetRootPath(m_disksList[currentDisk]);
		}
	}

	void ProjectBrowserWindow::DrawReturnArrow()
	{
		if (!m_fileBrowserWidget.IsOnRootPath())
		{
			ImGui::SameLine();

			if (ImGui::Button("<-"))
			{
				m_fileBrowserWidget.ToParentPath();
			}
		}
	}


	void ProjectBrowserWindow::CreateNewProject()
	{
		std::filesystem::path newProjectFullPath = m_fileBrowserWidget.GetCurrentPath() / (m_newProjectName + PROJECT_EXTENSION_DOT);
		Project::CreateNewProjectFile(newProjectFullPath);
		OpenProject(newProjectFullPath);
	}

	void ProjectBrowserWindow::OpenProject(const std::filesystem::path& projFilePath)
	{
		BAMBO_ASSERT_S(m_onProjectLoadedCallback)

		if (!m_editorContext->CurrentProject->OpenProject(projFilePath))
		{
			Bambo::Logger::Get()->Log(ProjectBrowserLog, Bambo::Verbosity::Error, "Can't open the project file.");
			return;
		}

		m_onProjectLoadedCallback();
	}
}