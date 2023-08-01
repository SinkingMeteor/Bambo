#pragma once
#include "Core/Essentials.h"
#include "Graphics/OpenGL/OpenGLCheck.h"
#include "Graphics/RendererImplementation.h"
#include "Graphics/VertexArrayObject.h"
#include "Graphics/VertexBufferObject.h"

namespace Bambo
{
	class BAMBO_API OpenGLRenderer final : public RendererImplementation
	{
	public:
		OpenGLRenderer() = default;
		virtual void Initialize() override;
		virtual void SetViewport(const Vector2u& origin, const Vector2u& size) override;
		virtual void Draw(const SPtr<VertexArrayObject> vao, uint32 vertexAmount) override;
		virtual void SetClearColor(const Color& color) override;
		virtual void Clear() override;
	};
}