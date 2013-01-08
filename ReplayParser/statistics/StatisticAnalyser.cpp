#include "StatisticAnalyser.h"

StatisticAnalyser::StatisticAnalyser( Replay::Shared replay )
	: m_Replay(replay)
{

}

void StatisticAnalyser::GenerateStatistics()
{
	m_localDriverMap.clear();
	GenerateLocalDriverMap();
	GenerateDriverStatistics();
}


void StatisticAnalyser::GenerateDriverStatistics()
{
	AnalyseEventGroups();
}

DriverStatistic::t_DriverContainer StatisticAnalyser::GetDriverStatistics()
{
	DriverStatistic::t_DriverContainer result;

	// lambda copy map values to vector
	result.reserve(m_localDriverMap.size());
	std::for_each(m_localDriverMap.begin(),m_localDriverMap.end(), [&result](const DriverStatistic::t_SlotDriverMap::value_type& p) 
	{ result.push_back(p.second); });

	return result;
}

void StatisticAnalyser::GenerateLocalDriverMap()
{
	foreach(ReplayDriver::Shared& driver, m_Replay->driver)
	{
		DriverStatistic::Shared driverStat(new DriverStatistic());
		driverStat->slotId = driver->slotId;
		driverStat->name = driver->name;
		m_localDriverMap.insert(DriverStatistic::t_SlotDriverPair(driverStat->slotId, driverStat));
	}
}

DriverStatistic::Shared StatisticAnalyser::GetDriverStatistic( u_char slotId )
{
	DriverStatistic::t_SlotDriverMap::iterator findIt = m_localDriverMap.find(slotId);
	if (findIt != m_localDriverMap.end()) return findIt->second;
	return DriverStatistic::Shared();
}

void StatisticAnalyser::AnalyseEventGroups()
{
	foreach(ReplayEventGroup::Shared& group, m_Replay->eventGroups)
		AnalyseEventGroup(group);
}

void StatisticAnalyser::AnalyseEventGroup( const ReplayEventGroup::Shared& group )
{
	foreach(ReplayEventCheckpoint::Shared& event , group->events.checkpoint_events) AnalyseCheckpointEvent(event);
	foreach(ReplayEventScoreboard::Shared& event , group->events.scoreboard_events) AnalyseScoreboardEvent(event);
	foreach(ReplayEventZipLoc::Shared& event, group->events.ziploc_events) AnalyseZipLocEvent(event);
	foreach(ReplayEventUnknown::Shared& event, group->events.unkown_events) AnalyseUnknownEvent(event);
}

void StatisticAnalyser::AnalyseCheckpointEvent( const ReplayEventCheckpoint::Shared& event )
{
	u_char lapNr = event->GetLap();
	u_char sectorNr = event->GetSector();
	float sectorTime = event->GetLapTime();
	if (sectorTime == -1) return;

	DriverStatistic::Shared driver = GetDriverStatistic(event->GetEventFrame()->GetOwner());
	if (driver)
	{
		DriverStatisticStint::Shared stint = driver->GetLastStint();
		if (!stint->HasLap(lapNr)) stint->AddLap(lapNr); // add this lap if not already done
		Lap::Shared lap = stint->GetLap(lapNr);
		lap->sectorTotalTimes[sectorNr] = sectorTime;
		lap->UpdateSectorTimes();

		if (sectorNr == 0) stint->AddLap(lapNr + 1);
	}
}

void StatisticAnalyser::AnalyseScoreboardEvent( const ReplayEventScoreboard::Shared& event )
{

}

void StatisticAnalyser::AnalyseZipLocEvent( const ReplayEventZipLoc::Shared& event )
{
	DriverStatistic::Shared driver = GetDriverStatistic(event->GetEventFrame()->GetOwner());
	if (driver)
	{
		DriverStatisticStint::Shared stint = driver->GetLastStint();
		stint->GetCurrentLapNr();
	}
}

void StatisticAnalyser::AnalyseUnknownEvent( const ReplayEventUnknown::Shared& event )
{
	if (event->GetEventFrame()->GetClass() == ECLASS_SYS && event->GetEventFrame()->GetType() == EventTypes::ETYPE_DNF)
	{

	}
}
