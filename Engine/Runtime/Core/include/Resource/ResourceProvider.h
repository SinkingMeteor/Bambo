#pragma once
#include "Essentials.h"
#include "Resource/ResourceCache.h"
namespace Bambo 
{
	template<typename ResType, typename Loader>
	class BAMBO_API ResourceProvider final
	{
	public:
		ResourceProvider(SPtr<ResourceCache> cache);
		ResourceProvider(const ResourceProvider&) = delete;
		ResourceProvider& operator=(const ResourceProvider&) = delete;
		SPtr<ResType> Load(const std::string& path);
		SPtr<ResType> Load(const std::size_t id);
		SPtr<ResType> GetResource(const bambo_id id);
		bool Contains(const bambo_id id);
	private:
		std::unordered_map<bambo_id, SPtr<ResType>> m_resourceMap;
		Loader m_loader;
		SPtr<ResourceCache> m_cache;
	};

	template<typename ResType, typename Loader>
	ResourceProvider<ResType, Loader>::ResourceProvider(SPtr<ResourceCache> cache) :
		m_resourceMap(),
		m_loader(),
		m_cache(cache)
	{}

	template<typename ResType, typename Loader>
	SPtr<ResType> ResourceProvider<ResType, Loader>::Load(const std::string& path)
	{
		std::size_t id = ToId(path);

		if (Contains(id))
		{
			return GetResource(id);
		}

		m_cache->AddResource(ResType::GetStaticID(), id, path);
		SPtr<ResType> resource = m_loader(id, path);
		m_resourceMap.emplace(id, resource);
		return resource;
	}

	template<typename ResType, typename Loader>
	SPtr<ResType> ResourceProvider<ResType, Loader>::Load(const std::size_t id)
	{
		if (Contains(id))
		{
			return GetResource(id);
		}

		std::string path{};
		if (m_cache && m_cache->TryGetPath(ResType::GetStaticID(), id, path))
		{
			SPtr<ResType> resource = m_loader(id, path);
			m_resourceMap.emplace(id, resource);
			return resource;
		}

		return nullptr;

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