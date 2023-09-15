#include "FileBrowserWidget.h"

namespace
{
	const char* BROWSER_FILETYPE_FILE = "file";
	const char* BROWSER_FILETYPE_FOLDER = "folder";
}

namespace BamboEditor
{
	FileBrowserWidget::FileBrowserWidget() :
		Widget(),
		m_rootPath(std::filesystem::current_path()),
		m_currentPath(m_rootPath),
		m_onFileClickDelegate()
	{}

	void FileBrowserWidget::SetRootPath(const std::filesystem::path& rootPath)
	{
		m_rootPath = rootPath;
		m_currentPath = m_rootPath;
	}

	bool FileBrowserWidget::HasFileWithExtension(const std::string& extension) const
	{
		bool hasExtension = false;

		for (const std::filesystem::directory_entry& directoryEntry : std::filesystem::directory_iterator(m_currentPath))
		{
			if (directoryEntry.is_directory()) continue;

			std::string filenameString = directoryEntry.path().filename().string();
			hasExtension |= Bambo::HasExtension(filenameString, extension);
		}

		return hasExtension;
	}

    void FileBrowserWidget::DisplayPath(const std::filesystem::directory_entry& entry)
    {
		const std::filesystem::path& path = entry.path();
		std::string filenameString = path.filename().string();

		bool isDirectory = entry.is_directory();
		uint32 fileSize = 0;
		const char* fileType = BROWSER_FILETYPE_FOLDER;

		if (isDirectory)
		{
			if (Bambo::IsHiddenFolder(path))
				return;
		}
		else
		{
			fileType = BROWSER_FILETYPE_FILE;
			fileSize = entry.file_size();
			//@TODO: Add filters
			//if (!Bambo::HasExtension(filenameString, TARGET_EXTENSION))
				//continue;
		}

        ImGui::TableNextRow();
        ImGui::TableNextColumn();

		ImGui::TextUnformatted(fileType);
		ImGui::TableNextColumn();

		static ImGuiTreeNodeFlags fileFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_SpanFullWidth;
		
		if (ImGui::TreeNodeEx(filenameString.c_str(), fileFlags, filenameString.c_str()))
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (isDirectory)
				{
					m_currentPath /= path.filename();
				}
				else
				{
					m_onFileClickDelegate.Invoke(entry.path());
				}
			}

			ImGui::TableNextColumn();
			ImGui::Text("%u KB", fileSize);

			ImGui::TreePop();
		}
    }

	void FileBrowserWidget::Draw()
	{
		static ImGuiTableFlags tableFlags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
	
        const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
        const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

        if (ImGui::BeginTable("Browser", 3, tableFlags))
        {
			ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
            ImGui::TableHeadersRow();

			for (const std::filesystem::directory_entry& directoryEntry : std::filesystem::directory_iterator(m_currentPath))
			{
				DisplayPath(directoryEntry);
			}

            ImGui::EndTable();
        }
	}
}