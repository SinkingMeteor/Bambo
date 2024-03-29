#pragma once
#include "Essentials.h"
#include "OpenGL/OpenGLCheck.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"

namespace Bambo
{
	class BAMBO_API OpenGLVertexArrayObject final : public VertexArrayObject
	{
	public:
		OpenGLVertexArrayObject();
		OpenGLVertexArrayObject(const OpenGLVertexArrayObject&) = delete;
		OpenGLVertexArrayObject& operator=(const OpenGLVertexArrayObject&) = delete;
		virtual ~OpenGLVertexArrayObject();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void AddVertexBufferObject(SPtr<VertexBufferObject> vbo) override;
	private:
		uint32 m_id;
		std::vector<SPtr<VertexBufferObject>> m_vbos;
		int32 m_layoutIndex;
	};
}