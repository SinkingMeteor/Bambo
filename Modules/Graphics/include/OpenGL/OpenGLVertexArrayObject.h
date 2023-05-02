#pragma once
#include "pch.h"
#include "Graphics.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"

namespace Bambo
{
	class BAMBO_API OpenGLVertexArrayObject final : public VertexArrayObject
	{
	public:
		OpenGLVertexArrayObject();
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