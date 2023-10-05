#pragma once
#include "Essentials.h"
#include "OpenGL/OpenGLCheck.h"
#include "VertexBufferObject.h"

namespace Bambo
{
	class BAMBO_API	OpenGLVertexBufferObject final : public VertexBufferObject
	{
	public:
		OpenGLVertexBufferObject(const void* data, uint32 byteSize);
		OpenGLVertexBufferObject(const OpenGLVertexBufferObject&) = delete;
		OpenGLVertexBufferObject& operator=(const OpenGLVertexBufferObject&) = delete;
		OpenGLVertexBufferObject(uint32 byteSize);
		virtual ~OpenGLVertexBufferObject();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void SetData(const void* data, uint32 byteSize) override;
		virtual void SetLayout(SPtr<BufferLayout> layout) override { m_layout = layout; }
		virtual SPtr<BufferLayout> GetLayout() override { return m_layout; }
	private:
		uint32 m_id;
		uint32 m_size;
		SPtr<BufferLayout> m_layout;
	};
}