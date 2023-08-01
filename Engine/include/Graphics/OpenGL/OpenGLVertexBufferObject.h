#pragma once
#include "Core/Essentials.h"
#include "Graphics/OpenGL/OpenGLCheck.h"
#include "Graphics/VertexBufferObject.h"

namespace Bambo
{
	class BAMBO_API	OpenGLVertexBufferObject final : public VertexBufferObject
	{
	public:
		OpenGLVertexBufferObject(const void* data, uint32 size);
		OpenGLVertexBufferObject(const OpenGLVertexBufferObject&) = delete;
		OpenGLVertexBufferObject& operator=(const OpenGLVertexBufferObject&) = delete;
		OpenGLVertexBufferObject(uint32 size);
		virtual ~OpenGLVertexBufferObject();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void SetData(const void* data, uint32 size) override;
		virtual void SetLayout(SPtr<BufferLayout> layout) override { m_layout = layout; }
		virtual SPtr<BufferLayout> GetLayout() override { return m_layout; }
	private:
		uint32 m_id;
		uint32 m_size;
		SPtr<BufferLayout> m_layout;
	};
}