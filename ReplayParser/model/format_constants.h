/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)

	Parts of this file are taken from the website http://rfactor.net/web/rf1/devcorner/replay-format-information/
*/

#ifndef format_constants_h__
#define format_constants_h__

enum EventClass
{
	ECLASS_LOC = 0,
	ECLASS_VFX,
	ECLASS_SFX,
	ECLASS_SYS,
	ECLASS_COMM,
	ECLASS_OTHER,
	ECLASS_MAXIMUM
};


class EventTypes
{
public:
	static const int ETYPE_NOTYPE = 63; // doesn’t need to be anything in particular, but this is the number least likely to be used for a real event type

	// ECLASS_LOC events
	static const int ETYPE_CONE = 0; // cone state
	static const int ETYPE_POST = 1; // post state
	static const int ETYPE_SIGN = 2; // sign state
	static const int ETYPE_WHEEL = 3; // wheel state
	static const int ETYPE_WING = 4; // wing state
	static const int ETYPE_PART = 5; // part state
	// note: do not change order of the ETYPE_*LOC events!
	static const int ETYPE_ZIPUPDATE = 6; // tells server that last zip can be safely extrapolated
	static const int ETYPE_ZIPLOC_R = 7; // compressed vehicle loc (more detailed than SIMPLELOC)
	static const int ETYPE_ZIPLOC_N = 8; // compressed vehicle loc
	static const int ETYPE_ZIPLOC_1 = 9; // compressed vehicle loc
	static const int ETYPE_ZIPLOC_2 = 10; // compressed vehicle loc
	static const int ETYPE_ZIPLOC_3 = 11; // compressed vehicle loc
	static const int ETYPE_ZIPLOC_4 = 12; // compressed vehicle loc
	static const int ETYPE_ZIPLOC_5 = 13; // compressed vehicle loc
	static const int ETYPE_ZIPLOC_6 = 14; // compressed vehicle loc
	static const int ETYPE_ZIPLOC_7 = 15; // compressed vehicle loc
	static const int ETYPE_SIMPLELOC_00 = 16; // simplified location event (smaller than ZIPLOC)
	static const int ETYPE_SIMPLELOC_01 = 17; // simplified location event
	static const int ETYPE_SIMPLELOC_02 = 18; // simplified location event
	static const int ETYPE_SIMPLELOC_03 = 19; // simplified location event
	static const int ETYPE_SIMPLELOC_04 = 20; // simplified location event
	static const int ETYPE_SIMPLELOC_05 = 21; // simplified location event
	static const int ETYPE_SIMPLELOC_06 = 22; // simplified location event
	static const int ETYPE_SIMPLELOC_07 = 23; // simplified location event
	static const int ETYPE_SIMPLELOC_08 = 24; // simplified location event
	static const int ETYPE_SIMPLELOC_09 = 25; // simplified location event
	static const int ETYPE_SIMPLELOC_10 = 26; // simplified location event
	static const int ETYPE_SIMPLELOC_11 = 27; // simplified location event
	static const int ETYPE_SIMPLELOC_12 = 28; // simplified location event
	static const int ETYPE_SIMPLELOC_13 = 29; // simplified location event
	static const int ETYPE_SIMPLELOC_14 = 30; // simplified location event
	static const int ETYPE_SIMPLELOC_15 = 31; // simplified location event
	static const int ETYPE_SIMPLELOC_16 = 32; // simplified location event
	static const int ETYPE_SIMPLELOC_17 = 33; // simplified location event
	static const int ETYPE_SIMPLELOC_18 = 34; // simplified location event
	static const int ETYPE_SIMPLELOC_19 = 35; // simplified location event
	static const int ETYPE_SIMPLELOC_20 = 36; // simplified location event
	static const int ETYPE_SIMPLELOC_21 = 37; // simplified location event
	static const int ETYPE_SIMPLELOC_22 = 38; // simplified location event
	static const int ETYPE_SIMPLELOC_23 = 39; // simplified location event
	static const int ETYPE_SIMPLELOC_24 = 40; // simplified location event
	static const int ETYPE_SIMPLELOC_25 = 41; // simplified location event
	static const int ETYPE_SIMPLELOC_26 = 42; // simplified location event
	static const int ETYPE_SIMPLELOC_27 = 43; // simplified location event
	static const int ETYPE_SIMPLELOC_28 = 44; // simplified location event
	static const int ETYPE_SIMPLELOC_29 = 45; // simplified location event
	static const int ETYPE_SIMPLELOC_30 = 46; // simplified location event
	static const int ETYPE_SIMPLELOC_31 = 47; // simplified location event
	static const int ETYPE_SIMPLELOC_32 = 48; // simplified location event

