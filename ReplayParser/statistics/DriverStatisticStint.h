#ifndef DriverStatisticStint_h__
#define DriverStatisticStint_h__

// All statistics about a stint until the driver got back to box (pressing ESC, DNF ...)
#include "Lap.h"

class DriverStatisticStint
{
public:
	typedef boost::shared_ptr<DriverStatisticStint> Shared;
	typedef std::vector<Shared> t_StintContainer;

	float distance; // in meter
	Lap::t_LapMap laps;

	DriverStatisticStint()
		: distance(0.0f), currentLap(0xFF)
	{

	}

	void AddLap(u_char lapNr)
	{
		Lap::Shared lap(new Lap());
		lap->lapNr = lapNr;
		laps.insert(Lap::t_LapPair(lapNr, lap));
		currentLap = lapNr;
	}

	Lap::Shared GetLap(u_char lapNr)
	{
		Lap::t_LapMap::iterator findIt = laps.find(lapNr);
		if (findIt != laps.end()) return findIt->second;
		return Lap::Shared();
	}

	bool HasLap(u_char lapNr)
	{
		return (laps.find(lapNr) != laps.end());
	}

	Lap::t_LapContainer GetLaps()
	{
		Lap::t_LapContainer result;

		// lambda copy map values to vector
		result.reserve(laps.size());
		std::for_each(laps.begin(),laps.end(), [&result](const Lap::t_LapMap::value_type& p) 
		{ result.push_back(p.second); });

		return result;
	}

	u_char GetCurrentLapNr()
	{
		if (currentLap == 0xFF) 
		{
			AddLap(0);
		}
		return currentLap;
	}
private:
	u_char currentLap;
};
#endif // DriverStatisticStint_h__
