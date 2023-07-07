#include "Windows/ProjectBrowser.h"
#include "Utils.h"

namespace
{
	const std::string TARGET_EXTENSION = "bambo";
}

DECLARE_LOG_CATEGORY_STATIC(ProjectBrowserLog)

namespace BamboEditor
{
	ProjectBrowserWindow::ProjectBrowserWindow(EditorContext* editorContext, const std::function<void()>& onProjectLoadedCallback) :
		m_editorContext(editorContext),
		m_onProjectLoadedCallback(onProjectLoadedCallback),
		m_windowName("Project Browser"),
		m_newProjectName(),
		m_rootDirectory(std::filesystem::current_path().root_path()),
		m_currentDirectory(m_rootDirectory),
		m_fileIcon(),
		m_folderIcon(),
		m_thumbnailSize(16.0f),
		m_padding(8.0f),
		m_sizeFactor(1.0f),
		m_hasProjectAtDirectory(false)
	{
		Bambo::TextureProvider* textureProvider = Bambo::TextureProvider::Get();
		m_fileIcon = textureProvider->GetResource(Bambo::ToId(BamboPaths::FILE_ICON_TEXTURE_KEY));
		m_folderIcon = textureProvider->GetResource(Bambo::ToId(BamboPaths::FOLDER_ICON_TEXTURE_KEY));
	}

	void ProjectBrowserWindow::OnGUI()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 viewportSize = viewport->Size;
		ImVec2 windowPos{ 0.0f, 0.0f };

		ImGui::SetNextWindowSize(viewportSize);
		ImGui::SetNextWindowPos(windowPos);

		ImGui::Begin(m_windowName.c_str(), nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoMove | ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);

		ImGui::Text(m_currentDirectory.string().c_str());

		if (m_currentDirectory != m_rootDirectory)
		{
			if (ImGui::Button("<-"))
			{
				m_currentDirectory = m_currentDirectory.parent_path();
			}
			ImGui::SameLine();
		}

		if (!m_hasProjectAtDirectory)
		{
			if (ImGui::Button("Create New Here"))
			{
				CreateNewProject();
			}

			ImGui::SameLine(0.0f, 50.0f);
			ImGui::Text("Project Name: ");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(200.0f);
			ImGui::PushID("Project Name");
			ImGui::InputText("", m_newProjectName, 32);
			ImGui::PopID();
		}

		ImGui::SameLine();
		ImGui::SetNextItemWidth(200.0f);
		ImGui::SliderFloat("Size", &m_sizeFactor, 0.5f, 2.0f);

		float cellSize = (m_thumbnailSize + m_padding) * m_sizeFactor;
		float panelWidth = ImGui::GetContentRegionAvail().x;

		m_hasProjectAtDirectory = false;

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
		{
			const std::filesystem::path& path = directoryEntry.path();
			std::string filenameString = path.filename().string();

			bool isDirectory = directoryEntry.is_directory();

			if (isDirectory)
			{
				if (Bambo::IsHiddenFolder(path))
					continue;
			}
			else
			{
				if (!Bambo::HasExtension(filenameString, TARGET_EXTENSION))
					continue;

				m_hasProjectAtDirectory = true;
			}

			SPtr<Bambo::Texture2D> icon = isDirectory ? m_folderIcon : m_fileIcon;
			ImGui::ImageButton((ImTextureID)icon->GetID(), { cellSize, cellSize }, { 0, 1 }, { 1, 0 });

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
				{
					m_currentDirectory /= path.filename();
				}
				else
				{
					ImGui::End();
					OpenProject(path);
					return;
				}
			}

			ImGui::SameLine();
			ImGui::SetNextItemWidth(300.0f);
			ImGui::Text(filenameString.c_str());
		}

		ImGui::End();
	}

	void ProjectBrowserWindow::CreateNewProject()
	{
		std::filesystem::path newProjectFullPath = m_currentDirectory / (m_newProjectName + PROJECT_EXTENSION_DOT);
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