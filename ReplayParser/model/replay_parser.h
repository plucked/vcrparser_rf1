/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef replay_parser_h__
#define replay_parser_h__

#include "Replay.h"

class ReplayParser
{
public:
	static Replay::Shared LoadFromFile(const std::string& filename);
	static void SaveToFile(const Replay& replay, const std::string& filename);
};
#endif // replay_parser_h__
