#pragma once
#include "Essentials.h"
#include "WindowManager.h"
#include "EditorEssentials.h"

namespace BamboEditor
{
	class EditorGUIContext final
	{
	public:
		EditorGUIContext(Bambo::Window* targetWindow) : m_targetWindow(targetWindow) {}
		void Initialize();
		void StartFrame();
		void EndFrame();
		void Dispose();
	private:
		ImGuiContext* m_context;
		Bambo::Window* m_targetWindow;
	};
}