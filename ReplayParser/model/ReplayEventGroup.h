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

	vector<ReplayEventUnknown::Shared> unkown_events;
	vector<ReplayEventCheckpoint::Shared> checkpoint_events;
	vector<ReplayEventScoreboard::Shared> scoreboard_events;
	vector<ReplayEventZipLoc::Shared> ziploc_events;
	vector<ReplayEventVFX::Shared> vfx_events;
	vector<ReplayEventSFX::Shared> sfx_events;

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
				//printf_s("Unknown event %d:%d\n", event_frame.GetClass(), event_frame.GetType());
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

				//if (event_frame.GetOwner() == 15)
				//printf_s("Driver: %d RPS: %d Gear: %d \n", event_frame.GetOwner(), ziploc_event.GetCurrentRPS(), event_frame.GetType() - EventTypes::ETYPE_ZIPLOC_N);
				break;
			}	
		default:
			//printf_s("Unknown loc event %d:%d\n", event_frame.GetClass(), event_frame.GetType());
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

				//if (checkpoint_event->GetLapTime() > 0.0f)
				//	printf_s("Checkpoint for driver [%d] in sector %d with laptime %f (%d)\n",  checkpoint_event->GetEventFrame()->GetOwner(), checkpoint_event->GetSector(), checkpoint_event->GetLapTime(), checkpoint_event->GetLap());
				break;
			}
		case EventTypes::ETYPE_SCOREBOARD:
			{
				ReplayEventScoreboard::Shared scoreboard_event( new ReplayEventScoreboard(event_frame));
				result->scoreboard_events.push_back(scoreboard_event);

				//if (scoreboard_event.GetBestLapSectors()[0] > 0.0f)
				//	printf_s("Score for driver [%d] %f %f %f\n",  scoreboard_event.GetEventFrame().GetOwner(), scoreboard_event.GetBestLapSectors()[0], scoreboard_event.GetBestLapSectors()[1], scoreboard_event.GetBestLapSectors()[2]);
				break;
			}	
		default:
			//printf_s("Unknown sys event %d:%d\n", event_frame.GetClass(), event_frame.GetType());
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
