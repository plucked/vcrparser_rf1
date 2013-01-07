/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayEventGroup_h__
#define ReplayEventGroup_h__

#include "ReplayEventFrame.h"
#include "ReplayEventUnknown.h"
#include "ReplayEventCheckpoint.h"
#include "ReplayEventScoreboard.h"
#include "ReplayEventZipLoc.h"
#include "ReplayEventVFX.h"
#include "ReplayEventSFX.h"

using namespace std;

class ReplayEventGroup
{
public:
	typedef boost::shared_ptr<ReplayEventGroup> Shared;

	float time;

	typedef vector<ReplayEventUnknown::Shared> t_unknown_events_container;
	typedef vector<ReplayEventCheckpoint::Shared> t_checkpoint_events_container;
	typedef vector<ReplayEventScoreboard::Shared> t_scoreboard_events_container;
	typedef vector<ReplayEventZipLoc::Shared> t_ziploc_events_container;
	typedef vector<ReplayEventVFX::Shared> t_vfx_events_container;
	typedef vector<ReplayEventSFX::Shared> t_sfx_events_container;

	struct Events
	{
		t_unknown_events_container unkown_events;
		t_checkpoint_events_container checkpoint_events;
		t_scoreboard_events_container scoreboard_events;
		t_ziploc_events_container ziploc_events;
		t_vfx_events_container vfx_events;
		t_sfx_events_container sfx_events;
	} events;
	
	Events GetEventsFromDriver( u_char slotId )
	{
		Events result;
		foreach(ReplayEventUnknown::Shared& event, events.unkown_events) if (event->GetEventFrame()->GetOwner() == slotId) result.unkown_events.push_back(event);
		foreach(ReplayEventCheckpoint::Shared& event, events.checkpoint_events) if (event->GetEventFrame()->GetOwner() == slotId) result.checkpoint_events.push_back(event);
		foreach(ReplayEventScoreboard::Shared& event, events.scoreboard_events) if (event->GetEventFrame()->GetOwner() == slotId) result.scoreboard_events.push_back(event);
		foreach(ReplayEventZipLoc::Shared& event, events.ziploc_events) if (event->GetEventFrame()->GetOwner() == slotId) result.ziploc_events.push_back(event);
		foreach(ReplayEventVFX::Shared& event, events.vfx_events) if (event->GetEventFrame()->GetOwner() == slotId) result.vfx_events.push_back(event);
		foreach(ReplayEventSFX::Shared& event, events.sfx_events) if (event->GetEventFrame()->GetOwner() == slotId) result.sfx_events.push_back(event);
		return result;
	}

	void RemoveEventsFromDriver( u_char slotId )
	{
		RemoveFromContainer<t_unknown_events_container>(slotId, events.unkown_events);
		RemoveFromContainer<t_checkpoint_events_container>(slotId, events.checkpoint_events);
		RemoveFromContainer<t_scoreboard_events_container>(slotId, events.scoreboard_events);
		RemoveFromContainer<t_ziploc_events_container>(slotId, events.ziploc_events);
		RemoveFromContainer<t_vfx_events_container>(slotId, events.vfx_events);
		RemoveFromContainer<t_sfx_events_container>(slotId, events.sfx_events);

		t_scoreboard_events_container::iterator scoreIt = events.scoreboard_events.begin();
		t_scoreboard_events_container::const_iterator scoreItEnd = events.scoreboard_events.end();
		for(; scoreIt != scoreItEnd; ++scoreIt)
		{
			ReplayEventScoreboard::Shared score = *scoreIt;
			std::vector<u_char> places = score->GetPlaces();
			std::vector<u_char>::iterator it = places.begin();
			std::vector<u_char>::const_iterator itEnd = places.end();
			for(; it != itEnd; ++it)
			{
				if (*it == slotId)
				{
					places.erase(it);
					break;
				}
			}
			score->SetPlaces(places);
		}
	}

	template<typename T> 
	void RemoveFromContainer(u_char slotId, T& container)
	{
		T::iterator it = container.begin();
		T::const_iterator itEnd = container.end();
		for(; it != itEnd; ) 
		{
			if ((*it)->GetEventFrame()->GetOwner() == slotId)
			{
				it = container.erase(it);
				itEnd = container.end();
			}
			else ++it;
		}
	}



