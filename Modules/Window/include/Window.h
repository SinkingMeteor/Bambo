#pragma once
#include "pch.h"
#include "Utils.h"
#include "EngineEvent.h"
#include "OS.h"

namespace Bambo 
{
	using EventCallback = std::function<void(Event&)>;

	struct WindowSettings
	{
	public:
		uint32 Width{ 1 };
		uint32 Height{ 1 };
		std::string Title{};
	};

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
		virtual void SetEventCallback(const EventCallback& callback) = 0;
		virtual bool WindowShouldClose() const = 0;
		virtual void Update() = 0;
		virtual void* GetWindowPtr() = 0;
		virtual void CloseWindow() = 0;

		static std::unique_ptr<Window> CreateBamboWindow(const WindowSettings& settings, OSType osType);
	};
}