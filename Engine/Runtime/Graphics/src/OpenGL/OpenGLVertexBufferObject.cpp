#include "OpenGL/OpenGLVertexBufferObject.h"

namespace Bambo
{
	OpenGLVertexBufferObject::OpenGLVertexBufferObject(const void* data, uint32 byteSize) :
		VertexBufferObject(),
		m_id(0),
		m_size(byteSize),
		m_layout(nullptr)
	{
		OpenGLCheck(glGenBuffers(1, &m_id));
		OpenGLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_id));
		OpenGLCheck(glBufferData(GL_ARRAY_BUFFER, m_size, data, GL_STATIC_DRAW));
		OpenGLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	OpenGLVertexBufferObject::OpenGLVertexBufferObject(uint32 byteSize) :
		m_id(0),
		m_size(byteSize),
		m_layout(nullptr)
	{
		OpenGLCheck(glGenBuffers(1, &m_id));
		OpenGLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_id));
		OpenGLCheck(glBufferData(GL_ARRAY_BUFFER, m_size, nullptr, GL_STATIC_DRAW));
		OpenGLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	OpenGLVertexBufferObject::~OpenGLVertexBufferObject()
	{
		OpenGLCheck(glDeleteBuffers(1, &m_id));
	}

	void OpenGLVertexBufferObject::Bind() 
	{
		OpenGLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	}

	void OpenGLVertexBufferObject::Unbind() 
	{
		OpenGLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	}

	void OpenGLVertexBufferObject::SetData(const void* data, uint32 byteSize)
	{
		OpenGLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_id));

		if (byteSize > m_size)
		{
			m_size = byteSize;
			OpenGLCheck(glBufferData(GL_ARRAY_BUFFER, m_size, data, GL_STATIC_DRAW));
			return;
		}

		OpenGLCheck(glBufferSubData(GL_ARRAY_BUFFER, 0, m_size, data));

	}
}