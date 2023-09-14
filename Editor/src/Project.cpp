#include "Project.h"
#include "World.h"

namespace
{
	const std::string TEMPLATE_WORLD_FILE_ASSET_LOCATION = "FirstWorld";
}

DECLARE_LOG_CATEGORY_STATIC(ProjectLog)

namespace BamboEditor
{
	void Project::CreateNewProjectFile(const std::filesystem::path& projFilePath)
	{
		Bambo::Logger::Get()->Log("ProjectBrowserLog", Bambo::Verbosity::Info, "%s", projFilePath.filename());

		std::filesystem::path assetsNewPath{ projFilePath.parent_path() / "Assets" };

		if (!CreateDirectory(assetsNewPath.string().c_str(), NULL))
		{
			Bambo::Logger::Get()->Log(ProjectLog, Bambo::Verbosity::Fatal, "Can't create an asset directory while constructing a project");
		}

		nlohmann::json rootConfig{};
		std::ofstream outProject{ projFilePath };

		BAMBO_ASSERT_S(!outProject.fail())
		BAMBO_ASSERT_S(projFilePath.has_filename())

		std::filesystem::path firstWorldPath = assetsNewPath / (TEMPLATE_WORLD_FILE_ASSET_LOCATION + Bambo::WORLD_FILE_EXTENSION_DOT);

		rootConfig["ProjectFolderLocation"] = projFilePath.string();
		rootConfig["AssetsFolderLocation"] = assetsNewPath.string();
		rootConfig["FirstWorldLocation"] = firstWorldPath.string();
		rootConfig["ProjectName"] = projFilePath.filename().replace_extension().string();
		outProject << std::setw(4) << rootConfig;

		outProject.close();
	}

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