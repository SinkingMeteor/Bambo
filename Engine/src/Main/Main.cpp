#include "engpch.h"
#include "Main/Engine.h"
#include "json.hpp"

int main()
{
	Bambo::InitialSettings settings{};
	std::ifstream input{ std::string{ BamboPaths::BamboResourcesDir + "config.json" } };

	if (!input.fail())
	{
		nlohmann::json rootNode{};
		input >> rootNode;

		if (rootNode.is_null())
		{
			Bambo::Logger::Log("EngineLog", Bambo::Verbosity::Error, "Engine configuration file was corrupted or modified.");
		}
		else
		{
			settings.WindowWidth = rootNode["WindowWidth"].get<int>();
			settings.WindowHeight = rootNode["WindowHeight"].get<int>();
			settings.WindowName = rootNode["WindowTitle"].get<std::string>();
		}
	}
	else
	{
		Bambo::Logger::Log("EngineLog", Bambo::Verbosity::Error, "Can't open engine configuration file.");
	}

	input.close();

	Bambo::Engine engine{settings};

	engine.Initialize();
	
	int result = engine.Run();

	return result;
}