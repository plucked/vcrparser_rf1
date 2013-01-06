/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#include "model/replay_parser.h"
#include "model/Replay.h"

int main(int argC, char* argV)
{
	Replay::Shared replay = ReplayParser::LoadFromFile("C:\\Games\\rFactor_2012\\ReplayFridge\\Replays\\Spanien_Rennen.Vcr");

	// try to detect the start of a race 
	float countdownAt = -1.0f;
	float greenAt = -1.0f;

	for(int i = 0; i < replay->eventGroups.size(); ++i)
		for(int j = 0; j < replay->eventGroups[i]->unkown_events.size(); ++j)
		{
			ReplayEventUnknown::Shared unknownEvent = replay->eventGroups[i]->unkown_events[j];
			if (unknownEvent->GetEventFrame()->GetClass() == ECLASS_SYS && unknownEvent->GetEventFrame()->GetType() == EventTypes::ETYPE_COUNTDOWN)
			{
				countdownAt = replay->eventGroups[i]->time;
			}
			
			if (unknownEvent->GetEventFrame()->GetClass() == ECLASS_SYS && unknownEvent->GetEventFrame()->GetType() == EventTypes::ETYPE_NEWSTATIONS &&
				countdownAt != -1.0f && greenAt == -1.0f)
			{
				int driver = unknownEvent->GetEventFrame()->GetOwner();
				greenAt = replay->eventGroups[i]->time;
			}
		}

	std::cout << "count at: " << countdownAt << " green at: " << greenAt << std::endl;

	ReplayParser::SaveToFile(*replay.get(), "C:\\Games\\rFactor_2012\\ReplayFridge\\Replays\\merge_saved.vcr");
	std::cout << replay->eventGroups.size() << std::endl;
	return 0;
}