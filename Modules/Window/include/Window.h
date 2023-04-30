#pragma once
#include "pch.h"
#include "Utils.h"
#include "WindowSettings.h"
#include "OS.h"
namespace Bambo 
{
	class BAMBO_API Window
	{
	public:
		Window() = default;
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		virtual ~Window();

		virtual void Initialize() = 0;
		virtual uint GetWidth() const = 0;
		virtual uint GetHeight() const = 0;

		virtual bool WindowShouldClose() const = 0;
		virtual void Update() = 0;
		virtual void* GetWindowPtr() = 0;
		virtual void CloseWindow() = 0;

		static std::unique_ptr<Window> CreateBamboWindow(const WindowSettings& settings, OSType osType);
	};
}