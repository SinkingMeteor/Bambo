#include "Project.h"

namespace BamboEditor
{
	bool Project::OpenProject(const std::filesystem::path& projFilePath)
	{
		std::ifstream stream{ projFilePath };
		BAMBO_ASSERT_S(!stream.fail())

		nlohmann::json projectConfig{};
		stream >> projectConfig;
		stream.close();

		if (projectConfig["ProjectName"].is_null()) return false;
		if (projectConfig["ProjectFolderLocation"].is_null()) return false;
		if (projectConfig["AssetsFolderLocation"].is_null()) return false;
		if (projectConfig["FirstWorldLocation"].is_null()) return false;

		SetProjectName(projectConfig["ProjectName"]);
		SetProjectFolderLocation(projectConfig["ProjectFolderLocation"]);
		SetAssetsFolderLocation(projectConfig["AssetsFolderLocation"]);
		SetStartupWorldPath(projectConfig["FirstWorldLocation"]);

		return true;
	}

	void Project::SaveProject()
	{
		std::string projectLocation{ (const char*)m_projectFolderLocation.c_str() };
		std::string fullSavePath = projectLocation + "/" + m_projectName + ".json";
		std::ofstream stream{ fullSavePath };

		if (stream.fail()) return;

		nlohmann::json rootNode{};
		rootNode["ProjectName"] = m_projectName;
		rootNode["FirstWorldLocation"] = m_startupWorldPath;
		rootNode["ProjectFolderLocation"] = m_projectFolderLocation;
		rootNode["AssetsFolderLocation"] = m_assetsFolderLocation;

		stream << rootNode;
		stream.close();
	}

}