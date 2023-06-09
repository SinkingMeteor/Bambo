#include "Windows/ContentBrowser.h"
#include "EditorPaths.h"
namespace BamboEditor
{
	ContentBrowserWindow::ContentBrowserWindow(EditorContext* editorContext) :
		GUIWindow(),
		m_windowName("ContentBrowser"),
		m_currentDirectory(),
		m_rootDirectory(),
		m_fileIcon(),
		m_folderIcon()
	{
		Bambo::TextureProvider* textureProvider = Bambo::TextureProvider::Get();
		m_fileIcon = textureProvider->GetResource(Bambo::ToId(BamboPaths::FILE_ICON_TEXTURE_KEY));
		m_folderIcon = textureProvider->GetResource(Bambo::ToId(BamboPaths::FOLDER_ICON_TEXTURE_KEY));

		m_currentDirectory = editorContext->CurrentProject->GetAssetsPath();
		m_rootDirectory = m_currentDirectory;
	}

	void ContentBrowserWindow::OnGUI()
	{
		ImGui::Begin(m_windowName.c_str(), nullptr, ImGuiWindowFlags_MenuBar);

		if (m_currentDirectory.empty())
		{
			ImGui::Text("You shoud create or open a project first");
			ImGui::End();
			return;
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::Checkbox("Settings", &m_isOpenedSettingsPanel)) {}
			ImGui::EndMenuBar();
		}

		DrawSettingsOverlay();

		if (m_currentDirectory != m_rootDirectory)
		{
			if (ImGui::Button("<-"))
			{
				m_currentDirectory = m_currentDirectory.parent_path();
			}
		}

		float cellSize = m_thumbnailSize + m_padding;
		float panelWidth = ImGui::GetContentRegionAvail().x;
		int32 columnCount = static_cast<int32>(panelWidth / cellSize);
		columnCount = std::max(1, columnCount);

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
		{
			const auto& path = directoryEntry.path();
			std::string filenameString = path.filename().string();

			ImGui::PushID(filenameString.c_str());
			SPtr<Bambo::Texture2D> icon = directoryEntry.is_directory() ? m_folderIcon : m_fileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon->GetID(), { m_thumbnailSize, m_thumbnailSize }, { 0, 1 }, { 1, 0 });

			if (ImGui::BeginDragDropSource())
			{
				std::filesystem::path relativePath(path);
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
					m_currentDirectory /= path.filename();

			}
			ImGui::TextWrapped(filenameString.c_str());

			ImGui::NextColumn();

			ImGui::PopID();
		}

		ImGui::Columns(1);

		ImGui::End();
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

		ImGui::SetNextWindowBgAlpha(0.35f);
		if (ImGui::Begin("Content browser settings", nullptr, window_flags))
		{
			ImGui::Text("Content settings:");
			ImGui::Separator();

			ImGui::SliderFloat("Thumbnail Size", &m_thumbnailSize, 16, 512);
			ImGui::SliderFloat("Padding", &m_padding, 0, 32);

		}
		ImGui::End();
	}
}