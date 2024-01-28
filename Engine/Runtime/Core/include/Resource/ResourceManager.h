#pragma once
#include "Essentials.h"
#include "ResourceInfo.h"
namespace Bambo
{
	class BAMBO_API ResourceManager
	{
		using ResourceUniqueId = bambo_id;
	public:
		ResourceManager();
		void ScanFiles(const std::filesystem::path& directory, bool isRecursive);
		void RegisterMetaFile(const std::filesystem::path& metaFilePath);
		void RegisterFile(const std::filesystem::path& filePath);
		bool HasResourceMetaFile(ResourceUniqueId id);
		ResourceInfo* GetResourceMetaFile(ResourceUniqueId id);
		void AddResourceMetaFile(ResourceInfo&& fileInfo);
	private:
		std::unordered_map<ResourceUniqueId, ResourceInfo> m_resources;
	};
}
