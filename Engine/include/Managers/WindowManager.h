#pragma once
#include "engpch.h"
#include "Managers/Singleton.h"
#include "Window.h"
#include "WindowSettings.h"
namespace Bambo
{
	class WindowManager : public Singleton<WindowManager>
	{
	public:
		void Initialize(const WindowSettings& settings);
		void Dispose();
		bool WantsToClose() const { return m_window->WindowShouldClose(); }
		void Update() { m_window->Update(); }
	private:
		std::unique_ptr<Window> m_window;
	};
}