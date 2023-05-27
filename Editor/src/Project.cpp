#include "Project.h"

namespace BamboEditor
{
	Project::Project(const std::string& projectName, const std::string& rootFolder) :
		m_projectName(projectName),
		m_projectLocation(rootFolder)
	{}

	UPtr<Project> Project::LoadProject(const std::string& projectPath)
	{
		std::ifstream input{ projectPath };
		nlohmann::json rootNode;
		input >> rootNode;
		input.close();

		if (rootNode.is_null()) return nullptr;

		const std::string& projectName = rootNode["ProjectName"];
		const std::string& worldLocation = rootNode["FirstWorldLocation"];

		UPtr<Project> project = std::make_unique<Project>(projectName, projectPath);
		project->SetFirstWorldPath(worldLocation);
		return project;
	}

	void Project::SaveProject()
	{
		nlohmann::json rootNode{};

		std::string fullSavePath = m_projectLocation + "/" + m_projectName + ".json";
		std::ofstream stream{ fullSavePath };

		if (stream.fail()) return;

		rootNode["ProjectName"] = m_projectName;
		rootNode["FirstWorldLocation"] = m_projectFirstWorldPath;

		stream << rootNode;
		stream.close();
	}

}