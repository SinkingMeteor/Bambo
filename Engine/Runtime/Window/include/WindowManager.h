#pragma once
#include "Essentials.h"
#include "Window.h"
#include "RenderAPI.h"

namespace Bambo
{
	class BAMBO_API WindowManager final
	{
	public:
		WindowManager() = default;
		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;
		void Initialize(const WindowSettings& settings, RenderAPI renderApi);
		void Dispose();
		bool WantsToClose() const { return m_window->WindowShouldClose(); }
		void Update() { m_window->Update(); }
		Window* GetWindow() { return m_window.get(); }
		uint32 GetWindowWidth() const { return m_window->GetWidth(); }
		uint32 GetWindowHeight() const { return m_window->GetHeight(); }
	private:
		std::unique_ptr<Window> m_window;
	};
}