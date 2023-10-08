#pragma once
#include "Essentials.h"
#include "Project.h"
#include "World.h"
#include "Engine.h"

namespace BamboEditor
{
	class EditorModule;

	struct EditorContext
	{
		SPtr<Project> CurrentProject{};
		SPtr<Bambo::World> CurrentWorld{};
		Bambo::IID SelectedGameObject{};
		Bambo::Engine* Engine;
		EditorModule* Editor;
	};

	struct EditorConfig
	{
		std::vector<std::string> Projects{};
	};
}