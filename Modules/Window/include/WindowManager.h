#pragma once
#include "pch.h"
#include "Singleton.h"
#include "Window.h"
namespace Bambo
{
	class WindowManager : public Singleton<WindowManager>
	{
	public:
		void Initialize(const WindowSettings& settings);
		void Dispose();
		bool WantsToClose() const { return m_window->WindowShouldClose(); }
		void Update() { m_window->Update(); }
		Window& GetWindow() { return *m_window; }
	private:
		std::unique_ptr<Window> m_window;
	};
}