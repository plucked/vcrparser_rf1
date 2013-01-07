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
	t_unknown_events_container unkown_events;

	typedef vector<ReplayEventCheckpoint::Shared> t_checkpoint_events_container;
	t_checkpoint_events_container checkpoint_events;

	typedef vector<ReplayEventScoreboard::Shared> t_scoreboard_events_container;
	t_scoreboard_events_container scoreboard_events;

	typedef vector<ReplayEventZipLoc::Shared> t_ziploc_events_container;
	t_ziploc_events_container ziploc_events;

	typedef vector<ReplayEventVFX::Shared> t_vfx_events_container;
	t_vfx_events_container vfx_events;

	typedef vector<ReplayEventSFX::Shared> t_sfx_events_container;
	t_sfx_events_container sfx_events;

	void RemoveEventsFromDriver( u_char slotId )
	{
		RemoveFromContainer<t_unknown_events_container>(slotId, unkown_events);
		RemoveFromContainer<t_checkpoint_events_container>(slotId, checkpoint_events);
		RemoveFromContainer<t_scoreboard_events_container>(slotId, scoreboard_events);
		RemoveFromContainer<t_ziploc_events_container>(slotId, ziploc_events);
		RemoveFromContainer<t_vfx_events_container>(slotId, vfx_events);
		RemoveFromContainer<t_sfx_events_container>(slotId, sfx_events);
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
				if (event_frame->GetClass() == ECLASS_MAXIMUM)
				{
					int i = 0;
				}
				ReplayEventUnknown::Shared unknown_event( new ReplayEventUnknown(event_frame));
				result->unkown_events.push_back(unknown_event);
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
				result->ziploc_events.push_back(ziploc_event);
				break;
			}	
		default:
			ReplayEventUnknown::Shared unknown_event( new ReplayEventUnknown(event_frame));
			result->unkown_events.push_back(unknown_event);
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
				result->checkpoint_events.push_back(checkpoint_event);
				break;
			}
		case EventTypes::ETYPE_SCOREBOARD:
			{
				ReplayEventScoreboard::Shared scoreboard_event( new ReplayEventScoreboard(event_frame));
				result->scoreboard_events.push_back(scoreboard_event);
				break;
			}	
		default:
			ReplayEventUnknown::Shared unknown_event( new ReplayEventUnknown(event_frame));
			result->unkown_events.push_back(unknown_event);
			break;
		}
	}

	static void AddVFXEvent( ReplayEventFrame::Shared event_frame, ReplayEventGroup::Shared result ) 
	{
		ReplayEventVFX::Shared vfx_event( new ReplayEventVFX(event_frame));
		result->vfx_events.push_back(vfx_event);
	}

	static void AddSFXEvent( ReplayEventFrame::Shared event_frame, ReplayEventGroup::Shared result ) 
	{
		ReplayEventSFX::Shared sfx_event( new ReplayEventSFX(event_frame));
		result->sfx_events.push_back(sfx_event);
	}

	void WriteToStream(std::ostream& stream) const
	{
		short count = GetTotalEventCount();

		BinaryStreamUtil::WriteBinary<float>(time, stream);
		BinaryStreamUtil::WriteBinary<short>(GetTotalEventCount(), stream);

		for(u_int i = 0; i < unkown_events.size(); ++i) unkown_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < checkpoint_events.size(); ++i) checkpoint_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < scoreboard_events.size(); ++i) scoreboard_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < ziploc_events.size(); ++i) ziploc_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < vfx_events.size(); ++i) vfx_events[i]->GetEventFrame()->WriteToStream(stream);
		for(u_int i = 0; i < sfx_events.size(); ++i) sfx_events[i]->GetEventFrame()->WriteToStream(stream);
	}

	u_int GetTotalEventCount() const
	{
		return unkown_events.size() + 
				checkpoint_events.size() + 
				scoreboard_events.size() + 
				ziploc_events.size() + 
				vfx_events.size() + 
				sfx_events.size();
	}
};

#endif // ReplayEventGroup_h__
