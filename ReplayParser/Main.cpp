/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#include "model/replay_parser.h"
#include "model/Replay.h"
#include "controller/ReplayFilterUtil.h"

int main(int argC, char* argV)
{
	Replay::Shared replay = ReplayParser::LoadFromFile("C:\\Games\\rFactor_2012\\ReplayFridge\\Replays\\Spanien_Rennen.Vcr");

	ReplayFilterUtil filter(replay);

	if (replay->session == SESSION_RACE)
		std::cout << "race start at " << filter.GetRaceStartTime() << std::endl;

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

	ReplayParser::SaveToFile(*replay.get(), "C:\\Games\\rFactor_2012\\ReplayFridge\\Replays\\merge_saved.vcr");
	std::cout << replay->eventGroups.size() << std::endl;
	return 0;
}