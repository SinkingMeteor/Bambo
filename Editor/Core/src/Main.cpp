#include "Editor.h"

int main()
{
	BEditor::BamboEditor editor{};

	if (!editor.Initialize())
	{
		return -1;
	}

	int result = editor.Run();

	return result;
}