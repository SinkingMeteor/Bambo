#include "EditorWindows/ContentBrowser.h"
#include "EditorPaths.h"

namespace
{
	const float TARGET_ITEM_SCALE = 20.0f;
}

namespace BamboEditor
{
	ContentBrowserWindow::ContentBrowserWindow(EditorContext* editorContext) :
		GUIWindow(),
		m_editorContext(editorContext),
		m_fileBrowserWidget(),
		m_windowName("ContentBrowser")
	{
		m_fileBrowserWidget.SetRootPath(editorContext->CurrentProject->GetAssetsPath());
	}

	void ContentBrowserWindow::OnGUI()
	{
		ImGui::Begin(m_windowName.c_str(), nullptr, ImGuiWindowFlags_None);

		DrawContentTree();
		ImGui::SameLine();
		DrawFolderContent();

		ImGui::End();
		
	}

	void ContentBrowserWindow::DrawPath(const std::filesystem::path& path, bool isDirectory)
	{
		std::string filenameString = path.filename().string();

		if (isDirectory)
		{
			if (Bambo::IsHiddenFolder(path))
				return;
		}

		ImGui::TableNextRow();
		ImGui::TableNextColumn();

		if (isDirectory)
		{
			bool open = ImGui::TreeNodeEx(filenameString.c_str(),  ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_OpenOnArrow, filenameString.c_str());

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				m_fileBrowserWidget.SetRootPath(path);
			}

			if (open)
			{
				for (auto& directoryEntry : std::filesystem::directory_iterator(path))
				{
					const std::filesystem::path& childPath = directoryEntry.path();
					DrawPath(childPath, directoryEntry.is_directory());
				}
				ImGui::TreePop();
			}
		}
		else
		{
			static ImGuiTreeNodeFlags fileFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_SpanFullWidth;
			ImGui::TreeNodeEx(filenameString.c_str(), fileFlags);
			ImGui::TreePop();

		}
	}

	void ContentBrowserWindow::DrawContentTree()
	{
		float windowWidth = ImGui::GetWindowWidth();
		float windowHeight = ImGui::GetWindowHeight();

		ImGui::BeginChild("ContentBrowserTree", ImVec2{ windowWidth * 0.2f, 0.0f }, true, ImGuiWindowFlags_NoDocking);
	
		static ImGuiTableFlags tableFlags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
		if (ImGui::BeginTable("ContentHierarchy", 1, tableFlags))
		{
			ImGui::TableSetupColumn("Name", ImGuiBackendFlags_None);
			ImGui::TableHeadersRow();

			DrawPath(m_editorContext->CurrentProject->GetAssetsPath(), true);
			ImGui::EndTable();
		}

		ImGui::EndChild();
	}

	void ContentBrowserWindow::DrawFolderContent()
	{
		float windowHeight = ImGui::GetWindowHeight();
		float windowWidth = ImGui::GetWindowWidth();

		ImGui::BeginChild("ContentBrowserContent", ImVec2{ 0.0f , 0.0f }, true, ImGuiWindowFlags_NoDocking);

		const std::filesystem::path& currentDir = m_fileBrowserWidget.GetCurrentPath();
		ImGui::Text(currentDir.string().c_str());
		ImGui::Dummy(ImVec2{ 1.0f, 10.0f });

		if (currentDir.empty())
		{
			ImGui::Text("You shoud create or open a project first");
			ImGui::EndChild();
			return;
		}

		if (ImGui::BeginPopupContextWindow("ContentBrowserContext"))
		{
			if (ImGui::MenuItem("CreateFolder")) { Bambo::MakeDirectory(currentDir, "NewFolder"); }

			ImGui::EndPopup();
		}

		if (!m_fileBrowserWidget.IsOnRootPath())
		{
			if (ImGui::Button("<-"))
			{
				m_fileBrowserWidget.ToParentPath();
			}
		}

		m_fileBrowserWidget.Draw();

		ImGui::EndChild();
	}
}