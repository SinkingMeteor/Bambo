#pragma once
#include "pch.h"

namespace Bambo
{
	enum class BAMBO_API ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Integer,
		Integer2,
		Integer3,
		Integer4,
		Matrix3f,
		Matrix4f,
		Bool
	};

	uint32 GetShaderDataTypeSize(ShaderDataType type);
	uint32 GetComponentCount(ShaderDataType type);
	const char* GetNameOfShaderData(ShaderDataType type);

	class BAMBO_API LayoutElement final
	{
	public:
		LayoutElement() = default;
		LayoutElement(ShaderDataType dataType);
		ShaderDataType GetType() const { return m_dataType; }
		uint32 GetSize() const { return m_size; }
		uint32 GetOffset() const { return m_offset; }
		const char* GetName() const { return GetNameOfShaderData(m_dataType); }
	private:
		ShaderDataType m_dataType;
		uint32 m_size;
		uint32 m_offset;

		const char* GetNameOfShaderData(ShaderDataType type) const;
		friend class BufferLayout;
	};

	using CLayoutIter = std::vector<LayoutElement>::const_iterator;

	class BAMBO_API BufferLayout final
	{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<ShaderDataType> elements);
		CLayoutIter Begin() const { return m_elements.cbegin(); }
		CLayoutIter End() const { return m_elements.cend(); }
		uint32 GetStride() const { return m_stride; }
	private:
		std::vector<LayoutElement> m_elements;
		uint32 m_stride{0};

		void CalculateOffsetsAndStride();
	};
}
