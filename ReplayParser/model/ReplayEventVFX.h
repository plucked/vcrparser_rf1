/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayEventVFX_h__
#define ReplayEventVFX_h__

#include "ReplayEventUnknown.h"

class ReplayEventVFX : public ReplayEventUnknown
{
public:
	typedef boost::shared_ptr<ReplayEventVFX> Shared;

	ReplayEventVFX(ReplayEventFrame::Shared replayEventFrame)
		: ReplayEventUnknown(replayEventFrame)
	{

	}
};
#endif // ReplayEventVFX_h__
