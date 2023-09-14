#include "Essentials.h"
#include "Engine.h"
#include "EditorModule.h"

int main()
{
	Bambo::Engine engine{};
	engine.Initialize();
	engine.AddModule(std::make_unique<BamboEditor::EditorModule>(engine.GetWindow()));
	engine.Run();
	return 0;

}