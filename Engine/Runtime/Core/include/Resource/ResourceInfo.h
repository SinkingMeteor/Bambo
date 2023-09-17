#pragma once
#include "Essentials.h"

namespace Bambo
{
	struct ResourceInfo
	{
	public:
		bambo_id TypeId{0u};
		bambo_id AssetId{0u};
		std::filesystem::path FullPath{};
		std::filesystem::path FileName{};
		std::filesystem::path Extension{};

		void LoadInfo(const std::filesystem::path& pathFromLoadMeta);
		void SaveInfo();
		static ResourceInfo Create(bambo_id assetId, bambo_id typeId, const std::filesystem::path& fullpath);
	};
}