/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayFilterUtil_h__
#define ReplayFilterUtil_h__

#include "../model/Replay.h"

class ReplayFilterUtil
{
public:
	ReplayFilterUtil(Replay::Shared replay);

	ReplayDriver::Shared GetDriver(u_char slotId);
	ReplayDriver::Shared GetDriver(const std::string& name);
	void RemoveDriver(u_char slotId);

	Replay::t_EventGroupContainer GetEventGroupsInFrame(float start = 0, float end = FLT_MAX);
	void RemoveEventGroupsInFrame(float start = 0, float end = FLT_MAX);
	void RemoveEventsFromDriver(u_char slotId, ReplayEventGroup::Shared& eventGroup);

	float GetRaceStartTime();
protected:
	void FillDriverList();
	


	Replay::Shared m_Replay;
	typedef std::map<int, ReplayDriver::Shared> t_DriverContainer;
	typedef std::pair<int, ReplayDriver::Shared> t_DriverPair;
	t_DriverContainer m_DriverContainer;
};

#endif // ReplayFilterUtil_h__
