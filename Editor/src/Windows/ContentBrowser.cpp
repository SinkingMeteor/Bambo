#include "Windows/ContentBrowser.h"
#include "EditorPaths.h"

namespace
{
	const float TARGET_ITEM_SCALE = 20.0f;
}

namespace BamboEditor
{
	ContentBrowserWindow::ContentBrowserWindow(EditorContext* editorContext, SPtr<Bambo::Texture2D> fileIcon, SPtr<Bambo::Texture2D> folderIcon) :
		GUIWindow(),
		m_windowName("ContentBrowser"),
		m_currentDirectory(),
		m_rootDirectory(),
		m_selectedContentItem(""),
		m_fileIcon(fileIcon),
		m_folderIcon(folderIcon)
	{
		m_currentDirectory = editorContext->CurrentProject->GetAssetsPath();
		m_rootDirectory = m_currentDirectory;
	}

	void ContentBrowserWindow::OnGUI()
	{
		ImGui::Begin(m_windowName.c_str(), nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);

		if (ImGui::BeginMenuBar())
		{
			ImGui::Checkbox("Settings", &m_isOpenedSettingsPanel);
			ImGui::EndMenuBar();
		}
			
		DrawSettingsOverlay();
		DrawContentTree();
		ImGui::SameLine();
		DrawFolderContent();

		ImGui::End();
		
	}

	void ContentBrowserWindow::DrawPath(const std::filesystem::path& pathToDraw, bool isDirectory)
	{

		if (ImGui::TreeNodeEx(pathToDraw.string().c_str(), isDirectory ? ImGuiTreeNodeFlags_None : ImGuiTreeNodeFlags_Bullet, pathToDraw.filename().string().c_str()))
		{
			if (isDirectory)
			{
				for (auto& directoryEntry : std::filesystem::directory_iterator(pathToDraw))
				{
					const std::filesystem::path& path = directoryEntry.path();
					DrawPath(path, directoryEntry.is_directory());
				}
			}

			ImGui::TreePop();
		}

		//if (ImGui::IsItemClicked())
		//{
		//	m_selectedEntity = &m_editorContext->CurrentWorld->GetEntityByID(idComponent->ID);
		//}

		//if (ImGui::BeginDragDropSource())
		//{
		//	ImGui::SetDragDropPayload("GOReparent", &childEntity, sizeof(childEntity));
		//	ImGui::Text("%s", tag->Tag.c_str());
		//	ImGui::EndDragDropSource();
		//}

		//if (ImGui::BeginDragDropTarget())
		//{
		//	const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GOReparent");
		//	if (payload != nullptr)
		//	{
		//		flecs::entity* targetEntity = static_cast<flecs::entity*>(payload->Data);
		//		targetEntity->child_of(childEntity);
		//	}

		//	ImGui::EndDragDropTarget();
		//}
	}

	void ContentBrowserWindow::DrawContentTree()
	{
		float windowHeight = ImGui::GetWindowHeight();
		float windowWidth = ImGui::GetWindowWidth();

		ImGui::BeginChild("ContentBrowserTree", ImVec2{ windowWidth * 0.2f, 0.0f }, true, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoDocking);
	
		std::filesystem::path targetPath = m_rootDirectory;
		DrawPath(targetPath, true);
		
		ImGui::EndChild();
	}

	void ContentBrowserWindow::DrawFolderContent()
	{
		float windowHeight = ImGui::GetWindowHeight();
		float windowWidth = ImGui::GetWindowWidth();

		ImGui::BeginChild("ContentBrowserContent", ImVec2{ 0.0f , 0.0f }, true, ImGuiWindowFlags_NoDocking);

		ImGui::Text(m_currentDirectory.string().c_str());
		ImGui::Dummy(ImVec2{ 1.0f, 10.0f });

		if (m_currentDirectory.empty())
		{
			ImGui::Text("You shoud create or open a project first");
			ImGui::EndChild();
			return;
		}

		if (ImGui::BeginPopupContextWindow("ContentBrowserContext"))
		{
			if (ImGui::MenuItem("CreateFolder")) { Bambo::MakeDirectory(m_currentDirectory, "NewFolder"); }

			ImGui::EndPopup();
		}

		if (m_currentDirectory != m_rootDirectory)
		{
			if (ImGui::Button("<-"))
			{
				m_currentDirectory = m_currentDirectory.parent_path();
			}
		}

		float panelWidth = ImGui::GetContentRegionAvail().x;
		float cellSize = panelWidth / m_columnsCount;
		bool selectedNewItem = false;

		ImGui::Columns(m_columnsCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
		{
			const std::filesystem::path& path = directoryEntry.path();
			std::string filenameString = path.filename().string();
			bool isSelected = m_selectedContentItem.size() != 0 && m_selectedContentItem == filenameString;

			ImGui::PushID(filenameString.c_str());
			SPtr<Bambo::Texture2D> icon = directoryEntry.is_directory() ? m_folderIcon : m_fileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon->GetID(), { m_itemScale, m_itemScale }, { 0, 1 }, { 1, 0 }, -1, isSelected ? ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f } : ImVec4{0.0f, 0.0f, 0.0f, 0.0f});

			if (ImGui::BeginDragDropSource())
			{
				std::filesystem::path relativePath(path);
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}

			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			{
				selectedNewItem = true;
				m_selectedContentItem = filenameString;
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				m_selectedContentItem = "";
				if (directoryEntry.is_directory())
					m_currentDirectory /= path.filename();
			}

			ImGui::SameLine();

			ImGui::SetNextItemWidth(cellSize);
			ImGui::SetWindowFontScale(m_itemScale / TARGET_ITEM_SCALE);
			ImGui::TextWrapped(filenameString.c_str());
			ImGui::SetWindowFontScale(1.0f);

			ImGui::NextColumn();

			ImGui::PopID();
		}

		if (ImGui::IsMouseClicked(0) && !selectedNewItem)
		{
			m_selectedContentItem = "";
		}

		ImGui::Columns(1);
		ImGui::EndChild();
	}

	void ContentBrowserWindow::DrawSettingsOverlay()
	{
		if (!m_isOpenedSettingsPanel) return;

		ImGuiIO& io = ImGui::GetIO();
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

		ImVec2 windowPosition = ImGui::GetWindowPos();
		windowPosition.x += 50.0f;
		windowPosition.y += 50.0f;

		ImGui::SetNextWindowPos(windowPosition, ImGuiCond_Always, ImVec2(0.0f, 0.0f));

		ImGui::Begin("Content browser settings", nullptr, window_flags);
		
		ImGui::Text("Content settings:");
		ImGui::Separator();

		ImGui::SliderFloat("Thumbnail Size", &m_itemScale, 12.0f, 48.0f);
		ImGui::SliderInt("Columns Count", &m_columnsCount, 1, 4);

		ImGui::End();
	}
}