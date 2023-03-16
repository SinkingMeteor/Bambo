#pragma once
#include "pch.h"
#include "Graphics/Texture2D.h"

namespace Bambo 
{
	struct SlicedTexture
	{
		Texture2D Texture{};
	};

	struct TextureLoader
	{
		using result_type = std::shared_ptr<SlicedTexture>;

		result_type operator()(const std::string& path) const
		{
			std::shared_ptr texture = std::make_shared<SlicedTexture>();
			return texture;
		}
	};

	template<typename Resource, typename Loader>
	class BAMBO_API ResourceProvider 
	{
	public:
		ResourceProvider();
		ResourceProvider(const ResourceProvider&) = delete;
		ResourceProvider& operator=(const ResourceProvider&) = delete;
		template<typename... Args>
		void Load(const bambo_id id, Args &&...args);
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
	void ResourceProvider<Resource, Loader>::Load(const bambo_id id, Args && ...args)
	{
		BAMBO_ASSERT(!Contains(id), "Key already in resource map")
		std::shared_ptr<Resource> resource = m_loader(std::forward<Args>(args)...);
		m_resourceMap.emplace(id, resource);
	}

	template<typename Resource, typename Loader>
	bool ResourceProvider<Resource, Loader>::Contains(const bambo_id id) 
	{
		auto it = m_resourceMap.find(id);
		return it != m_resourceMap.end();
	}


	using TextureProvider = ResourceProvider<SlicedTexture, TextureLoader>;
}