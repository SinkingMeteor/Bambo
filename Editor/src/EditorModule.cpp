#include "EditorModule.h"

namespace BamboEditor
{
	void EditorModule::OnAttach()
	{
		m_currentWorld = std::make_shared<Bambo::World>();
		m_windows.emplace_back<UPtr<SceneHierarchyWindow>>(std::make_unique<SceneHierarchyWindow>(m_currentWorld));

		Bambo::WindowManager* windowManager = Bambo::WindowManager::Get();
		uint32 width = windowManager->GetWindowWidth();
		uint32 height = windowManager->GetWindowHeight();

		m_framebuffer = Bambo::Framebuffer::Create({ Bambo::FramebufferTextureType::Color }, width, height);
		m_windows.emplace_back<UPtr<GameViewportWindow>>(std::make_unique<GameViewportWindow>(m_framebuffer));


		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;

		//Загрузить config эдитора. В нем должны находиться все пути к проектам. Загрузить проект -> Загрузить мир

		std::ifstream editorConfigiStream{ BamboPaths::BamboEditorConfigDir };
		if (editorConfigiStream.fail())
		{
			//Проект-заглушка. В будущем заменить на диалоговое окно
			m_currentProject = std::make_unique<Project>("MockProject", BamboPaths::BamboEditorResourceDir);
			m_windows.emplace_back<UPtr<ContentBrowserWindow>>(std::make_unique<ContentBrowserWindow>(m_currentProject));

			OpenWorld();

			Bambo::Entity& cameraEntity = m_currentWorld->CreateEntity();
			Bambo::CameraComponent* camera = cameraEntity.AddComponent<Bambo::CameraComponent>();
			camera->Camera.SetViewportSize(Bambo::WindowManager::Get()->GetWindowWidth(), Bambo::WindowManager::Get()->GetWindowHeight());

			SPtr<Bambo::Texture2D> tex = Bambo::TextureProvider::Get()->Load(Bambo::ToId("TestImage"), BamboPaths::BamboResourcesDir + "Textures/TestImage.png");
			Bambo::SpriteComponent spriteData{ tex };
			m_currentWorld->CreateEntity("TestSprite").AddComponent<Bambo::SpriteComponent>(spriteData);

			return;
		}

		nlohmann::json rootConfig{};
		rootConfig << editorConfigiStream;
		BAMBO_ASSERT_S(!rootConfig.is_null())

		//Вот тут, по идее, должен храниться список доступных проектов. Но пока он только один

		const std::string& projectName = rootConfig["CurrentProjectName"];
		const std::string& projectLocation = rootConfig["CurrentProjectLocation"];
		const std::string& projectFirstWorldPath = rootConfig["CurrentProjectFirstWorldPath"];
		
		m_currentProject = std::make_shared<Project>(projectName, projectLocation);
		m_currentProject->SetFirstWorldPath(projectFirstWorldPath);

		m_windows.emplace_back<UPtr<ContentBrowserWindow>>(std::make_unique<ContentBrowserWindow>(m_currentProject));

		if (projectFirstWorldPath.size() == 0)
		{
			OpenWorld();
		}
		else
		{
			OpenWorld(projectFirstWorldPath);
		}
	}

	void EditorModule::OnDetach()
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}
	}

	void EditorModule::OnUpdate(float deltaTime)
	{
		if (m_currentWorld)
		{
			m_currentWorld->Update(deltaTime);
		}
	}
	
	void EditorModule::OnRender()
	{
		Bambo::RenderManager* renderManager = Bambo::RenderManager::Get();
		renderManager->GetRenderer().Clear();

		m_framebuffer->Bind();

		renderManager->GetRenderer().Clear();

		if (m_currentWorld)
		{
			m_currentWorld->Render();
		}

		m_framebuffer->Unbind();
	}


	void EditorModule::OnGUI()
	{
		bool isToolActive = true;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::DockSpaceOverViewport(viewport, ImGuiDockNodeFlags_::ImGuiDockNodeFlags_PassthruCentralNode);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W")) { isToolActive = false; }
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		for (UPtr<GUIWindow>& window : m_windows)
		{
			window->OnGUI();
		}

		ImGui::ShowDemoWindow();
	}

	void EditorModule::OnEvent(Bambo::Event& event)
	{

	}

	void EditorModule::OpenWorld()
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}
		m_currentWorld->Initialize();
	}

}