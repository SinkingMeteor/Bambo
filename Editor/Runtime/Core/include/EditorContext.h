#pragma once
#include "Essentials.h"
#include "Project.h"
#include "World.h"
#include "Engine.h"
#include "EditorCamera.h"

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
		EditorCamera* EditorCamera;
	};

	struct EditorConfig
	{
		std::vector<std::string> Projects{};
	};
}