#include "Resource/ResourceManager.h"

namespace
{
	std::filesystem::path META_FILE_PATH = std::filesystem::path{".meta"};
}

namespace Bambo
{
	Bambo::ResourceManager::ResourceManager() :
		m_resources()
	{
	}

	void ResourceManager::ScanFiles(const std::filesystem::path& path)
	{
		bool isDirectory = std::filesystem::is_directory(path);

		if (isDirectory)
		{
			for (auto& directoryEntry : std::filesystem::directory_iterator(path))
			{
				const std::filesystem::path& childPath = directoryEntry.path();
				ScanFiles(childPath);
			}

			return;
		}
	
		std::filesystem::path filenameExtension = path.extension();
		if (filenameExtension != META_FILE_PATH) return;

		ResourceInfo info{};
		info.LoadInfo(path);

		auto it = m_resources.find(info.AssetId);
		if (it != m_resources.end()) return;

		m_resources[info.AssetId] = info;
	}

	bool ResourceManager::HasFile(bambo_id id)
	{
		auto it = m_resources.find(id);
		return it != m_resources.end();
	}

	void ResourceManager::AddFile(ResourceInfo&& fileInfo)
	{
		BAMBO_ASSERT_S(!HasFile(fileInfo.AssetId))

		m_resources[fileInfo.AssetId] = std::forward<ResourceInfo>(fileInfo);
	}

	ResourceInfo* ResourceManager::GetFile(bambo_id id)
	{
		BAMBO_ASSERT_S(HasFile(id))

		return &m_resources[id];
	}


}