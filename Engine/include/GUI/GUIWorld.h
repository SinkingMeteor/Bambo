#pragma once
#include "engpch.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "WindowManager.h"

namespace Bambo
{
	class BAMBO_API GUIWorld
	{
	public:
		GUIWorld() = default;
		void Initialize();
		void StartFrame();
		void EndFrame();
		void Dispose();
	private:
		ImGuiContext* m_context;
	};
}