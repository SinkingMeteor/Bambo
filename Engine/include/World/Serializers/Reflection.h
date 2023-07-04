#pragma once
#include "Essentials.h"

namespace Bambo
{
	enum class ReflectionPrivitiveType
	{
		Int32,
		String,
		Float
	};

	class ReflectionVariable
	{
	public:
		ReflectionVariable(const char* name, ReflectionPrivitiveType primitiveType, uint32 offset) :
			m_name(name),
			m_primitiveType(primitiveType),
			m_offset(offset)
		{}
		
		const std::string& GetName() const { return m_name; }
		ReflectionPrivitiveType GetPrimitiveType() const { return m_primitiveType; }
		uint32 GetOffset() const { return m_offset; }

	private:
		std::string m_name;
		ReflectionPrivitiveType m_primitiveType;
		uint32 m_offset;
	};

	class ReflectionData
	{
	public:
		ReflectionData(std::initializer_list<const MemberVariable& > variables) :
			m_variables(variables)
		{}

		const std::vector<ReflectionVariable> GetVariables() const { return m_variables; }
	private:
		std::vector<ReflectionVariable> m_variables;
	};
}