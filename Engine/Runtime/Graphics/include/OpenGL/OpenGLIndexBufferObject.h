#pragma once
#include "Essentials.h"
#include "IndexBufferObject.h"

namespace Bambo
{
	class BAMBO_API OpenGLIndexBufferObject final : public IndexBufferObject
	{
	public:
		OpenGLIndexBufferObject(std::size_t byteSize);
		virtual ~OpenGLIndexBufferObject();

		void Bind() override;
		void Unbind() override;
		void SetIndices(const void* data, std::size_t byteSize) override;
	private:
		GLuint m_id;
		std::size_t m_size;
	};
}