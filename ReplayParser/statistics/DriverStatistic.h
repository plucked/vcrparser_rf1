#ifndef DriverStatistic_h__
#define DriverStatistic_h__

#include "DriverStatisticStint.h"

class DriverStatistic
{
public:
	typedef boost::shared_ptr<DriverStatistic> Shared;
	typedef std::vector<Shared> t_DriverContainer;
	typedef std::map<u_char, Shared> t_SlotDriverMap;
	typedef std::pair<u_char, Shared> t_SlotDriverPair;


	u_char slotId;
	std::string name;

	DriverStatisticStint::t_StintContainer m_Stints;

	// Creates a new one if there are no stints
	DriverStatisticStint::Shared GetLastStint()
	{
		if (m_Stints.size() == 0)
		{
			DriverStatisticStint::Shared newStint(new DriverStatisticStint());
			m_Stints.push_back(newStint);
		}

		return m_Stints.back();
	}
};
#endif // DriverStatistic_h__
