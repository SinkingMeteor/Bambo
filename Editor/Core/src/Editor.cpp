#include "Editor.h"

namespace BEditor
{
	BamboEditor::BamboEditor() :
		m_window(std::make_shared<Bambo::WindowSettings>(Bambo::WindowSettings{ 1280u, 720u, "Bambo Editor" })),
		m_renderTarget(m_window.GetSettings()),
		m_guiContext(nullptr)
	{
	}

	BamboEditor::~BamboEditor()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext(m_guiContext);
	}

	bool BamboEditor::Initialize()
	{
		int result = m_window.Initialize();
		m_renderTarget.Initialize();

		m_guiContext = ImGui::CreateContext();
		ImGui::SetCurrentContext(m_guiContext);
		ImGui_ImplGlfw_InitForOpenGL(m_window.GetRawWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 130");

		return result;
	}

	int BamboEditor::Run()
	{
		Bambo::Timer timer{};
		const float deltaTime = 1.0f / 60.0f;

		while (!m_window.WindowShouldClose())
		{
			float passedTime = timer.Restart();

			while (passedTime > deltaTime)
			{
				passedTime -= deltaTime;
				Update(deltaTime);
			}
			Update(passedTime);
			Render();
		}

		return 0;
	}

	void BamboEditor::Update(float deltaTime)
	{
	}

	void BamboEditor::Render() 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		bool showDemoWindow = true;
		ImGui::ShowDemoWindow(&showDemoWindow);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_window.GetRawWindow());
		glfwPollEvents();
	}
}
