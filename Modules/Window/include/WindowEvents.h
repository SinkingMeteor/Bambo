#pragma once
#include "pch.h"
#include "EngineEvent.h"

namespace Bambo
{
	class BAMBO_API WindowResizedEvent : public Event
	{
		BAMBO_EVENT_META_INFO('WRSZ');

	public:
		WindowResizedEvent(uint32 width, uint32 height) :
			m_width(width),
			m_height(height)
		{}

		uint32 GetWidth() const { return m_width; }
		uint32 GetHeight() const { return m_height; }
	private:
		uint32 m_width;
		uint32 m_height;
	};
}