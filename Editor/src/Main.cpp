#include <memory>
#include "Main/Engine.h"
#include "EditorModule.h"
#include "Essentials.h"

class FooClass
{
public:
	void Say() { printf("Hello super world!"); }
};

int main()
{
	FooClass foo{};
	Bambo::Delegate<void()> helloDelegate{};
	helloDelegate.Bind(foo, &FooClass::Say);
	helloDelegate.Invoke();

	Bambo::Engine engine{};
	engine.Initialize();
	engine.AddModule(std::make_unique<BamboEditor::EditorModule>());
	engine.Run();
	return 0;

}