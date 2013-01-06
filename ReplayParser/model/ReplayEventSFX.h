/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayEventSFX_h__
#define ReplayEventSFX_h__

#include "ReplayEventUnknown.h"

class ReplayEventSFX : public ReplayEventUnknown
{
public:
	typedef boost::shared_ptr<ReplayEventSFX> Shared;

	ReplayEventSFX(ReplayEventFrame::Shared replayEventFrame)
		: ReplayEventUnknown(replayEventFrame)
	{

	}
};
#endif // ReplayEventSFX_h__
