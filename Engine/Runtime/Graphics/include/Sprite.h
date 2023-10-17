#pragma once
#include "Essentials.h"
#include "Texture2D.h"

namespace Bambo
{
	class BAMBO_API Sprite final
	{
	public:
		Sprite();

		SPtr<Texture2D> GetTexture() const { return m_texture; }

		RectInt GetRect() const;
		glm::vec3& GetOriginRef() { return m_origin; }
		glm::vec3 GetOrigin() const { return m_origin; }
		int32& GetRectIndexRef() { return m_texRectIndex; }
		int32 GetRectIndex() const { return m_texRectIndex; }

		void SetOrigin(const glm::vec3& origin) { m_origin = origin; }
		void SetTexture(SPtr<Texture2D> texture) { m_texture = texture; }
		void SetRectIndex(int32 rectIndex) { m_texRectIndex = rectIndex; }

		glm::vec3 GetOriginOffset() const;

	private:
		SPtr<Texture2D> m_texture{ nullptr };
		glm::vec3 m_origin;
		int32 m_texRectIndex{ 0 };
	};
}