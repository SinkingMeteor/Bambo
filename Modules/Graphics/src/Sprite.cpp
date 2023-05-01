#include "Sprite.h"

namespace Bambo 
{
	Sprite::Sprite(std::shared_ptr<Texture2D> texture) :
		m_vertices(),
		m_texture(),
		m_spriteRect(),
		m_transform()
	{
		SetTexture(texture);
		SetPivot(glm::vec2{ 0.5f, 0.5f });
	}

	Sprite::Sprite(std::shared_ptr<Texture2D> texture, const RectInt& rect):
		m_vertices(),
		m_texture(texture),
		m_spriteRect(rect),
		m_transform()
	{
		UpdatePosition();
		UpdateTexCoords();
		SetPivot(glm::vec2{ 0.5f, 0.5f });
	}

	void Sprite::SetTexture(std::shared_ptr<Texture2D> texture)
	{
		m_texture = texture;
		SetRect(m_texture->GetTextureRect());
	}


	void Sprite::SetRect(const RectInt& rect) 
	{
		if (m_spriteRect == rect) return;

		m_spriteRect = rect;

		UpdatePosition();
		UpdateTexCoords();
	}

	RectFloat Sprite::GetLocalBounds() const
	{
		float width = static_cast<float>(std::abs(m_spriteRect.Width));
		float height = static_cast<float>(std::abs(m_spriteRect.Height));

		return RectFloat(Vector2f{ 0.f, 0.f }, Vector2f{ width, height });
	}

	void Sprite::Render(Renderer& renderer, const RenderConfig& config) 
	{
		if (!m_texture) return;

		RenderConfig spriteConfig{ config };

		spriteConfig.ModelMatrix.GetInternalMatrix() *= m_transform.GetMatrix().GetInternalMatrix();
		spriteConfig.Primitive = PrimitiveType::TriangleStrip;
		spriteConfig.Texture = m_texture;

		renderer.Draw(m_vertices.data(), m_vertices.size(), spriteConfig);
	}

	void Sprite::UpdatePosition()
	{
		RectFloat bounds = GetLocalBounds();

		m_vertices[0].Position = glm::vec2{0.0f, 0.0f};
		m_vertices[1].Position = glm::vec2{ 0.0f, bounds.Height };
		m_vertices[2].Position = glm::vec2{ bounds.Width, 0.0f };
		m_vertices[3].Position = glm::vec2{ bounds.Width, bounds.Height };
	}

	void Sprite::UpdateTexCoords()
	{
		if (!m_texture) return;

		RectInt texRect = m_texture->GetTextureRect();
		float texWidth = static_cast<float>(texRect.Width);
		float texHeight = static_cast<float>(texRect.Height);

		float left = static_cast<float>(m_spriteRect.Left) / texWidth;
		float right = (left + static_cast<float>(m_spriteRect.Width)) / texWidth;
		float top = static_cast<float>(m_spriteRect.Top) / texHeight;
		float bottom = (top + static_cast<float>(m_spriteRect.Height)) / texHeight;

		m_vertices[0].TexCoord = glm::vec2(left, top);
		m_vertices[1].TexCoord = glm::vec2(left, bottom);
		m_vertices[2].TexCoord = glm::vec2(right, top);
		m_vertices[3].TexCoord = glm::vec2(right, bottom);
	}

	void Sprite::SetPivot(const glm::vec2& relativePivot)
	{
		if (!m_texture) return;

		RectInt textureRect = m_texture->GetTextureRect();
		m_transform.SetOrigin(glm::vec2{ textureRect.Width * relativePivot.x, textureRect.Height * relativePivot.y });
	}

}