	// ECLASS_VFX events
	static const int ETYPE_BACKFIRE = 0; // veh backfire animation
	static const int ETYPE_LIGHT = 1; // veh rain light switch
	static const int ETYPE_TERRAIN = 2; // terrain conditions event
	static const int ETYPE_COPTER = 3; // sends the helicopter on its way
	static const int ETYPE_WEATHER = 4; // weather updates from the server
	static const int ETYPE_CLOUDMAP = 5; // cloud texture map names
	static const int ETYPE_LIGHTNING = 6; // lightning
	static const int ETYPE_DENT_BODY = 7; // dent bodywork
	static const int ETYPE_RESET_BODY = 8; // reset bodywork (vehicle reset to pits or something)
	static const int ETYPE_WALLSKID = 9; // generate skid on wall
	static const int ETYPE_RACELIGHTS = 10; // start lights, pit entrance & exit lights, maybe caution lights around track?

	// ECLASS_SFX events
	static const int ETYPE_VEHSFX_START = 0; // starts a vehicle sound effect
	static const int ETYPE_THUNDER = 1; // thunder
	static const int ETYPE_PIT_HORN = 2; // pit horn plays when someone enters pits

	// ECLASS_SYS events
	static const int ETYPE_SYNC_NOTIFY = 0; // server sends this to client if client should send a sync request (state change, etc)
	static const int ETYPE_PLAYER_READY = 1; // message from client to server requesting verification
	static const int ETYPE_PLAYER_VERIFY = 2; // server to client, data verify along with any changes
	static const int ETYPE_TRACKTOLOAD = 3; // server to client, new track is being loaded
	static const int ETYPE_CHATMSG = 4; // chat message, bi-directional
	static const int ETYPE_SCOREBOARD = 5; // score update
	static const int ETYPE_CHECKPOINT = 6;
	static const int ETYPE_SPEEDCOMP = 7;
	static const int ETYPE_NEWSTATIONS = 8; // complete new list of all active flag stations
	static const int ETYPE_UPDATESTATIONS = 9; // update flag stations

	static const int ETYPE_COUNTDOWN = 10; // start countdown
	static const int ETYPE_NEXTPHASE = 11; // move to next phase
	static const int ETYPE_SKIPFORMATION = 12; // skip formation lap

	static const int ETYPE_YELLOW_FLAG = 13;
	static const int ETYPE_STOP_GO = 14; // received stop/go
	static const int ETYPE_SERVE_STOP_GO = 15; // served stop/go

	static const int ETYPE_DNF = 16; // DNF player
	static const int ETYPE_UNDO_DNF = 17; // Undo DNF
	static const int ETYPE_DISQUALIFY = 18;
	static const int ETYPE_CLIENTKICK = 19; // used to kick client

	static const int ETYPE_PIT_BLUE_ON = 20; // pit exit flashing blue
	static const int ETYPE_PIT_BLUE_OFF = 21; // pit exit not flashing blue

	static const int ETYPE_TRACK_ORDER = 24; // order of vehicles on track (while under yellow flag)
	static const int ETYPE_SAFETY_CAR_ON = 25; // safety car is active
	static const int ETYPE_SAFETY_CAR_OFF = 26; // safety car is not active
	static const int ETYPE_SAFETY_CAR_LAPS = 27; // set the number of safety car formation laps

