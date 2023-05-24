#include "Main/Engine.h"
#include "Main/Module.h"
#include "World/World.h"
#include "World/Entity.h"
#include "World/Components/Components.h"
#include "imgui.h"
#include <memory>

using namespace Bambo;

class TestModule : public Bambo::Module
{
public:
	TestModule() : m_world(std::make_unique<Bambo::World>()) {}

	virtual int32 GetModuleName() const override { return 'TSTM'; }

	virtual void OnAttach() override
	{
		m_world->Initialize();

		Entity& camera = m_world->CreateEntity("Camera");
		CameraComponent* cameraComponent = camera.AddComponent<CameraComponent>(CameraComponent{});
		cameraComponent->Camera.SetViewportSize(WindowManager::Get()->GetWindow().GetWidth(), WindowManager::Get()->GetWindow().GetHeight());

		std::shared_ptr<Texture2D> texture = TextureProvider::Get()->GetResource(ToId("TestTexture"));

		Entity& sprite = m_world->CreateEntity("Sprite");
		sprite.AddComponent<SpriteComponent>(SpriteComponent{ texture });
	}
	virtual void OnDetach() override
	{
		m_world->Dispose();
	}
	virtual void OnUpdate(float deltaTime) override
	{
		m_world->Update(deltaTime);
	}
	virtual void Render() override
	{
		m_world->Render();
	}
	virtual void OnGUI() override
	{
		ImGui::ShowDemoWindow();
	}



private:
	std::unique_ptr<Bambo::World> m_world;
	std::string m_moduleName = "Polygon";
};

int main()
{
	Bambo::Engine engine{};
	engine.Initialize();
	engine.AddModule(std::make_unique<TestModule>());

	engine.Run();
	return 0;
}