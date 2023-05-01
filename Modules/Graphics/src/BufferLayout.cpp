#include "BufferLayout.h"

namespace Bambo
{
	uint32 GetShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Matrix3f:     return 4 * 3 * 3;
		case ShaderDataType::Matrix4f:     return 4 * 4 * 4;
		case ShaderDataType::Integer:      return 4;
		case ShaderDataType::Integer2:     return 4 * 2;
		case ShaderDataType::Integer3:     return 4 * 3;
		case ShaderDataType::Integer4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		BAMBO_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	uint32 GetComponentCount(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Matrix3f:    return 3;
		case ShaderDataType::Matrix4f:    return 4;
		case ShaderDataType::Integer:     return 1;
		case ShaderDataType::Integer2:    return 2;
		case ShaderDataType::Integer3:    return 3;
		case ShaderDataType::Integer4:    return 4;
		case ShaderDataType::Bool:    return 1;
		}

		BAMBO_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	const char* GetNameOfShaderData(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None: return "None";
		case ShaderDataType::Float:   return "Float";
		case ShaderDataType::Float2:  return "Float2";
		case ShaderDataType::Float3:  return "Float3";
		case ShaderDataType::Float4:  return "Float4";
		case ShaderDataType::Matrix3f:    return "Matrix3f";
		case ShaderDataType::Matrix4f:    return "Matrix4f";
		case ShaderDataType::Integer:     return "Integer";
		case ShaderDataType::Integer2:    return "Integer2";
		case ShaderDataType::Integer3:    return "Integer3";
		case ShaderDataType::Integer4:    return "Integer4";
		case ShaderDataType::Bool:    return "Boolean";
		}

		BAMBO_ASSERT(false, "Unknown ShaderDataType!");
		return "Unknown";
	}

	LayoutElement::LayoutElement(ShaderDataType dataType) :
		m_dataType(dataType),
		m_size(GetShaderDataTypeSize(dataType)),
		m_offset(0)
	{}


	BufferLayout::BufferLayout(std::initializer_list<ShaderDataType> elements)
	: m_elements()
	{
		m_elements.reserve(elements.size());
		for (ShaderDataType type : elements)
		{
			m_elements.push_back(type);
		}
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32 offset = 0;
		m_stride = 0;
		for (LayoutElement& element : m_elements)
		{
			element.m_offset = offset;
			offset += element.m_size;
			m_stride += element.m_size;
		}
	}

}