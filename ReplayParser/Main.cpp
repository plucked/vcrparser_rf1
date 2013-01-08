/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#include "model/replay_parser.h"
#include "model/Replay.h"
#include "controller/ReplayFilterUtil.h"
#include "statistics/StatisticAnalyser.h"

int main(int argC, char* argV)
{
	Replay::Shared replay = ReplayParser::LoadFromFile("C:\\Games\\rFactor_2012\\ReplayFridge\\Replays\\F1RL Season 2012 - 03 China Grand Prix S4 2.Vcr");

	StatisticAnalyser statistics(replay);
	statistics.GenerateStatistics();
	DriverStatistic::t_DriverContainer driverStats = statistics.GetDriverStatistics();
	
	foreach(DriverStatistic::Shared& driver, driverStats)
	{
		std::cout << "Laps for " << driver->name << std::endl;
		foreach(DriverStatisticStint::Shared& stint, driver->m_Stints)
		{
			std::cout << "====== STINT ======" << std::endl;

			foreach(Lap::Shared lap, stint->GetLaps())
			{
				std::cout << lap->ToString() << std::endl;
			}

			std::cout << "====== END OF STINT ======" << std::endl;
		}
	}
	int i = 0;
	/*ReplayFilterUtil filter(replay);

	if (replay->session == SESSION_RACE)
		std::cout << "race start at " << filter.GetRaceStartTime() << std::endl;

	foreach(ReplayDriver::Shared& driver, replay->driver)
	{
		std::cout << "distance of "<< driver->name << " is " << filter.GetDriverDistance(driver->slotId) << std::endl;
	}*/

	//std::cout << "distance of Benjamin Koehler: " << filter.GetDriverDistance(filter.GetDriver("Benjamin Koehler")->slotId) << std::endl;
	

	//filter.RemoveDriver(filter.GetDriver("Rainer Heynke")->slotId);

	/*for(int i = 0; i < replay->eventGroups.size(); ++i)
	for(int j = 0; j < replay->eventGroups[i]->scoreboard_events.size(); ++j)
	{
	ReplayEventScoreboard::Shared score = replay->eventGroups[i]->scoreboard_events[j];
	std::vector<u_char> places = score->GetPlaces();
	std::cout << "Places" << std::endl;
	std::vector<u_char>::iterator it = places.begin();
	std::vector<u_char>::const_iterator itEnd = places.end();
	for(; it != itEnd; ++it)
	{
	ReplayDriver::Shared driver = filter.GetDriver(*it);
	if (driver) std::cout << "Driver: " << driver->name << std::endl;
	}
	}*/

	//ReplayParser::SaveToFile(*replay.get(), "C:\\Games\\rFactor_2012\\ReplayFridge\\Replays\\merge_saved.vcr");
	std::cout << replay->eventGroups.size() << std::endl;
	return 0;
}