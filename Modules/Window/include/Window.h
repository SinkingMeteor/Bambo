#pragma once
#include "pch.h"
#include "Essentials.h"
#include "Utils.h"
#include "OS.h"

namespace Bambo 
{
	struct WindowSettings
	{
	public:
		uint32 Width{ 1 };
		uint32 Height{ 1 };
		std::string Title{};
	};

	using OnWindowResizedDelegate = MulticastDelegate<void(uint32, uint32)>; //width, height

	class BAMBO_API Window
	{
	public:

		Window() = default;
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		virtual ~Window() = default;

		virtual void Initialize() = 0;
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;
		virtual bool WindowShouldClose() const = 0;
		virtual void Update() = 0;
		virtual void* GetWindowPtr() = 0;
		virtual void CloseWindow() = 0;

		OnWindowResizedDelegate& OnWindowResized() { return m_onWindowResized; }

		static std::unique_ptr<Window> CreateBamboWindow(const WindowSettings& settings, OSType osType);
	protected:
		OnWindowResizedDelegate m_onWindowResized;
	};
}