	static ReplayEventGroup::Shared ReadFromStream(istream& stream) 
	{
		ReplayEventGroup::Shared result(new ReplayEventGroup);
		result->time = BinaryStreamUtil::ReadBinary<float>(stream);
		short event_group_count = BinaryStreamUtil::ReadBinary<short>(stream);
		for (short i = 0; i < event_group_count; ++i)
		{
			ReplayEventFrame::Shared event_frame = ReplayEventFrame::ReadFromStream(stream);

			switch (event_frame->GetClass())
			{
			case ECLASS_SFX:
				{
					AddSFXEvent(event_frame, result);
					break;
				}
			case ECLASS_VFX:
				{
					AddVFXEvent(event_frame, result);
					break;
				}
			case ECLASS_SYS:
				{
					AddSYSEvent(event_frame, result);
					break;
				}
			case ECLASS_LOC:
				{
					AddLOCEvent(event_frame, result);
					break;
				}
			default:
				ReplayEventUnknown::Shared unknown_event( new ReplayEventUnknown(event_frame));
				result->events.unkown_events.push_back(unknown_event);
				break;
			}
		}
		return result;
	}

	static void AddLOCEvent( ReplayEventFrame::Shared event_frame, ReplayEventGroup::Shared result ) 
	{
		switch (event_frame->GetType())
		{
		case EventTypes::ETYPE_ZIPLOC_R:
		case EventTypes::ETYPE_ZIPLOC_N:
		case EventTypes::ETYPE_ZIPLOC_1:
		case EventTypes::ETYPE_ZIPLOC_2:
		case EventTypes::ETYPE_ZIPLOC_3:
		case EventTypes::ETYPE_ZIPLOC_4:
		case EventTypes::ETYPE_ZIPLOC_5:
		case EventTypes::ETYPE_ZIPLOC_6:
		case EventTypes::ETYPE_ZIPLOC_7:
			{
				ReplayEventZipLoc::Shared ziploc_event( new ReplayEventZipLoc(event_frame));
				result->events.ziploc_events.push_back(ziploc_event);
				break;
			}	
		default:
			ReplayEventUnknown::Shared unknown_event( new ReplayEventUnknown(event_frame));
			result->events.unkown_events.push_back(unknown_event);
			break;
		}
	}

	static void AddSYSEvent( ReplayEventFrame::Shared event_frame, ReplayEventGroup::Shared result ) 
	{
		switch (event_frame->GetType())
		{
		case EventTypes::ETYPE_CHECKPOINT:
			{
				ReplayEventCheckpoint::Shared checkpoint_event( new ReplayEventCheckpoint(event_frame));
				result->events.checkpoint_events.push_back(checkpoint_event);
				break;
			}
		case EventTypes::ETYPE_SCOREBOARD:
			{
				ReplayEventScoreboard::Shared scoreboard_event( new ReplayEventScoreboard(event_frame));
				result->events.scoreboard_events.push_back(scoreboard_event);
				break;
			}	
		default:
			ReplayEventUnknown::Shared unknown_event( new ReplayEventUnknown(event_frame));
			result->events.unkown_events.push_back(unknown_event);
			break;
		}
	}

	static void AddVFXEvent( ReplayEventFrame::Shared event_frame, ReplayEventGroup::Shared result ) 
	{
		ReplayEventVFX::Shared vfx_event( new ReplayEventVFX(event_frame));
		result->events.vfx_events.push_back(vfx_event);
	}

	static void AddSFXEvent( ReplayEventFrame::Shared event_frame, ReplayEventGroup::Shared result ) 
	{
		ReplayEventSFX::Shared sfx_event( new ReplayEventSFX(event_frame));
		result->events.sfx_events.push_back(sfx_event);
	}

	void WriteToStream(std::ostream& stream) const
	{
		short count = GetTotalEventCount();

		BinaryStreamUtil::WriteBinary<float>(time, stream);
		BinaryStreamUtil::WriteBinary<short>(GetTotalEventCount(), stream);

		for(u_int i = 0; i < events.unkown_events.size(); ++i) events.unkown_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < events.checkpoint_events.size(); ++i) events.checkpoint_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < events.scoreboard_events.size(); ++i) events.scoreboard_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < events.ziploc_events.size(); ++i) events.ziploc_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < events.vfx_events.size(); ++i) events.vfx_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < events.sfx_events.size(); ++i) events.sfx_events[i]->GetEventFrame()->WriteToStream(stream);
	}

	u_int GetTotalEventCount() const
	{
		return events.unkown_events.size() + 
				events.checkpoint_events.size() + 
				events.scoreboard_events.size() + 
				events.ziploc_events.size() + 
				events.vfx_events.size() + 
				events.sfx_events.size();
	}
};

#endif // ReplayEventGroup_h__
