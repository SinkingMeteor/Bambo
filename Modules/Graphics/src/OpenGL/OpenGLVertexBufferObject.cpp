#include "OpenGL/OpenGLVertexBufferObject.h"

namespace Bambo
{
	OpenGLVertexBufferObject::OpenGLVertexBufferObject(const void* data, uint32 size) :
		m_id(0),
		m_size(size),
		m_layout(nullptr)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, m_size, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexBufferObject::OpenGLVertexBufferObject(uint32 size) :
		m_id(0),
		m_size(size),
		m_layout(nullptr)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, m_size, nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexBufferObject::~OpenGLVertexBufferObject()
	{
		glDeleteBuffers(1, &m_id);
	}

	void OpenGLVertexBufferObject::Bind() 
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void OpenGLVertexBufferObject::Unbind() 
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void OpenGLVertexBufferObject::SetData(const void* data, uint32 size) 
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_size, data);

	}
}