#pragma once
#include "Core.h"

namespace Bambo
{
	class IID
	{
	public:
		IID() :
			m_ID(0)
		{}

		IID(uint64 id) : 
			m_ID(id)
		{}

		IID(const IID& id)
		{
			m_ID = id.m_ID;
		}

		IID& operator=(const IID& id)
		{
			m_ID = id.m_ID;
			return *this;
		}

		static uint64 GetGlobalCounter() { return m_idCounter; }
		static void SetGlobalCounter(uint64 id) { m_idCounter = id; }
		static IID GenerateNew() { return IID(++m_idCounter); }

		bool IsValid() const { return m_ID != 0; }
		operator uint64() const { return m_ID; }
		bool operator==(const IID& id) const
		{
			return m_ID == id.m_ID;
		}

	private:
		uint64 m_ID;
		static uint64 m_idCounter;
	};
}

namespace std 
{
	template<>
	struct hash<Bambo::IID>
	{
		std::size_t operator()(const Bambo::IID& id) const
		{
			return std::hash<std::uint64_t>{}((std::uint64_t)id);
		}
	};

}
