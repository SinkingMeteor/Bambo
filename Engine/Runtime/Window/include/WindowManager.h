#pragma once
#include "Essentials.h"
#include "Window.h"
#include "SingletonManager.h"
namespace Bambo
{
	class BAMBO_API WindowManager : public ISingleton
	{
		SINGLETON_BODY(WindowManager, 'WNDM')
	public:
		void Initialize(const WindowSettings& settings);
		void Dispose();
		bool WantsToClose() const { return m_window->WindowShouldClose(); }
		void Update() { m_window->Update(); }
		Window& GetWindow() { return *m_window; }
		uint32 GetWindowWidth() const { return m_window->GetWidth(); }
		uint32 GetWindowHeight() const { return m_window->GetHeight(); }
	private:
		std::unique_ptr<Window> m_window;
	};
}