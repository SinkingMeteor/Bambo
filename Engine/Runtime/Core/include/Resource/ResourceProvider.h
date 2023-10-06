#pragma once
#include "Essentials.h"
#include "ResourceManager.h"
#include "Engine.h"

namespace Bambo 
{
	class Engine;

	template<typename ResType, typename Loader>
	class BAMBO_API ResourceProvider final
	{
	public:
		ResourceProvider(Engine* engine);
		ResourceProvider(const ResourceProvider&) = delete;
		ResourceProvider& operator=(const ResourceProvider&) = delete;
		SPtr<ResType> Load(const std::filesystem::path& path);
		SPtr<ResType> Load(bambo_id id);
		SPtr<ResType> GetResource(const bambo_id id);
		bool Contains(const bambo_id id);
	private:
		std::unordered_map<bambo_id, SPtr<ResType>> m_resourceMap;
		Loader m_loader;
		Engine* m_engine;
	};

	template<typename ResType, typename Loader>
	ResourceProvider<ResType, Loader>::ResourceProvider(Engine* engine) :
		m_resourceMap(),
		m_loader(),
		m_engine(engine)
	{}

	template<typename ResType, typename Loader>
	SPtr<ResType> ResourceProvider<ResType, Loader>::Load(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path)) 
		{
			Logger::Get()->Log("ResourceProvider", Verbosity::Warning, "Can't load the file with path %s", path.string().c_str());
			return nullptr;
		}

		std::filesystem::path metaPath = path;
		metaPath.concat(".meta");
		
		if (!std::filesystem::exists(metaPath)) 
		{
			Logger::Get()->Log("ResourceProvider", Verbosity::Warning, "Can't find a meta file for the file with path %s", path.string().c_str());
			return nullptr;
		}

		ResourceInfo info{};
		info.LoadInfo(metaPath);

		BAMBO_ASSERT_S(ResourceManager::Get()->HasResourceMetaFile(info.AssetId));

		if (Contains(info.AssetId))
		{
			return GetResource(info.AssetId);
		}

		SPtr<ResType> resource = m_loader(m_engine, info.AssetId, path.string());
		m_resourceMap.emplace(info.AssetId, resource);
		return resource;
	}

	template<typename ResType, typename Loader>
	SPtr<ResType> ResourceProvider<ResType, Loader>::Load(bambo_id id)
	{
		if (!ResourceManager::Get()->HasResourceMetaFile(id)) return nullptr;

		if (Contains(id))
		{
			return GetResource(id);
		}

		ResourceInfo* info = ResourceManager::Get()->GetResourceMetaFile(id);
		BAMBO_ASSERT_S(info)
		id = info->AssetId;

		SPtr<ResType> resource = m_loader(m_engine, id, info->FullPath.string());
		m_resourceMap.emplace(id, resource);
		return resource;
	}


	template<typename ResType, typename Loader>
	bool ResourceProvider<ResType, Loader>::Contains(const bambo_id id)
	{
		auto it = m_resourceMap.find(id);
		return it != m_resourceMap.end();
	}

	template<typename ResType, typename Loader>
	SPtr<ResType> ResourceProvider<ResType, Loader>::GetResource(const bambo_id id)
	{
		BAMBO_ASSERT(Contains(id), "No key found in resource map")
		return m_resourceMap[id];
	}

}