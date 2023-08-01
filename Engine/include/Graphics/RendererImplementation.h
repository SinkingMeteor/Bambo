#pragma once
#include "Core/Essentials.h"
#include "Graphics/RenderAPI.h"
#include "Core/Color.h"
#include "Graphics/Vertex.h"
#include "Graphics/RenderConfig.h"
#include "Graphics/VertexArrayObject.h"
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
		virtual void Draw(const SPtr<VertexArrayObject> vao, uint32 vertexAmount) = 0;
		virtual void SetClearColor(const Color& color) = 0;
		virtual void Clear() = 0;

		static std::unique_ptr<RendererImplementation> CreateRenderer();
	};
}