#include "Resource/ResourceCache.h"

namespace Bambo
{
	ResourceCache::ResourceCache(const std::string& destination) :
		m_resourcePaths(),
		m_destination(destination)
	{
		std::filesystem::path path{ destination };

		if (std::filesystem::exists(path))
		{
			std::ifstream stream{ path };
			BAMBO_ASSERT_S(!stream.fail())

			nlohmann::json rootJson{};
			stream >> rootJson;
			stream.close();

			BAMBO_ASSERT_S(!rootJson.is_null());

			m_resourcePaths = rootJson.get<std::unordered_map<bambo_id, std::unordered_map<bambo_id, std::string>>>();
		}
	}

	ResourceCache::~ResourceCache()
	{
		std::filesystem::path path{ m_destination };

		std::ofstream stream{ path };
		BAMBO_ASSERT_S(!stream.fail())

		nlohmann::json rootJson{};
		rootJson = m_resourcePaths;

		stream << rootJson;
		stream.close();
	}

	void ResourceCache::AddResource(bambo_id typeId, bambo_id assetId, const std::string& resourcePath)
	{
		BAMBO_ASSERT(!HasResource(typeId, assetId), "Resource already has been loaded")

		m_resourcePaths[typeId][assetId] = resourcePath;
	}

	bool ResourceCache::TryGetPath(bambo_id typeId, bambo_id assetId, std::string& str)
	{
		if (!HasResource(typeId, assetId)) return false;

		str = m_resourcePaths[typeId][assetId];
	}


	bool ResourceCache::HasResource(bambo_id typeId, bambo_id assetId) const
	{
		auto typeIt = m_resourcePaths.find(typeId);

		if (typeIt == m_resourcePaths.end()) return false;

		auto assetIt = typeIt->second.find(typeId);

		return assetIt != typeIt->second.end();
	}

	void ResourceCache::RemoveResource(bambo_id typeId, bambo_id assetId)
	{
		BAMBO_ASSERT(HasResource(typeId, assetId), "Resource cached hasn't resource")

		m_resourcePaths[typeId].erase(assetId);
	}
}