#pragma once
#include "pch.h"
#include "Singleton.h"
namespace Bambo 
{
	template<typename Resource, typename Loader>
	class BAMBO_API ResourceProvider : public Singleton<ResourceProvider<Resource, Loader>>
	{
	public:
		ResourceProvider();
		ResourceProvider(const ResourceProvider&) = delete;
		ResourceProvider& operator=(const ResourceProvider&) = delete;
		template<typename... Args>
		std::shared_ptr<Resource> Load(const bambo_id id, Args &&...args);
		std::shared_ptr<Resource> GetResource(const bambo_id id);
		bool Contains(const bambo_id id);
	private:
		std::unordered_map<bambo_id, std::shared_ptr<Resource>> m_resourceMap;
		Loader m_loader;
	};

	template<typename Resource, typename Loader>
	ResourceProvider<Resource, Loader>::ResourceProvider() :
		m_resourceMap(),
		m_loader()
	{

	}

	template<typename Resource, typename Loader>
	template<typename ...Args>
	std::shared_ptr<Resource> ResourceProvider<Resource, Loader>::Load(const bambo_id id, Args && ...args)
	{
		if (Contains(id))
		{
			return GetResource(id);
		}

		std::shared_ptr<Resource> resource = m_loader(std::forward<Args>(args)...);
		m_resourceMap.emplace(id, resource);
		return resource;
	}

	template<typename Resource, typename Loader>
	bool ResourceProvider<Resource, Loader>::Contains(const bambo_id id) 
	{
		auto it = m_resourceMap.find(id);
		return it != m_resourceMap.end();
	}

	template<typename Resource, typename Loader>
	std::shared_ptr<Resource> ResourceProvider<Resource, Loader>::GetResource(const bambo_id id)
	{
		BAMBO_ASSERT(Contains(id), "No key found in resource map")
		return m_resourceMap[id];
	}

}