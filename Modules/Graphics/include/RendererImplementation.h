#pragma once
#include "pch.h"
#include "RenderAPI.h"
#include "Vectors.h"
#include "Color.h"
#include "Vertex.h"
#include "RenderConfig.h"
namespace Bambo
{
	class BAMBO_API RendererImplementation
	{
	public:
		RendererImplementation() = default;
		RendererImplementation(const RendererImplementation&) = delete;
		RendererImplementation& operator=(const RendererImplementation&) = delete;
		virtual ~RendererImplementation() {}
		virtual void Initialize() = 0;
		virtual void SetViewport(const Vector2u& origin, const Vector2u& size) = 0;
		virtual void Draw(const void* vertices, int bytesAmount, const RenderConfig& config) = 0;
		virtual void SetClearColor(const Color& color) = 0;
		virtual void Clear() = 0;

		static std::unique_ptr<RendererImplementation> CreateRenderer(RenderAPI renderApi);
	};
}