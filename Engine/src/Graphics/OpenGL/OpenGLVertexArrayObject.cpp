#include "Graphics/OpenGL/OpenGLVertexArrayObject.h"

namespace Bambo
{
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Matrix3f:     return GL_FLOAT;
		case ShaderDataType::Matrix4f:     return GL_FLOAT;
		case ShaderDataType::Integer:      return GL_INT;
		case ShaderDataType::Integer2:     return GL_INT;
		case ShaderDataType::Integer3:     return GL_INT;
		case ShaderDataType::Integer4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		BAMBO_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArrayObject::OpenGLVertexArrayObject() :
		VertexArrayObject(),
		m_id(0),
		m_vbos(),
		m_layoutIndex(0)
	{
		OpenGLCheck(glGenVertexArrays(1, &m_id));
	}

	OpenGLVertexArrayObject::~OpenGLVertexArrayObject()
	{
		OpenGLCheck(glDeleteVertexArrays(1, &m_id));
	}

	void OpenGLVertexArrayObject::Bind()
	{
		OpenGLCheck(glBindVertexArray(m_id));
	}

	void OpenGLVertexArrayObject::Unbind() 
	{
		OpenGLCheck(glBindVertexArray(0));
	}

	void OpenGLVertexArrayObject::AddVertexBufferObject(SPtr<VertexBufferObject> vbo)
	{
		SPtr<BufferLayout> layout = vbo->GetLayout();
		Bind();
		vbo->Bind();

		for (CLayoutIter it = layout->Begin(); it != layout->End(); ++it)
		{
			switch (it->GetType())
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Integer:
			case ShaderDataType::Integer2:
			case ShaderDataType::Integer3:
			case ShaderDataType::Integer4:
			case ShaderDataType::Bool:
			{
				OpenGLCheck(glEnableVertexAttribArray(m_layoutIndex));
				OpenGLCheck(glVertexAttribPointer(m_layoutIndex,
					GetComponentCount(it->GetType()),
					ShaderDataTypeToOpenGLType(it->GetType()),
					GL_FALSE,
					layout->GetStride(),
					(const void*)it->GetOffset()));
				++m_layoutIndex;
				break;
			}
			case ShaderDataType::Matrix3f:
			case ShaderDataType::Matrix4f:
			{
				uint32 count = GetComponentCount(it->GetType());
				for (uint32 i = 0; i < count; ++i)
				{
					OpenGLCheck(glEnableVertexAttribArray(m_layoutIndex));
					OpenGLCheck(glVertexAttribPointer(m_layoutIndex, 
						count,
						ShaderDataTypeToOpenGLType(it->GetType()),
						GL_FALSE,
						layout->GetStride(),
						(const void*)(it->GetOffset() + sizeof(float) * count * i)));
					OpenGLCheck(glVertexAttribDivisor(m_layoutIndex, 1));
					++m_layoutIndex;
				}
				break;
			}
			default:
				BAMBO_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		vbo->Unbind();
		Unbind();
		m_vbos.push_back(vbo);
	}
}