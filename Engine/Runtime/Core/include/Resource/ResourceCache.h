#pragma once
#include "Essentials.h"

namespace Bambo
{
	class BAMBO_API ResourceCache final
	{
	public:
		ResourceCache(const std::string& destination);
		ResourceCache(const ResourceCache&) = delete;
		ResourceCache operator=(const ResourceCache&) = delete;
		~ResourceCache();

		void AddResource(bambo_id typeId, bambo_id assetId, const std::string& resourcePath);
		bool TryGetPath(bambo_id typeId, bambo_id assetId, std::string& str);
		bool HasResource(bambo_id typeId, bambo_id assetId) const;
		void RemoveResource(bambo_id typeId, bambo_id assetId);

	private:
		std::unordered_map<bambo_id, std::unordered_map<bambo_id, std::string>> m_resourcePaths;
		std::string m_destination;
	};
}