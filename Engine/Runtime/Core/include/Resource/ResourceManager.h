#pragma once
#include "Essentials.h"
#include "ResourceInfo.h"
#include "SingletonManager.h"
namespace Bambo
{
	class BAMBO_API ResourceManager : public ISingleton
	{
		SINGLETON_BODY(ResourceManager, 'RESM')
	public:
		ResourceManager();
		void ScanFiles(const std::filesystem::path& startPath);
		bool HasFile(bambo_id id);
		ResourceInfo* GetFile(bambo_id id);
		void AddFile(ResourceInfo&& fileInfo);
	private:
		std::unordered_map<bambo_id, ResourceInfo> m_resources;
	};
}
