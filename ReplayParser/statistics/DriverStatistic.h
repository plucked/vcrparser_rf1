#ifndef DriverStatistic_h__
#define DriverStatistic_h__

#include "DriverStatisticStint.h"

class DriverStatistic
{
public:
	typedef std::vector<DriverStatistic> t_DriverContainer;


	u_char slotId;
	std::string name;

	DriverStatisticStint::t_StintContainer m_Stints;
};
#endif // DriverStatistic_h__
