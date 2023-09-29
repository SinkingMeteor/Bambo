#pragma once
#include "Essentials.h"
#include "Renderer.h"

namespace Bambo
{
	class World;

	struct LineRenderRequest
	{
	public:
		Vector3f FromPos;
		Vector3f ToPos;
		Color LineColor;
		float Thickness;
	};

	class BAMBO_API DebugLineRenderer : public Renderer
	{
	public:
		DebugLineRenderer(SPtr<Shader> defaultShader);
		void EnqueueLineToRender(const LineRenderRequest& renderRequest);
		void Render(World* world);
	private:
		static constexpr uint32 LINE_VERTEX_COUNT = 4;

		SPtr<VertexBufferObject> m_vbo;
		SPtr<VertexArrayObject> m_vao;
		std::array<QuadVertex, LINE_VERTEX_COUNT> m_renderVertices;
		std::vector<LineRenderRequest> m_lines;
	};
}