	static const int ETYPE_NEW_ENGINE = 28; // slot needed new engine during warmup (so send to back of grid)
	static const int ETYPE_QUAL_ORDER = 29; // listing of new qualifying order (used when player

	static const int ETYPE_TORDER_ADD = 30; // client -> server msg, if client is added from track order
	static const int ETYPE_TORDER_REMOVE = 31; // client -> server msg, if client is removed from 	track order
	static const int ETYPE_TORDER_TOBACK = 32; // client -> server msg, if client is removed from 	track order
	static const int ETYPE_TRACK_CLOSED = 33; // server -> client msg, track has been closed for 	business
	static const int ETYPE_TRACK_OPENED = 34; // server -> client msg, track has been opened for 	business
	static const int ETYPE_ENTRY_DATA = 35; // client -> server, client is sending entry data
	static const int ETYPE_ENTRY_DATA_OK = 36; // server -> client, entry data is ok
	static const int ETYPE_ENTRY_DATA_NO = 37; // server -> client, entry data not allowed

	static const int ETYPE_DRIVER_CHANGE = 38; // sent from previous driver to new driver (through server if necessary)
	static const int ETYPE_DRIVER_CHANGE_NOTIFY = 39; // sent from previous driver to new (driver (through server if necessary)
	static const int ETYPE_PASSENGER_CHANGE = 40; // notifies drivers that a passenger has joined/left their vehicle
	static const int ETYPE_FILE_REQUEST = 41;
	static const int ETYPE_FILE_HEADER = 42;
	static const int ETYPE_NET_AI_INFO = 43; // server info about one multiplayer AI
	static const int ETYPE_NET_AI_REQUEST = 44; // request server info about one or more AIs
	static const int ETYPE_NET_RESTART = 45; // restart event or race in multiplayer
	static const int ETYPE_CLIENT_VIEW = 46; // what client is looking at (slot or actual position) for server throttling purposes

	static const int ETYPE_VOICE_CHAT_MIXED = 47; // voice chat data thats been mixed by the 	server and ready for client consumption
	static const int ETYPE_VOICE_CHAT_CLIENT = 48; // voice chat data that the clients are	submitting to the server

