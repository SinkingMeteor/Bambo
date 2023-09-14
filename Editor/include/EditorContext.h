#pragma once
#include "Essentials.h"
#include "Project.h"
#include "World.h"

namespace BamboEditor
{

	struct EditorContext
	{
		SPtr<Project> CurrentProject{};
		SPtr<Bambo::World> CurrentWorld{};
		Bambo::IID SelectedGameObject{};
	};
}