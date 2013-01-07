/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef replay_h__
#define replay_h__

#include "ReplayEventGroup.h"
#include "ReplayDriver.h"
#include "ReplayCameraGroup.h"

using namespace std;

class Replay
{
public:
	typedef boost::shared_ptr<Replay> Shared;

	string header_string;
	float version;

	string rfm_file;
	string unknown_str;
	string scn_file;
	string aiw_file;
	
	u_char unknown_byte_1;
	SessionTypes session;
	u_short race_time;

	
	ReplayDriver::t_DriverContainer driver;

	float replay_playback_position;
	int unknown_integer_1;
	int camera_flag;
	ReplayCameraGroup::Shared cameraGroup;

	int event_group_count;
	int event_count;

	float unknown_float_1;
	float replay_time_start_et; // et = gametime (elapsed time)
	float replay_time_end_et; 
	float replay_duration;

	typedef vector<ReplayEventGroup::Shared> t_EventGroupContainer;
	t_EventGroupContainer eventGroups;
	

	static Replay::Shared ReadFromStream(istream& stream)
	{
		Replay::Shared result(new Replay());

		/*
			This header looks like a C-style comment.
			I think they have a "dirty" macro or something to identify the file with a string compare. (o:
			The problem is, they don't need to store the length, because they know what they expect, so it could be a change in this size 
			for future releases, which will break a compatibility
		*/
		result->header_string = BinaryStreamUtil::ReadString(stream, 49); 
		result->version = BinaryStreamUtil::ReadBinary<float>(stream);

		result->rfm_file = BinaryStreamUtil::ReadStringWithSizeInt(stream);
		result->unknown_str = BinaryStreamUtil::ReadStringWithSizeInt(stream); // Unknown (seems to be the length of an unknown string, which is always 0 in my test cases)
		result->scn_file = BinaryStreamUtil::ReadStringWithSizeInt(stream);
		result->aiw_file =BinaryStreamUtil:: ReadStringWithSizeInt(stream);

		result->unknown_byte_1 = BinaryStreamUtil::ReadBinary<u_char>(stream);
		result->session = (SessionTypes)BinaryStreamUtil::ReadBinary<u_char>(stream);
		result->race_time = BinaryStreamUtil::ReadBinary<u_short>(stream);

		int driverSize = BinaryStreamUtil::ReadBinary<int>(stream);
		for(int i = 0; i < driverSize; ++i)
		{
			result->driver.push_back(ReplayDriver::ReadFromStream(stream));
			//printf_s("Driver: %s [%d] \n", driver.name.c_str(), driver.slotId);
		}

		result->replay_playback_position = BinaryStreamUtil::ReadBinary<float>(stream);
		result->unknown_integer_1 = BinaryStreamUtil::ReadBinary<int>(stream);
		result->camera_flag = BinaryStreamUtil::ReadBinary<int>(stream);

		if (result->camera_flag != 0)
		{
			result->cameraGroup = ReplayCameraGroup::ReadFromStream(stream);
		}

		result->event_group_count = BinaryStreamUtil::ReadBinary<int>(stream);
		result->event_count = BinaryStreamUtil::ReadBinary<int>(stream);
		
		result->unknown_float_1 = BinaryStreamUtil::ReadBinary<float>(stream);
		result->replay_time_start_et = BinaryStreamUtil::ReadBinary<float>(stream);
		result->replay_time_end_et = BinaryStreamUtil::ReadBinary<float>(stream); 
		result->replay_duration = BinaryStreamUtil::ReadBinary<float>(stream);

		while(stream.good() && stream.eof() == false)
		{
			result->eventGroups.push_back(ReplayEventGroup::ReadFromStream(stream));
		}

		result->eventGroups.erase(result->eventGroups.end() - 1);
		return result;
	}

