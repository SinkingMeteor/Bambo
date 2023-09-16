#pragma once
#include "Essentials.h"
#include "ResourceManager.h"

namespace Bambo 
{
	template<typename ResType, typename Loader>
	class BAMBO_API ResourceProvider final
	{
	public:
		ResourceProvider();
		ResourceProvider(const ResourceProvider&) = delete;
		ResourceProvider& operator=(const ResourceProvider&) = delete;
		SPtr<ResType> Load(const std::filesystem::path& path);
		SPtr<ResType> Load(bambo_id id);
		SPtr<ResType> GetResource(const bambo_id id);
		bool Contains(const bambo_id id);
	private:
		std::unordered_map<bambo_id, SPtr<ResType>> m_resourceMap;
		Loader m_loader;
	};

	template<typename ResType, typename Loader>
	ResourceProvider<ResType, Loader>::ResourceProvider() :
		m_resourceMap(),
		m_loader()
	{}

	template<typename ResType, typename Loader>
	SPtr<ResType> ResourceProvider<ResType, Loader>::Load(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path)) return nullptr;

		std::size_t id = ToId(path.string());

		if (Contains(id))
		{
			return GetResource(id);
		}

		if (ResourceManager::Get()->HasFile(id))
		{
			ResourceInfo* info = ResourceManager::Get()->GetFile(id);
			BAMBO_ASSERT_S(info)
			id = info->AssetId;
		}
		else
		{
			ResourceManager::Get()->AddFile(ResourceInfo::Create(id, ResType::GetStaticID(), path));
		}

		SPtr<ResType> resource = m_loader(id, path.string());
		m_resourceMap.emplace(id, resource);
		return resource;
	}

	template<typename ResType, typename Loader>
	SPtr<ResType> ResourceProvider<ResType, Loader>::Load(bambo_id id)
	{
		if (Contains(id))
		{
			return GetResource(id);
		}

		if (!ResourceManager::Get()->HasFile(id)) return nullptr;

		ResourceInfo* info = ResourceManager::Get()->GetFile(id);
		BAMBO_ASSERT_S(info)
		id = info->AssetId;

		SPtr<ResType> resource = m_loader(id, info->FullPath.string());
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