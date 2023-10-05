#pragma once
#include "Essentials.h"
#include "RenderAPI.h"
#include "Color.h"
#include "Vertex.h"
#include "RenderConfig.h"
#include "VertexArrayObject.h"
#include "IndexBufferObject.h"
namespace Bambo
{
	enum class RenderPrimitive
	{
		TriangleStrip = 0,
		Triangle
	};

	class BAMBO_API RendererImplementation
	{
	public:
		RendererImplementation() = default;
		RendererImplementation(const RendererImplementation&) = delete;
		RendererImplementation& operator=(const RendererImplementation&) = delete;
		virtual ~RendererImplementation() {}
		virtual void Initialize() = 0;
		virtual void SetViewport(const Vector2u& origin, const Vector2u& size) = 0;
		virtual void Draw(const SPtr<VertexArrayObject> vao, uint32 vertexAmount, RenderPrimitive primitive) = 0;
		virtual void DrawIndexed(const SPtr<VertexArrayObject> vao, const SPtr<IndexBufferObject> ibo, uint32 vertexAmount, RenderPrimitive primitive) = 0;
		virtual void SetClearColor(const Color& color) = 0;
		virtual void Clear() = 0;

		static std::unique_ptr<RendererImplementation> CreateRenderer();
	};
}