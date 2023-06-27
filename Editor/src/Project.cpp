#include "Project.h"

namespace BamboEditor
{
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

}