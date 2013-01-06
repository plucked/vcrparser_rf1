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


	ReplayDriver::Shared GetDriver(int slotId);
	float GetRaceStartTime();
protected:
	void FillDriverList();


	Replay::Shared m_Replay;
	typedef std::map<int, ReplayDriver::Shared> t_DriverContainer;
	typedef std::pair<int, ReplayDriver::Shared> t_DriverPair;
	t_DriverContainer m_DriverContainer;
};

#endif // ReplayFilterUtil_h__
