#ifndef StatisticAnalyser_h__
#define StatisticAnalyser_h__

#include "../model/Replay.h"
#include "DriverStatistic.h"

class StatisticAnalyser
{
public:
	StatisticAnalyser(Replay::Shared replay);
	void GenerateStatistics();
	void GenerateDriverStatistics();
	DriverStatistic::t_DriverContainer GetDriverStatistics();
protected:
	void GenerateLocalDriverMap();
	DriverStatistic::Shared GetDriverStatistic(u_char slotId);

	void AnalyseEventGroups();
	void AnalyseEventGroup(const ReplayEventGroup::Shared& group);
	void AnalyseCheckpointEvent(const ReplayEventCheckpoint::Shared& event);
	void AnalyseScoreboardEvent(const ReplayEventScoreboard::Shared& event);
	void AnalyseZipLocEvent(const ReplayEventZipLoc::Shared& event);
	void AnalyseUnknownEvent(const ReplayEventUnknown::Shared& event);

	Replay::Shared m_Replay;
	DriverStatistic::t_SlotDriverMap m_localDriverMap;
};
#endif // StatisticAnalyser_h__
