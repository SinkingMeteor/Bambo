#pragma once
#include "pch.h"
#include "RenderAPI.h"
#include "Vectors.h"
#include "Color.h"
#include "Vertex.h"
#include "RenderConfig.h"
namespace Bambo
{
	class BAMBO_API Renderer
	{
	public:
		Renderer() = default;
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		virtual ~Renderer() {}
		virtual void Initialize() = 0;
		virtual void SetViewport(const Vector2u& origin, const Vector2u& size) = 0;
		virtual void Draw(const Vertex* vertices, int amount, const RenderConfig& config) = 0;
		virtual void SetClearColor(const Color& color) = 0;
		virtual void Clear() = 0;

		static std::unique_ptr<Renderer> CreateRenderer(RenderAPI renderApi);
	};
}