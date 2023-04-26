#pragma once
#include "pch.h"
#include "Window.h"
#include "Time/Timer.h"
#include "Utils.h"
#include "RenderTarget.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace BEditor
{
	class BamboEditor
	{
	public:
		BamboEditor();
		BamboEditor(const BamboEditor& editor) = delete;
		BamboEditor& operator=(const BamboEditor& editor) = delete;
		~BamboEditor();

		bool Initialize();
		int Run();
	private:
		Bambo::Window m_window;
		Bambo::RenderTarget m_renderTarget;
		ImGuiContext* m_guiContext;

		void Update(float deltaTime);
		void Render();
	};

}

