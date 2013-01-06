/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayEventCheckpoint_h__
#define ReplayEventCheckpoint_h__

#include "ReplayEventUnknown.h"

class ReplayEventCheckpoint : public ReplayEventUnknown
{
public:
	typedef boost::shared_ptr<ReplayEventCheckpoint> Shared;

	ReplayEventCheckpoint(ReplayEventFrame::Shared replayEventFrame)
		: ReplayEventUnknown(replayEventFrame) {}

	float GetLapTime() const { return BinaryStreamUtil::GetBits<float>(0, eventFrame->GetEventData()); }
	void SetLapTime(float value) { BinaryStreamUtil::SetBits(value, 0, eventFrame->GetEventData()); }

	float GetCheckpointTime() const { return BinaryStreamUtil::GetBits<float>(4, eventFrame->GetEventData()); }
	void SetCheckpointTime(float value) { BinaryStreamUtil::SetBits(value, 4, eventFrame->GetEventData()); }

	u_char GetLap() const { return BinaryStreamUtil::GetBits<char>(8, eventFrame->GetEventData()); }
	void SetLap(char value) { BinaryStreamUtil::SetBits(value, 8, eventFrame->GetEventData()); }

	u_char GetSector() const 
	{ 
		char sector = BinaryStreamUtil::GetBits<char>(9, eventFrame->GetEventData()); 
		return (sector == 0) ? 0 : (sector == 64) ? 1 : 2; 
	}
	void SetSector(char value) 
	{ 
		char sector = (value == 0) ? 0 : (value == 1) ? 64 : 128;
		BinaryStreamUtil::SetBits(sector, 9, eventFrame->GetEventData()); 
	}
};
#endif // ReplayEventCheckpoint_h__
