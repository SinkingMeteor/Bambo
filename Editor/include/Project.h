#pragma once
#include <string>
#include <memory>
#include "json.hpp"

namespace BamboEditor
{
	class Project final
	{
	public:
		Project(const std::string& projectName, const std::string& rootFolder);
		static UPtr<Project> LoadProject(const std::string& projectPath);
		void SaveProject();

		const std::string& GetName() const { return m_projectName; }
		const std::filesystem::path& GetRootFolder() const { return m_projectLocation; }
		const std::string& GetFirstWorldPath() const { return m_projectFirstWorldPath; }

		void SetFirstWorldPath(const std::string& worldPath) { m_projectFirstWorldPath = worldPath; }

	private:
		std::string m_projectName;
		std::string m_projectFirstWorldPath;

		std::filesystem::path m_projectLocation;
	};
}