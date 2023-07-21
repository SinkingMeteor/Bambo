#include <memory>
#include "Main/Engine.h"
#include "EditorModule.h"
#include "Essentials.h"

int main()
{
	Bambo::Engine engine{};
	engine.Initialize();
	engine.AddModule(std::make_unique<BamboEditor::EditorModule>());
	engine.Run();
	return 0;

}