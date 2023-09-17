#include "FileBrowserWidget.h"
#include "Resource/ResourceManager.h"
#include "Resource/Resource.h"
#include "Resource/ResourceInfo.h"
namespace
{
	const char* BROWSER_FILETYPE_FILE = "File";
	const char* BROWSER_FILETYPE_FOLDER = "Folder";
	const char* META_EXTENSION = ".meta";

	template<typename ResourceProviderType>
	std::size_t TEXTURE_ASSET_ID = ResourceProviderType::GetStaticID();

	const char* GetResourceTypeName(std::size_t typeId)
	{
		switch (typeId)
		{
		case (int32)Bambo::AssetType::None: return "Unknown";
		case (int32)Bambo::AssetType::Texture2D: return "Texture2D";
		case (int32)Bambo::AssetType::Shader: return "Shader";
		case (int32)Bambo::AssetType::Audio: return "Audio";
		case (int32)Bambo::AssetType::World: return "World";
		default: return "File";
		}
	}
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

	void FileBrowserWidget::ProcessFile(const std::filesystem::path& filePath, FileDisplayParameters& displayParameters)
	{
		if (filePath.extension() == META_EXTENSION)
		{
			displayParameters.NeedToDisplay = false;
			return;
		}

		displayParameters.NeedToDisplay = true;
		displayParameters.FileSize = std::filesystem::file_size(filePath);

		std::filesystem::path metaFilePath = filePath;
		metaFilePath.concat(".meta");

		if (!std::filesystem::exists(metaFilePath))
		{
			displayParameters.FileType = BROWSER_FILETYPE_FILE;
			return;
		}


		Bambo::ResourceInfo info{};
		info.LoadInfo(metaFilePath);
		displayParameters.FileType = GetResourceTypeName(info.TypeId);
	}

	void FileBrowserWidget::ProcessDirectory(const std::filesystem::path& folderPath, FileDisplayParameters& displayParameters)
	{
		if (Bambo::IsHiddenFolder(folderPath))
		{
			displayParameters.NeedToDisplay = false;
			return;
		}

		displayParameters.FileType = BROWSER_FILETYPE_FOLDER;
		displayParameters.FileSize = 0u;
		displayParameters.NeedToDisplay = true;
	}

    void FileBrowserWidget::DisplayPath(const std::filesystem::directory_entry& entry)
    {
		const std::filesystem::path& path = entry.path();
		std::string filenameString = path.filename().string();

		bool isDirectory = entry.is_directory();
		FileDisplayParameters displayParameters{};

		if (isDirectory)
		{
			ProcessDirectory(path, displayParameters);
	
		}
		else
		{
			ProcessFile(path, displayParameters);
		}

		if (!displayParameters.NeedToDisplay) return;

        ImGui::TableNextRow();
        ImGui::TableNextColumn();

		ImGui::TextUnformatted(displayParameters.FileType.c_str());
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
			ImGui::Text("%u KB", displayParameters.FileSize);

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