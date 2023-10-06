#pragma once
#include "pch.h"
#include "VertexBufferObject.h"
#include "RenderAPI.h"
namespace Bambo
{
	class BAMBO_API VertexArrayObject
	{
	public:
		VertexArrayObject() = default;
		VertexArrayObject(const VertexArrayObject& vao) = delete;
		VertexArrayObject& operator=(const VertexArrayObject& vao) = delete;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void AddVertexBufferObject(SPtr<VertexBufferObject> vbo) = 0;
		virtual ~VertexArrayObject() {}

		static SPtr<VertexArrayObject> CreateVertexArrayObject(RenderAPI renderApi);
	};
}