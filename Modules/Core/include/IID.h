#include "pch.h"

namespace Bambo
{
	class BAMBO_API IID
	{
	public:
		IID()
		{
			static uint64 m_idCounter = 0;
			m_ID = ++m_idCounter;
		}

		IID(uint64 id) : 
			m_ID(id)
		{}

		IID(const IID&) = default;

		operator uint64() const { return m_ID; }
	private:
		uint64 m_ID;
	};
}

namespace std 
{
	template <typename T> struct hash;

	template<>
	struct hash<Bambo::IID>
	{
		std::size_t operator()(const Bambo::IID& id) const
		{
			return (uint64)id;
		}
	};

}
