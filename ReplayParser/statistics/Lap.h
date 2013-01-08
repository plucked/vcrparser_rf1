#ifndef Lap_h__
#define Lap_h__

#define INVALID_SECTOR FLT_MIN

class Lap
{
public:
	typedef boost::shared_ptr<Lap> Shared;
	typedef std::vector<Shared> t_LapContainer;
	typedef std::map<u_char, Shared> t_LapMap;
	typedef std::pair<u_char, Shared> t_LapPair;

	u_char lapNr;
	// total times are from the beginning of the lap
	std::vector<float> sectorTotalTimes; // 0 = start/stop line, 1 = first sector, 2 = second sector
	// times are by each sector on its own
	std::vector<float> sectorTimes; // 0 = start/stop line, 1 = first sector, 2 = second sector

	Lap()
		: lapNr(0)
	{
		for(u_int i = 0; i < 3; ++i) sectorTotalTimes.push_back(INVALID_SECTOR);
		for(u_int i = 0; i < 3; ++i) sectorTimes.push_back(INVALID_SECTOR);
	}

	void UpdateSectorTimes()
	{
		if (sectorTotalTimes[1] != INVALID_SECTOR) sectorTimes[1] = sectorTotalTimes[1];
		if (sectorTotalTimes[1] != INVALID_SECTOR && sectorTotalTimes[2] != INVALID_SECTOR) sectorTimes[2] = sectorTotalTimes[2] - sectorTotalTimes[1];
		if (sectorTotalTimes[2] != INVALID_SECTOR && sectorTotalTimes[0] != INVALID_SECTOR) sectorTimes[0] = sectorTotalTimes[0] - sectorTotalTimes[2];
	}

	std::string ToString()
	{
		std::stringstream ss;
		ss << "Lap [" << (int)lapNr << "]";
		ss << " s1: ";
		if (sectorTotalTimes[1] == INVALID_SECTOR) ss << "----";
		else ss << sectorTotalTimes[1];
		if (sectorTimes[1] == INVALID_SECTOR) ss << "(----)";
		else ss  << " (" << sectorTimes[1] << ")";

		ss << " s2: ";
		if (sectorTotalTimes[2] == INVALID_SECTOR) ss << "----";
		else ss << sectorTotalTimes[2];
		if (sectorTimes[2] == INVALID_SECTOR) ss << "(----)";
		else ss << " (" << sectorTimes[2] << ")";

		ss << " s3: ";
		if (sectorTotalTimes[0] == INVALID_SECTOR) ss << "----";
		else ss << sectorTotalTimes[0];
		if (sectorTimes[0] == INVALID_SECTOR) ss << "(----)";
		else ss << " (" << sectorTimes[0] << ")";
		return ss.str();
	}
};
#endif // Lap_h__
