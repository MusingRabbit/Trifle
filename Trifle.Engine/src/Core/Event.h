#ifndef EVENT_H
#define EVENT_H

#include "Types.h"
#include <any>
#include <unordered_map>

class Event
{
private:
	EventId m_type;
	std::unordered_map<EventId, std::any> m_data;

public:
	Event() = delete;

	explicit Event(EventId type)
		: m_type(type)
	{
		
	}

	template<typename T>
	void SetParam(EventId id, T value)
	{
		m_data[id] = value;
	}

	template<typename T>
	T GetParam(EventId id)
	{
		return std::any_cast<T>(m_data[id]);
	}

	EventId GetType() const
	{
		return m_type;
	}


};


#endif // DEBUG