#include "Renderer2D.h"

namespace Bambo
{
	static constexpr uint32 SPRITE_VERTEX_COUNT = 4;

	Renderer2D::Renderer2D() :
		Renderer(),
		m_vbo(VertexBufferObject::CreateVertexBufferObject(4 * sizeof(QuadVertex))),
		m_vao(VertexArrayObject::CreateVertexArrayObject())
	{
		m_vbo->SetLayout(std::make_shared<BufferLayout>(std::initializer_list{ ShaderDataType::Float3, ShaderDataType::Float2, ShaderDataType::Float4 }));
		m_vao->AddVertexBufferObject(m_vbo);
	}

	void Renderer2D::Render(const SPtr<Sprite> sprite, const RenderConfig& renderConfig)
	{
		if (m_camera.expired()) return;

		m_vbo->SetData(sprite->m_vertices.data(), SPRITE_VERTEX_COUNT * sizeof(QuadVertex));

		renderConfig.Shader->Use();
		glm::mat4 modelMatrix = renderConfig.ModelMatrix.GetInternalMatrix() * sprite->GetTransform().GetMatrix().GetInternalMatrix();
		renderConfig.Shader->SetMatrix4("model", modelMatrix);
		renderConfig.Shader->SetMatrix4("projView", m_camera.lock()->GetProjViewMatrix());

		if (sprite->m_texture)
		{
			sprite->m_texture->Use();
		}

		RenderInternal(m_vao, SPRITE_VERTEX_COUNT);
	}
}