	void WriteToStream(std::ostream& stream) const
	{
		BinaryStreamUtil::WriteString(header_string, stream);
		BinaryStreamUtil::WriteBinary<float>(version, stream);

		BinaryStreamUtil::WriteStringWithSizeInt(rfm_file, stream);
		BinaryStreamUtil::WriteStringWithSizeInt(unknown_str, stream);
		BinaryStreamUtil::WriteStringWithSizeInt(scn_file, stream);
		BinaryStreamUtil::WriteStringWithSizeInt(aiw_file, stream);

		BinaryStreamUtil::WriteBinary<char>(unknown_byte_1, stream);
		BinaryStreamUtil::WriteBinary<char>(session, stream);
		BinaryStreamUtil::WriteBinary<u_short>(race_time, stream);

		BinaryStreamUtil::WriteBinary<int>(driver.size(), stream);

		for(u_int i = 0; i < driver.size(); ++i) driver[i]->WriteToStream(stream);

		BinaryStreamUtil::WriteBinary<float>(replay_playback_position, stream);
		BinaryStreamUtil::WriteBinary<int>(unknown_integer_1 ,stream);
		BinaryStreamUtil::WriteBinary<int>(camera_flag ,stream);

		if (camera_flag != 0) cameraGroup->WriteToStream(stream);

		BinaryStreamUtil::WriteBinary<int>(eventGroups.size(), stream);
		BinaryStreamUtil::WriteBinary<int>(GetEventCount() ,stream);

		BinaryStreamUtil::WriteBinary<float>(unknown_float_1, stream);
		BinaryStreamUtil::WriteBinary<float>(replay_time_start_et ,stream);
		BinaryStreamUtil::WriteBinary<float>(replay_time_end_et ,stream); 
		BinaryStreamUtil::WriteBinary<float>(replay_duration ,stream);

		for(u_int i = 0; i < eventGroups.size(); ++i) eventGroups[i]->WriteToStream(stream);

		stream.flush();
	}

	u_int GetEventCount() const 
	{
		u_int result = 0;
		t_EventGroupContainer::const_iterator it = eventGroups.begin();
		t_EventGroupContainer::const_iterator itEnd = eventGroups.end();
		for(; it != itEnd; ++it) result += it->get()->GetTotalEventCount();
		return result;
	}

	void PrintInfo() const 
	{
		std::cout << "Parsing Results" << std::endl;
		int unkown_events = 0;
		int checkpoint_events = 0;
		int scoreboard_events = 0;
		int ziploc_events = 0;
		int vfx_events = 0;
		int sfx_events = 0;
		for(u_int i = 0; i < eventGroups.size(); ++i)
		{
			unkown_events += eventGroups[i]->events.unkown_events.size();
			checkpoint_events += eventGroups[i]->events.checkpoint_events.size();
			scoreboard_events += eventGroups[i]->events.scoreboard_events.size();
			ziploc_events += eventGroups[i]->events.ziploc_events.size();
			vfx_events += eventGroups[i]->events.vfx_events.size();
			sfx_events += eventGroups[i]->events.sfx_events.size();
		}
		std::cout << "unknown_events: " << unkown_events << std::endl;
		std::cout << "checkpoint_events: " << checkpoint_events << std::endl;
		std::cout << "scoreboard_events: " << scoreboard_events << std::endl;
		std::cout << "ziploc_events: " << ziploc_events << std::endl;
		std::cout << "vfx_events: " << vfx_events << std::endl;
		std::cout << "sfx_events: " << sfx_events << std::endl;
		std::cout << "total event groups: " << eventGroups.size() << std::endl;
		std::cout << "total events: " << GetEventCount() << std::endl;

		/*for(u_int i = 0; i < eventGroups.size(); ++i)
		{
			for(u_int j = 0; j < eventGroups[i]->unkown_events.size(); ++j)
			{
				ReplayEventUnknown::Shared unknown = eventGroups[i]->unkown_events[j];
				std::cout << "Unknown Event [Class: " << unknown->GetEventFrame()->GetClass() << " Type: " << unknown->GetEventFrame()->GetType() << " Owner: " << unknown->GetEventFrame()->GetOwner() << "]" << std::endl;
			}
		}*/
		
	}
protected:

};
#endif // replay_h__
