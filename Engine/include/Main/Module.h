#pragma once
#include "engpch.h"
#include "EngineEvent.h"
namespace Bambo
{
	class BAMBO_API Module
	{
	public:
		Module() = default;
		virtual ~Module() = default;

		virtual int32 GetModuleName() const = 0;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTIme) {}
		virtual void OnGUI() {}
		virtual void OnEvent(Event& event) {}
	};
}