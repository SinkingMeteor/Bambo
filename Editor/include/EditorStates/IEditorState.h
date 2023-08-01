#pragma once
#include "Core/Essentials.h"
#include "Core/Patterns/StateMachine.h"

namespace BamboEditor
{
	enum class EditorStateType
	{
		OpenProject = 0,
		Main
	};

	class IEditorState : public Bambo::IState
	{
	public:
		IEditorState() = default;
		virtual ~IEditorState() = default;

		virtual void OnUpdate(float deltaTIme) = 0;
		virtual void OnRender() = 0;
		virtual void OnGUI() = 0;
	};
}