	// ECLASS_OTHER events
	static const int ETYPE_FIX = 0; // fix damage
	static const int ETYPE_PITSTATE = 1; // change in pitstate
	static const int ETYPE_BASICSCORE = 2; // basic score
	static const int ETYPE_BASICSCORECLIENT = 3; // basic score client
	static const int ETYPE_SIMULATEINTERNET = 4; // simulate some attributes of the Internet	for network testing purposes
	static const int ETYPE_CALLVOTE_NEXTSESSION = 5; // “/callvote nextsession”
	static const int ETYPE_CALLVOTE_NEXTEVENT = 6; // “/callvote nextrace”
	static const int ETYPE_CALLVOTE_ADDAI = 7; // “/callvote addai”
	static const int ETYPE_CALLVOTE_ADD5AI = 8; // “/callvote add5ai”
	static const int ETYPE_CALLVOTE_REMOTESERVER = 9; // “/callvote kingme”
	static const int ETYPE_CALLVOTE_RESTARTEVENT = 10; // “/callvote restartweekend”
	static const int ETYPE_CALLVOTE_RESTARTRACE = 11; // “/callvote restartrace”
	static const int ETYPE_VOTE_YES = 12; // “/vote yes”
	static const int ETYPE_VOTE_NO = 13; // “/vote no”
	static const int ETYPE_VOTEIGNORED_PARTICIPANT = 14; // “Vote ignored: Only active 		participants may vote”
	static const int ETYPE_VOTEIGNORED_NOVOTE = 15; // “Vote ignored: There is no vote in 		progress”
	static const int ETYPE_VOTEIGNORED_ONEVOTE = 16; // “Vote ignored: You can only vote 		once per issue”
	static const int ETYPE_NODE_VOTED_YES = 17; // “%s voted YES to %s:” plus either “%d 		more to pass” or “vote PASSED”
	static const int ETYPE_NODE_VOTED_NO = 18; // “%s voted NO to %s” 
	static const int ETYPE_CANNOTCALL_DISABLED = 19; // “Cannot call vote: voting for %s is 		disabled”
	static const int ETYPE_CANNOTCALL_INPROGRESS = 20; // “Cannot call vote: there is a vote in 		progress”
	static const int ETYPE_CANNOTCALL_JUSTENDED = 21; // “Cannot call vote: voted just ended 		(wait %d seconds)”
	static const int ETYPE_CANNOTCALL_PARTICIPANT = 22; // “Cannot call vote: must be server or active participant”
	static const int ETYPE_CANNOTCALL_BEFORERACE = 23; // “Cannot call vote: cannot restart race before race starts”
	static const int ETYPE_CANNOTCALL_PASTRACE = 24; // “Cannot call vote: cannot advance session past race”
	static const int ETYPE_CANNOTCALL_MINVOTERS = 25; // “Cannot call vote: %d voters required”
	static const int ETYPE_CANNOTCALL_RACERESTARTS = 26; // “Cannot call vote: no more race restarts allowed”
	static const int ETYPE_CANNOTCALL_MOREAI = 27; // “Cannot call vote: no more AIs can be added”
	static const int ETYPE_VOTE_PROPOSED = 28; // “\”%s\” proposed by %s:” plus either “%d vote(s) needed to pass” or “vote PASSED”
	static const int ETYPE_WITHHOLDING_GREEN = 29; // WITHHOLDING_GREEN_MSG defined in steward.hpp
	static const int ETYPE_CANNOTCALL_PLRNOTFOUND = 31; // “Cannot call vote: player specified not found”
	static const int ETYPE_ADMIN_MSG = 32; // Some admin message
	static const int ETYPE_CANNOTCALL_SPECEVENT = 33; // “Cannot call vote: circuit not found or request disallowed”
};

enum EventFlags // Event flag
{
	EFLAG_NONE = 0, // no special flags (default)
	EFLAG_NO_NETWORK, // do not send across network (i.e. replay only)
	EFLAG_HIGH_PRIO, // make sure it’s in the high priority list (but not guaranteed)
	EFLAG_GUARANTEE, // guaranteed network event
	EFLAG_MAXIMUM
};

enum FileRequestTypes
{
	FREQ_PARTIAL=0, //request has full partial path
	FREQ_FULLPATH, //request has full path
	FREQ_SYMBOLIC //request is a symbol so the server needs to do a table lookup
};	

enum SessionTypes : u_char
{
	SESSION_PRACTISE_1 = 1,
	SESSION_PRACTISE_2 = 2,
	SESSION_PRACTISE_3 = 3,
	SESSION_PRACTISE_4 = 4,
	SESSION_QUALY = 5,
	SESSION_WARMUP = 6,
	SESSION_RACE = 7,
};

		// Invalid owner definition
#define EOWNER_INVALID (0x0ff)

namespace
{
	template<typename T>
	long ChangeBinary(T value, long header, int mask, int shift)
	{
		return ((value & mask) << shift) |  (header & (_I32_MAX - (mask << shift)));
	}

	EventClass GetEventClass(u_long header) { return (EventClass) ( header >> 29 ); }
	EventFlags GetEventFlag(u_long header) { return (EventFlags) ((header >> 27) & 0x03 ); }
	u_long GetEventSession(u_long header) { return ((header >> 24) & 0x07 ); }
	int GetEventType(u_long header) { return (int) ((header >> 18) & 0x03f ); }
	u_long GetEventSize(u_long header) { return ((header >> 8 ) & 0x03ff); }
	u_long SetEventSize(u_long size, u_long header) { return ChangeBinary<u_long>(size, header, 0x03FF, 8); }
	u_long GetEventOwner(u_long header) { return ( header & 0x0ff ); }

	
}


#endif // format_constants_h__
