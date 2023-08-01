#pragma once
#include "Core/Essentials.h"
#include "Window/WindowManager.h"
#include "EditorEssentials.h"

namespace BamboEditor
{
	class GUIWorld
	{
	public:
		GUIWorld(Bambo::Window* targetWindow) : m_targetWindow(targetWindow) {}
		void Initialize();
		void StartFrame();
		void EndFrame();
		void Dispose();
	private:
		ImGuiContext* m_context;
		Bambo::Window* m_targetWindow;
	};
}