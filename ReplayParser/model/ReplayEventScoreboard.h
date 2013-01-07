/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayEventScoreboard_h__
#define ReplayEventScoreboard_h__

#include "ReplayEventUnknown.h"

class ReplayEventScoreboard : public ReplayEventUnknown
{
public:
	typedef boost::shared_ptr<ReplayEventScoreboard> Shared;

	ReplayEventScoreboard(ReplayEventFrame::Shared replayEventFrame)
		: ReplayEventUnknown(replayEventFrame)
	{
		std::vector<float> times = GetBestLapSectors();
		std::vector<u_char> places = GetPlaces();
	}

	std::vector<float> GetBestLapSectors() const { return BinaryStreamUtil::GetBits<float>(3, 0, GetEventFrame()->GetEventData()); }
	void SetBestLapSectors(const std::vector<float>& sectors) { BinaryStreamUtil::SetBits<float>(sectors, 0, GetEventFrame()->GetEventData()); }

	std::vector<u_char> GetPlaces() const { return BinaryStreamUtil::GetBits<u_char>(GetEventFrame()->GetSize() - 12, 12, GetEventFrame()->GetEventData()); }
	void SetPlaces(const std::vector<u_char>& places)
	{
		std::vector<u_char> oldplaces = GetPlaces();

		char* insertData = new char[places.size()];
		int offset = 0;
		foreach(const u_char& place, places) insertData[offset++] = place;

		GetEventFrame()->RemoveFromEventData(12, GetEventFrame()->GetSize() - 12);
		GetEventFrame()->InsertToEventData(12, places.size(), insertData);

		delete[] insertData;
	
		std::vector<u_char> newplaces = GetPlaces();
		int i = 0;
	}
protected:
	float best_lap_sectors[3];
};
#endif // ReplayEventScoreboard_h__
