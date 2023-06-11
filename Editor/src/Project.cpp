#include "Project.h"

namespace BamboEditor
{
	bool Project::LoadProject(const std::string& projectPath)
	{
		std::ifstream input{ projectPath };
		nlohmann::json rootNode;
		input >> rootNode;
		input.close();

		if (rootNode.is_null()) return false;

		m_projectName = rootNode["ProjectName"];
		m_startupWorldPath = rootNode["FirstWorldLocation"].get<std::string>();
		m_projectFolderLocation = rootNode["ProjectFolderLocation"].get<std::string>();
		m_assetsFolderLocation = rootNode["AssetsFolderLocation"].get<std::string>();

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