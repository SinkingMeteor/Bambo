#pragma once
#include "pch.h"
#include "Window.h"
#include "Input.h"
#include "Time/Timer.h"
#include "Utils.h"
#include "TextureProvider.h"
#include "ShaderProvider.h"
#include "AudioProvider.h"
#include "Sound.h"
#include "AudioDevice.h"
#include "AudioListener.h"
#include "Sprite.h"
#include "Utils.h"

class Engine 
{
public:
	Engine();
	Engine(const Engine& engine) = delete;
	Engine& operator=(const Engine& engine) = delete;
	~Engine();
	[[nodiscard]] int Run();
private:
	void Initialize();
	void Update(float deltaTime);
	void Render();

	Bambo::Window m_window;
	Bambo::Input m_input;
	Bambo::TextureProvider m_textureProvider;
	Bambo::ShaderProvider m_shaderProvider;
	Bambo::AudioProvider m_audioProvider;

	Bambo::RenderTarget m_renderTarget;

	std::unique_ptr<Bambo::Sprite> m_testSprite;
	std::shared_ptr<Bambo::Camera> m_camera;
	std::shared_ptr<Bambo::AudioDevice> m_audioDevice;
	Bambo::AudioListener m_audioListener;
	Bambo::Sound m_audioSource;
};
