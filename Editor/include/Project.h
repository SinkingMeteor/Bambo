#pragma once
#include "engpch.h"
#include <string>
#include <memory>
#include "json.hpp"

namespace BamboEditor
{
	class Project final
	{
	public:
		Project() = default;
		Project(const Project& project) = default;
		Project& operator=(const Project& project) = default;
		~Project() = default;

		void SaveProject();

		const std::string& GetName() const { return m_projectName; }
		const std::filesystem::path& GetRootPath() const { return m_projectFolderLocation; }
		const std::filesystem::path& GetAssetsPath() const { return m_assetsFolderLocation; }
		const std::filesystem::path& GetStartupWorldPath() const { return m_startupWorldPath; }

		void SetProjectName(const std::string& projectName) { m_projectName = projectName; }
		void SetStartupWorldPath(const std::string& worldPath) { m_startupWorldPath = worldPath; }
		void SetProjectFolderLocation(const std::string& projectLocation) { m_projectFolderLocation = projectLocation; }
		void SetAssetsFolderLocation(const std::string& assetsLocation) { m_assetsFolderLocation = assetsLocation; }
	private:
		std::string m_projectName;

		std::filesystem::path m_startupWorldPath;
		std::filesystem::path m_projectFolderLocation;
		std::filesystem::path m_assetsFolderLocation;
	};
}