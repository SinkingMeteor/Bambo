#pragma once
#include "pch.h"

namespace Bambo
{
	using EventDescriptor = std::size_t;

#define BAMBO_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define BAMBO_EVENT_META_INFO(text) public:\
		static const EventDescriptor Descriptor = static_cast<std::size_t>(text);\
		virtual EventDescriptor GetDescriptor() const override { return Descriptor; }\

	class BAMBO_API Event
	{
	public:
		bool Handled{ false };

		virtual ~Event() = default;
		virtual EventDescriptor GetDescriptor() const = 0;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_event(event)
		{}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_event.GetDescriptor() == T::Descriptor)
			{
				m_event.Handled |= func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};

}