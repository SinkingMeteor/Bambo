#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"
#include "Widget/Widget.h"

namespace BamboEditor
{
	using OnFileClickDelegate = Bambo::MulticastDelegate<void(const std::filesystem::path&)>; // clicked file

	class FileBrowserWidget : public Widget
	{
	public:
		FileBrowserWidget();
		
		OnFileClickDelegate& OnFileClick() { return m_onFileClickDelegate; }
		
		const std::filesystem::path& GetCurrentPath() const { return m_currentPath; }
		void SetRootPath(const std::filesystem::path& rootPath);
		bool HasFileWithExtension(const std::string& extension) const;
		bool IsOnRootPath() const { return m_rootPath == m_currentPath; }
		void ToParentPath() { m_currentPath = m_currentPath.parent_path(); }
		virtual void Draw() override;
	private:
		std::filesystem::path m_rootPath;
		std::filesystem::path m_currentPath;

		OnFileClickDelegate m_onFileClickDelegate;

		void DisplayPath(const std::filesystem::directory_entry& entry);
	};
}