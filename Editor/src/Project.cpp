#include "Project.h"

namespace BamboEditor
{
	bool Project::LoadProject(const std::filesystem::path& projectPath, const std::string& projectName)
	{
		if (projectPath.empty()) return false;

		std::string projectFullName = projectName + ".bproj";
		std::string strProjectPath = projectPath.string();
		std::filesystem::path fullpath = projectPath / projectFullName;
		
		std::ifstream input{ fullpath };
		
		nlohmann::json rootConfig{};

		if (input.fail())
		{
			std::string assetsNewPath = (projectPath / "Assets").string();

			if (!CreateDirectory(assetsNewPath.c_str(), NULL))
			{
				BAMBO_ASSERT(false, "Can't create a directory while constructing a project")
			}

			std::ofstream outProject{ fullpath };
			rootConfig["ProjectFolderLocation"] = projectPath.string();
			rootConfig["AssetsFolderLocation"] = assetsNewPath;
			rootConfig["FirstWorldLocation"] = "TemplateWorld.bworld";
			rootConfig["ProjectName"] = projectName;
			outProject << std::setw(4) << rootConfig;
			outProject.close();
		}
		else
		{
			input >> rootConfig;
			input.close();
		}

		BAMBO_ASSERT_S(!rootConfig.is_null())

		m_projectName = rootConfig["ProjectName"];
		m_startupWorldPath = rootConfig["FirstWorldLocation"].get<std::string>();
		m_projectFolderLocation = rootConfig["ProjectFolderLocation"].get<std::string>();
		m_assetsFolderLocation = rootConfig["AssetsFolderLocation"].get<std::string>();

		return true;
	}

	void Project::SaveProject()
	{
		nlohmann::json rootNode{};

		std::string projectLocation{ (const char*)m_projectFolderLocation.c_str() };
		std::string fullSavePath = projectLocation + "/" + m_projectName + ".json";
		std::ofstream stream{ fullSavePath };

		if (stream.fail()) return;

		rootNode["ProjectName"] = m_projectName;
		rootNode["FirstWorldLocation"] = m_startupWorldPath;
		rootNode["ProjectFolderLocation"] = m_projectFolderLocation;
		rootNode["AssetsFolderLocation"] = m_assetsFolderLocation;

		stream << rootNode;
		stream.close();
	}

	void Project::CreateDefaultProject()
	{
		m_projectName = "Unknown project";
		m_projectFolderLocation = "";
		m_assetsFolderLocation = "";
		m_startupWorldPath = "";
	}
}