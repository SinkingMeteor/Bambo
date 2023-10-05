#pragma once
#include "pch.h"
#include "BufferLayout.h"
namespace Bambo
{
	class BAMBO_API VertexBufferObject
	{
	public:
		VertexBufferObject() = default;
		VertexBufferObject(const VertexBufferObject& vbo) = delete;
		VertexBufferObject& operator=(const VertexBufferObject& vbo) = delete;
		virtual ~VertexBufferObject() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(const void* data, uint32 byteSize) = 0;
		virtual void SetLayout(SPtr<BufferLayout> layout) = 0;
		virtual SPtr<BufferLayout> GetLayout() = 0;

		static SPtr<VertexBufferObject> CreateVertexBufferObject(const void* data, uint32 byteSize);
		static SPtr<VertexBufferObject> CreateVertexBufferObject(uint32 byteSize);
	};
}