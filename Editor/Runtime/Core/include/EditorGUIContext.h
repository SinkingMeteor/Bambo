#pragma once
#include "Essentials.h"
#include "WindowManager.h"
#include "EditorEssentials.h"

namespace BamboEditor
{
	class EditorGUIContext final
	{
	public:
		EditorGUIContext();
		void Initialize(Bambo::Window* targetWindow);
		void StartFrame();
		void EndFrame();
		void Dispose();
	private:
		ImGuiContext* m_context;
		Bambo::Window* m_targetWindow;
	};
}