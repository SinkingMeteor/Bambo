#include "DebugLineRenderer.h"
#include "RenderManager.h"
#include "World.h"
#include "Engine.h"

namespace Bambo
{
	DebugLineRenderer::DebugLineRenderer(World* world, SPtr<Shader> defaultShader) :
		Renderer(),
		m_vbo(),
		m_vao(),
		m_renderVertices(),
		m_lines()
	{
		Engine* engine = world->GetWorldContext()->Engine;
		RenderAPI renderApi = engine->GetRenderManager()->GetCurrentRenderAPI();

		m_vbo = VertexBufferObject::CreateVertexBufferObject(renderApi, LINE_VERTEX_COUNT * sizeof(QuadVertex));
		m_vao = VertexArrayObject::CreateVertexArrayObject(renderApi);

		m_defaultShader = defaultShader;

		BAMBO_ASSERT(!m_defaultShader.expired() && m_defaultShader.lock(), "Default shader wasn't loaded")

		m_vbo->SetLayout(std::make_shared<BufferLayout>(std::initializer_list{ ShaderDataType::Float3, ShaderDataType::Float2, ShaderDataType::Float4 }));
		m_vao->AddVertexBufferObject(m_vbo);

		m_renderVertices[0] = QuadVertex{};
		m_renderVertices[1] = QuadVertex{};
		m_renderVertices[2] = QuadVertex{};
		m_renderVertices[3] = QuadVertex{};
	}

	void DebugLineRenderer::EnqueueLineToRender(const LineRenderRequest& renderRequest)
	{
		m_lines.push_back(renderRequest);
	}

	void DebugLineRenderer::Render(World* world)
	{
		Engine* engine = world->GetWorldContext()->Engine;
		BAMBO_ASSERT_S(engine);
		RendererImplementation* renderer = engine->GetRenderManager()->GetRenderer();
		BAMBO_ASSERT_S(renderer);

		SPtr<Shader> defaultShader = m_defaultShader.lock();
		BAMBO_ASSERT_S(defaultShader);

		const glm::mat4& projectionMatrix = world->GetCameraManager()->GetProjectionMatrix();
		const glm::mat4& viewMatrix = world->GetCameraManager()->GetViewMatrix();

		defaultShader->Use();
		defaultShader->SetMatrix4("ViewMatrix", viewMatrix);
		defaultShader->SetMatrix4("ProjectionMatrix", projectionMatrix);

		for (size_t i = 0; i < m_lines.size(); ++i)
		{
			LineRenderRequest& drawRequest = m_lines[i];

			Vector3f dir =  drawRequest.FromPos - drawRequest.ToPos;
			glm::vec3 dirNormalized = glm::normalize(glm::vec3{ dir.X, dir.Y, dir.Z });

			glm::vec3 leftDir = glm::rotate(glm::mat4{ 1.0f }, -90.0f, glm::vec3{ 0.0f, 0.0f, 1.0f }) * glm::vec4{ dirNormalized, 0.0f };
			leftDir *= drawRequest.Thickness * 0.5f;
			glm::vec3 rightDir = glm::rotate(glm::mat4{ 1.0f }, 90.0f, glm::vec3{ 0.0f, 0.0f, 1.0f }) * glm::vec4{ dirNormalized, 0.0f };
			rightDir *= drawRequest.Thickness * 0.5f;

			m_renderVertices[0].Position = { drawRequest.FromPos.X + leftDir.x, drawRequest.FromPos.Y + leftDir.y, drawRequest.FromPos.Z + leftDir.z };
			m_renderVertices[0].TexCoord = { 0.0f, 1.0f };
			m_renderVertices[0].Color = drawRequest.LineColor;

			m_renderVertices[1].Position = { drawRequest.FromPos.X + rightDir.x, drawRequest.FromPos.Y + rightDir.y, drawRequest.FromPos.Z + rightDir.z };
			m_renderVertices[1].TexCoord = { 0.0f, 0.0f };
			m_renderVertices[1].Color = drawRequest.LineColor;

			m_renderVertices[2].Position = { drawRequest.ToPos.X + leftDir.x, drawRequest.ToPos.Y + leftDir.y, drawRequest.ToPos.Z + leftDir.z };
			m_renderVertices[2].TexCoord = { 1.0f, 1.0f };
			m_renderVertices[2].Color = drawRequest.LineColor;

			m_renderVertices[3].Position = { drawRequest.ToPos.X + rightDir.x, drawRequest.ToPos.Y + rightDir.y, drawRequest.ToPos.Z + rightDir.z };
			m_renderVertices[3].TexCoord = { 1.0f, 0.0f };
			m_renderVertices[3].Color = drawRequest.LineColor;

			m_vbo->SetData(m_renderVertices.data(), LINE_VERTEX_COUNT * sizeof(QuadVertex));

			renderer->Draw(m_vao, LINE_VERTEX_COUNT, RenderPrimitive::TriangleStrip);
		}

		m_lines.clear();
	}
}