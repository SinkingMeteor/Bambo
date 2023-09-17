#include "Resource/ResourceManager.h"
#include "Resource/Resource.h"
namespace
{
	std::filesystem::path META_FILE_PATH = std::filesystem::path{".meta"};
	std::string META_FILE_STR = std::string{".meta"};

	std::size_t FILE_EXTENSION_WORLD = Bambo::ToId(".bworld");
	std::size_t FILE_EXTENSION_WAV = Bambo::ToId(".wav");
	std::size_t FILE_EXTENSION_PNG = Bambo::ToId(".png");
	std::size_t FILE_EXTENSION_SHADER = Bambo::ToId(".shader");


	Bambo::AssetType GetAssetType(const std::string& fileExtension)
	{
		std::size_t extensionId = Bambo::ToId(fileExtension);
		if (extensionId == FILE_EXTENSION_PNG) return Bambo::AssetType::Texture2D;
		if (extensionId == FILE_EXTENSION_WAV) return Bambo::AssetType::Audio;
		if (extensionId == FILE_EXTENSION_SHADER) return Bambo::AssetType::Shader;
		if (extensionId == FILE_EXTENSION_WORLD) return Bambo::AssetType::World;
		return Bambo::AssetType::None;
	}
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
		if (filenameExtension == META_FILE_PATH)
		{
			RegisterMetaFile(path);
			return;
		}

		RegisterFile(path);
	}

	void ResourceManager::RegisterMetaFile(const std::filesystem::path& metaFilePath)
	{
		BAMBO_ASSERT_S(std::filesystem::exists(metaFilePath))

		std::filesystem::path originalPath = metaFilePath;
		originalPath.replace_extension();
		if (!std::filesystem::exists(originalPath))
		{
			std::filesystem::remove(metaFilePath);
			return;
		}

		ResourceInfo info{};
		info.LoadInfo(metaFilePath);

		auto it = m_resources.find(info.AssetId);
		if (it != m_resources.end()) return;

		m_resources[info.AssetId] = info;
	}

	void ResourceManager::RegisterFile(const std::filesystem::path& filePath)
	{
		BAMBO_ASSERT_S(std::filesystem::exists(filePath))

		std::filesystem::path metaPath = filePath;
		metaPath.concat(META_FILE_STR);

		if (std::filesystem::exists(metaPath)) return;

		Bambo::AssetType assetType = GetAssetType(filePath.extension().string());
		if (assetType == Bambo::AssetType::None) return;

		bambo_id uniqueId = ToId(filePath.string());
		bambo_id typeId = static_cast<bambo_id>(assetType);

		BAMBO_ASSERT_S(m_resources.find(uniqueId) == m_resources.end())

		m_resources[uniqueId] = ResourceInfo::Create(uniqueId, typeId, filePath);

	}

	bool ResourceManager::HasResourceMetaFile(ResourceUniqueId id)
	{
		auto it = m_resources.find(id);
		return it != m_resources.end();
	}

	void ResourceManager::AddResourceMetaFile(ResourceInfo&& fileInfo)
	{
		BAMBO_ASSERT_S(!HasResourceMetaFile(fileInfo.AssetId))

		m_resources[fileInfo.AssetId] = std::forward<ResourceInfo>(fileInfo);
	}

	ResourceInfo* ResourceManager::GetResourceMetaFile(ResourceUniqueId id)
	{
		BAMBO_ASSERT_S(HasResourceMetaFile(id))

		return &m_resources[id];
	}


}