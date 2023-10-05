#include "OpenGL/OpenGLIndexBufferObject.h"
#include "OpenGL/OpenGLCheck.h"

namespace Bambo
{
	OpenGLIndexBufferObject::OpenGLIndexBufferObject(std::size_t byteSize) :
		m_id(0),
		m_size(byteSize)
	{
		OpenGLCheck(glGenBuffers(1, &m_id));
		OpenGLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
		OpenGLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize * sizeof(uint32), nullptr, GL_STATIC_DRAW));
		OpenGLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	OpenGLIndexBufferObject::~OpenGLIndexBufferObject()
	{
		OpenGLCheck(glDeleteBuffers(1, &m_id));
	}

	void OpenGLIndexBufferObject::Bind()
	{
		OpenGLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	}

	void OpenGLIndexBufferObject::Unbind()
	{
		OpenGLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void OpenGLIndexBufferObject::SetIndices(const void* data, std::size_t byteSize)
	{
		Bind();

		if (m_size < byteSize)
		{
			m_size = byteSize;
			OpenGLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize * sizeof(uint32), data, GL_STATIC_DRAW));
			return;
		}

		OpenGLCheck(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_size * sizeof(uint32), data));

		Unbind();
	}
}