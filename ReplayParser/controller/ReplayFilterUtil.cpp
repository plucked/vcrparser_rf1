/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/
#include "ReplayFilterUtil.h"
#include "../model/Vector3.h"

ReplayFilterUtil::ReplayFilterUtil( Replay::Shared replay ) 
	: m_Replay(replay)
{
	FillDriverList();
}

DriverStatistic::t_DriverContainer ReplayFilterUtil::GetDriverStatistics()
{
	DriverStatistic::t_DriverContainer result;

	return result;
}


ReplayDriver::Shared ReplayFilterUtil::GetDriver( u_char slotId )
{
	t_DriverContainer::iterator findIt = m_DriverContainer.find(slotId);
	if (findIt != m_DriverContainer.end()) return findIt->second;
	return ReplayDriver::Shared();
}

ReplayDriver::Shared ReplayFilterUtil::GetDriver( const std::string& name )
{
	foreach(ReplayDriver::Shared& driver, m_Replay->driver)
	{
		if (driver->name == name) return driver;
	}

	return ReplayDriver::Shared();
}

void ReplayFilterUtil::RemoveDriver( u_char slotId )
{
	// Remove the driver
	ReplayDriver::t_DriverContainer::iterator it = m_Replay->driver.begin();
	ReplayDriver::t_DriverContainer::const_iterator itEnd = m_Replay->driver.end();
	for(; it != itEnd; ++it)
	{
		if ((*it)->slotId == slotId) 
		{
			m_Replay->driver.erase(it);
			break;
		}
	}

	// Remove from the easy access container
	t_DriverContainer::iterator findIt = m_DriverContainer.find(slotId);
	if (findIt != m_DriverContainer.end()) m_DriverContainer.erase(findIt);

	// Remove the events
	foreach(ReplayEventGroup::Shared& group, m_Replay->eventGroups)
	{
		group->RemoveEventsFromDriver(slotId);
	}
}

Replay::t_EventGroupContainer ReplayFilterUtil::GetEventGroupsInFrame( float start /*= 0*/, float end /*= FLT_MAX*/ )
{
	Replay::t_EventGroupContainer result;

	foreach(ReplayEventGroup::Shared& group, m_Replay->eventGroups)
	{
		if (group->time >= start && group->time < end) result.push_back(group);
	}

	return result;
}


void ReplayFilterUtil::RemoveEventGroupsInFrame( float start /*= 0*/, float end /*= FLT_MAX*/ )
{
	Replay::t_EventGroupContainer::iterator it = m_Replay->eventGroups.begin();
	Replay::t_EventGroupContainer::const_iterator itEnd = m_Replay->eventGroups.end();

	for(; it != itEnd; )
	{
		ReplayEventGroup::Shared& group = *it;
		if (group->time >= start && group->time < end)
		{
			it = m_Replay->eventGroups.erase(it);
			itEnd = m_Replay->eventGroups.end();
		}
		else ++it;
	}
}

void ReplayFilterUtil::RemoveEventsFromDriver( u_char slotId, ReplayEventGroup::Shared& eventGroup )
{
	eventGroup->RemoveEventsFromDriver(slotId);
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
		
		ReplayEventGroup::t_unknown_events_container::iterator itUnknown = group->events.unkown_events.begin();
		ReplayEventGroup::t_unknown_events_container::const_iterator itEndUnknown = group->events.unkown_events.end();
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

float ReplayFilterUtil::GetDriverDistance( u_char slotId )
{
	Vector3 last;

	bool first = true;
	float total = 0;

	float lastEventGroupTime;

	Replay::t_EventGroupContainer::iterator it = m_Replay->eventGroups.begin();
	Replay::t_EventGroupContainer::const_iterator itEnd = m_Replay->eventGroups.end();
	for(; it != itEnd; ++it)
	{
		ReplayEventGroup::Shared group = *it;

		ReplayEventGroup::t_ziploc_events_container::iterator itZip = group->events.ziploc_events.begin();
		ReplayEventGroup::t_ziploc_events_container::const_iterator itZipEnd = group->events.ziploc_events.end();
		for(; itZip != itZipEnd; ++itZip)
		{
			ReplayEventZipLoc::Shared zip = *itZip;
			if (zip->GetEventFrame()->GetOwner() == slotId && zip->GetCurrentRPS() > 0)
			{
				Vector3 current = Vector3( zip->GetPosX(), zip->GetPosY(), zip->GetPosZ());
				if (first)
				{
					first = false;
				}
				else
				{
					float timeDiff = group->time - lastEventGroupTime;
					float distance = Vector3::Distance(last, current);

					if (distance < 1000.0) // if the distance is more then 1km, there is a paket loss (disconnect?!)
					{
						// kilometer per hour
						float kmh = 3600.0f / timeDiff * distance / 1000.0f;
						total += distance;
					}
					else first = true;
				}
				last = current;
			}
		}

		lastEventGroupTime = group->time;
	}
	return total;
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

