#pragma once
#include "Essentials.h"

namespace Bambo
{
	class BAMBO_API IndexBufferObject
	{
	public:
		IndexBufferObject() = default;
		virtual ~IndexBufferObject() = default;

		IndexBufferObject(const IndexBufferObject&) = delete;
		IndexBufferObject& operator=(const IndexBufferObject&) = delete;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetIndices(const void* data, std::size_t byteSize) = 0;

		static SPtr<IndexBufferObject> CreateIndexBuffer(std::size_t byteSize);
	};
}