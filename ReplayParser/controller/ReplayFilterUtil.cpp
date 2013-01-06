/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/
#include "ReplayFilterUtil.h"


ReplayFilterUtil::ReplayFilterUtil( Replay::Shared replay ) 
	: m_Replay(replay)
{
	FillDriverList();
}

ReplayDriver::Shared ReplayFilterUtil::GetDriver( int slotId )
{
	t_DriverContainer::iterator findIt = m_DriverContainer.find(slotId);
	if (findIt != m_DriverContainer.end()) return findIt->second;
	return ReplayDriver::Shared();
}

float ReplayFilterUtil::GetRaceStartTime()
{
	// try to detect the start of a race 
	float countdownAt = -1.0f;
	float greenAt = -1.0f;

	Replay::t_EventGroupContainer::iterator it = m_Replay->eventGroups.begin();
	Replay::t_EventGroupContainer::const_iterator itEnd = m_Replay->eventGroups.end();
	for(; it != itEnd; ++it)
	{
		ReplayEventGroup::Shared group = *it;
		
		ReplayEventGroup::t_unknown_events_container::iterator itUnknown = group->unkown_events.begin();
		ReplayEventGroup::t_unknown_events_container::const_iterator itEndUnknown = group->unkown_events.end();
		for(; itUnknown != itEndUnknown; ++itUnknown)
		{
			ReplayEventUnknown::Shared unknownEvent = *itUnknown;
			if (unknownEvent->GetEventFrame()->GetClass() == ECLASS_SYS && unknownEvent->GetEventFrame()->GetType() == EventTypes::ETYPE_COUNTDOWN)
			{
				countdownAt = group->time;
			}

			if (unknownEvent->GetEventFrame()->GetClass() == ECLASS_SYS && unknownEvent->GetEventFrame()->GetType() == EventTypes::ETYPE_NEWSTATIONS &&
				countdownAt != -1.0f && greenAt == -1.0f)
			{
				int driver = unknownEvent->GetEventFrame()->GetOwner();
				greenAt = group->time;
				return greenAt;
			}
		}
	}

	return greenAt;
}

void ReplayFilterUtil::FillDriverList()
{
	ReplayDriver::t_DriverContainer::iterator it = m_Replay->driver.begin();
	ReplayDriver::t_DriverContainer::const_iterator itEnd = m_Replay->driver.end();
	for(; it != itEnd; ++it)
	{
		m_DriverContainer.insert(t_DriverPair(it->get()->slotId, *it));
	}
}