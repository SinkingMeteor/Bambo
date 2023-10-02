#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"
#include "Widget.h"
#include "Resource/ResourceInfo.h"

namespace BamboEditor
{
	using OnFileClickDelegate = Bambo::MulticastDelegate<void(const std::filesystem::path&)>; // clicked file

	class FileBrowserWidget : public Widget
	{
		struct FileDisplayParameters
		{
		public:
			std::string FileType{};
			uint32 FileSize{0};
			bool NeedToDisplay{ false };
		};

	public:
		FileBrowserWidget();
		
		OnFileClickDelegate& OnFileClick() { return m_onFileClickDelegate; }
		
		const std::filesystem::path& GetCurrentPath() const { return m_currentPath; }
		void SetRootPath(const std::filesystem::path& rootPath);
		bool HasFileWithExtension(const std::string& extension) const;
		bool IsOnRootPath() const { return m_rootPath == m_currentPath; }
		void ToParentPath() { m_currentPath = m_currentPath.parent_path(); }
		virtual void Draw() override;
	protected:
		virtual void ProcessFile(const std::filesystem::path& filePath, FileDisplayParameters& displayParameters, Bambo::ResourceInfo& info);
		virtual void ProcessDirectory(const std::filesystem::path& filePath, FileDisplayParameters& displayParameters);
	private:
		std::filesystem::path m_rootPath;
		std::filesystem::path m_currentPath;

		OnFileClickDelegate m_onFileClickDelegate;

		void DisplayPath(const std::filesystem::directory_entry& entry);
	};
}