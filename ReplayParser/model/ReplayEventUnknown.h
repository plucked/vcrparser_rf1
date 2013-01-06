/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayEventUnknown_h__
#define ReplayEventUnknown_h__

#include "ReplayEventFrame.h"

class ReplayEventUnknown
{
public:
	typedef boost::shared_ptr<ReplayEventUnknown> Shared;

	ReplayEventUnknown(ReplayEventFrame::Shared replayEventFrame)
		: eventFrame(replayEventFrame)
	{

	}

	const ReplayEventFrame::Shared& GetEventFrame() const { return eventFrame; }
protected:
	ReplayEventFrame::Shared eventFrame;
};
#endif // ReplayEventUnknown_h__
