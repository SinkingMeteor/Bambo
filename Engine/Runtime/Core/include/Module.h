#pragma once
#include "Essentials.h"

namespace Bambo
{
	class Engine;

	class BAMBO_API Module
	{
	public:
		Module() = default;
		virtual ~Module() = default;

		virtual int32 GetModuleName() const = 0;

		virtual void OnAttach(Engine* engine) {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTIme) {}
		virtual void OnRender() {}
		virtual void OnGUIStart() {}
		virtual void OnGUI() {}
		virtual void OnGUIEnd() {}
	};
}