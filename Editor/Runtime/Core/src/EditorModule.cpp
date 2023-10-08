#include "EditorModule.h"
#include "MainEditorState.h"
#include "OpenProjectEditorState.h"
#include "InspectorDrawersRegistry.h"
#include "DefaultDrawers.h"

namespace
{
	const std::filesystem::path CONFIG_FILE_PATH = BamboPaths::EditorResourceDir / "EditorConfig.json";
}

namespace BamboEditor
{
	EditorModule::EditorModule() :
		m_editorContext(),
		m_editorConfig(),
		m_states(),
		m_guiWorld()
	{}

	void EditorModule::OnAttach(Engine* engine)
	{
		m_editorContext.Engine = engine;

		LoadEditorConfig();

		m_guiWorld.Initialize(m_editorContext.Engine->GetWindowManager()->GetWindow());
		m_editorContext.CurrentProject = std::make_unique<Project>();

		m_states.AddState(std::make_shared<OpenProjectEditorState>(&m_editorContext, &m_editorConfig, &m_states));
		m_states.AddState(std::make_shared<MainEditorState>(&m_editorContext));

		InspectorDrawersRegistry* drawerRegistry = SingletonManager::Get()->Register<InspectorDrawersRegistry>();
		drawerRegistry->Register(SpriteComponent::GetTypeID(), DrawSpriteComponent);
		drawerRegistry->Register(CameraComponent::GetTypeID(), DrawCameraComponent);
		drawerRegistry->Register(TextComponent::GetTypeID(), DrawTextComponent);

		m_states.EnterTo(static_cast<uint32>(EditorStateType::OpenProject));
	}

	void EditorModule::OnDetach()
	{
		SaveEditorConfig();

		m_states.ExitCurrentState();
		m_states.Clear();
		m_guiWorld.Dispose();
	}

	void EditorModule::OnUpdate(float deltaTime)
	{
		IEditorState* editorState = m_states.GetCurrentState();
		if (!editorState) return;

		editorState->OnUpdate(deltaTime);
	}
	
	void EditorModule::OnRender()
	{
		IEditorState* editorState = m_states.GetCurrentState();
		if (!editorState) return;
		editorState->OnRender();
	}

	void EditorModule::OnGUIStart()
	{
		m_guiWorld.StartFrame();
	}

	void EditorModule::OnGUI()
	{
		IEditorState* editorState = m_states.GetCurrentState();
		if (!editorState) return;
		editorState->OnGUI();
	}

	void EditorModule::OnGUIEnd()
	{
		m_guiWorld.EndFrame();
	}

	void EditorModule::LoadEditorConfig()
	{
		if (!std::filesystem::exists(CONFIG_FILE_PATH)) 
		{
			SaveEditorConfig();
		}

		std::ifstream configStream{ CONFIG_FILE_PATH };
		BAMBO_ASSERT_S(!configStream.fail())

		nlohmann::json configRoot{};
		configStream >> configRoot;
		configStream.close();

		m_editorConfig.Projects = configRoot["projectsPaths"].get<std::vector<std::string>>();
	}

	void EditorModule::SaveEditorConfig()
	{
		std::ofstream configStream{ CONFIG_FILE_PATH };
		BAMBO_ASSERT_S(!configStream.fail())

		nlohmann::json configRoot{};
		configRoot["projectsPaths"] = m_editorConfig.Projects;
		configStream << configRoot;
		configStream.close();

	}
}