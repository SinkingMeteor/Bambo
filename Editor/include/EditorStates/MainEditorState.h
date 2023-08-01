#pragma once
#include "Core/Essentials.h"
#include "EditorEssentials.h"
#include "EditorStates/IEditorState.h"
#include "Project.h"
#include "World/World.h"
#include "Windows/GUIWindow.h"
#include "Graphics/Framebuffer.h"
#include "EditorContext.h"

namespace BamboEditor
{
	class MainEditorState final : public IEditorState
	{
	public:
		MainEditorState(EditorContext* editorContext);
		virtual uint32 GetId() const override { return static_cast<uint32>(EditorStateType::Main); };
		virtual void Enter() override;
		virtual void Exit() override;

		virtual void OnUpdate(float deltaTIme) override;
		virtual void OnRender() override;
		virtual void OnGUI() override;
	private:
		EditorContext* m_editorContext;
		std::vector<UPtr<GUIWindow>> m_windows;
		SPtr<Bambo::Framebuffer> m_framebuffer;
		Bambo::TextureProvider m_textureProvider;

		void OpenWorld(const std::filesystem::path& worldFilePath);
		void SaveProject();
		void DispatchNewProject();
	};
}