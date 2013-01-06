/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayEventZipLoc_h__
#define ReplayEventZipLoc_h__

#include "ReplayEventUnknown.h"

class ReplayEventZipLoc : public ReplayEventUnknown
{
	/*
		pos: 
		 x = x;
		 y = height
		 z = y;
	*/
public:
	typedef boost::shared_ptr<ReplayEventZipLoc> Shared;

	ReplayEventZipLoc(ReplayEventFrame::Shared replayEventFrame)
		: ReplayEventUnknown(replayEventFrame)
	{

	}

	u_long GetInfo1() const { return BinaryStreamUtil::GetBits<u_long>(0, eventFrame->GetEventData()); }
	void SetInfo1(u_long value) const { BinaryStreamUtil::SetBits<u_long>(value, 0, eventFrame->GetEventData()); }

	u_long GetInfo2() const { return BinaryStreamUtil::GetBits<u_long>(4, eventFrame->GetEventData()); }
	void SetInfo2(u_long value) const { BinaryStreamUtil::SetBits<u_long>(value, 4, eventFrame->GetEventData()); }

	int GetCurrentRPS() const { return (int)(GetInfo1() >> 18); }
	bool GetPitLaneFlag() const { return (bool)(GetInfo1() >> 17 & 1); }
	int GetThrottle() const { return (int)(GetInfo1() >> 12 & 16); }
	bool GetBrakeLight() const { return (bool)(GetInfo1() >> 11 & 1); }
	bool GetHornFlag() const { return (bool)(GetInfo1() >> 10 & 1); }
	int GetTractionControl() const { return (int)(GetInfo1() >> 8 & 2); }
	bool GetSpeedLimiterFlag() const { return (bool)(GetInfo1() >> 7 & 1); }
	int GetSteerYaw() const { return (int)(GetInfo1() & 64); }

	int GetAcceleration() const { return (int)(GetInfo2() >> 24); }
	bool GetAccelerationFlag() const { return (int)(GetInfo2() >> 23 & 1); }
	bool GetWarningLightFlag() const { return (int)(GetInfo2() >> 22 & 1); }
	bool GetDriverVisibleFlag() const { return (int)(GetInfo2() >> 21 & 1); }
	bool GetHeadLightFlag() const { return (int)(GetInfo2() >> 20 & 1); }
	int GetCurrentDriver() const { return (int)(GetInfo2() >> 18 & 2); }

	bool Get_DPART_DEBRIS11() const { return (int)(GetInfo2() >> 17 & 1); }
	bool Get_DPART_DEBRIS10() const { return (int)(GetInfo2() >> 16 & 1); }
	bool Get_DPART_DEBRIS9() const { return (int)(GetInfo2() >> 15 & 1); }
	bool Get_DPART_DEBRIS8() const { return (int)(GetInfo2() >> 14 & 1); }
	bool Get_DPART_DEBRIS7() const { return (int)(GetInfo2() >> 13 & 1); }
	bool Get_DPART_DEBRIS6() const { return (int)(GetInfo2() >> 12 & 1); }
	bool Get_DPART_DEBRIS5() const { return (int)(GetInfo2() >> 11 & 1); }
	bool Get_DPART_DEBRIS4() const { return (int)(GetInfo2() >> 10 & 1); }
	bool Get_DPART_DEBRIS3() const { return (int)(GetInfo2() >> 9 & 1); }
	bool Get_DPART_DEBRIS2() const { return (int)(GetInfo2() >> 8 & 1); }
	bool Get_DPART_DEBRIS1() const { return (int)(GetInfo2() >> 7 & 1); }
	bool Get_DPART_DEBRIS0() const { return (int)(GetInfo2() >> 6 & 1); }

	bool Get_DPART_RWING() const { return (int)(GetInfo2() >> 5 & 1); }
	bool Get_DPART_FWING() const { return (int)(GetInfo2() >> 4 & 1); }
	bool Get_DPART_RR() const { return (int)(GetInfo2() >> 3 & 1); }
	bool Get_DPART_RL() const { return (int)(GetInfo2() >> 2 & 1); }
	bool Get_DPART_FR() const { return (int)(GetInfo2() >> 1 & 1); }
	bool Get_DPART_FL() const { return (int)(GetInfo2() & 1); }

	float GetTireSpinFL() const { return BinaryStreamUtil::GetBits<float, short>(8, eventFrame->GetEventData()); } 
	void SetTireSpinFL(float value) const { BinaryStreamUtil::SetBits<float, short>(value, 8, eventFrame->GetEventData()); }

	float GetTireSpinFR() const { return BinaryStreamUtil::GetBits<float, short>(10, eventFrame->GetEventData()); } 
	void SetTireSpinFR(float value) const { BinaryStreamUtil::SetBits<float, short>(value, 10, eventFrame->GetEventData()); }

	float GetTireSpinRL() const { return BinaryStreamUtil::GetBits<float, short>(12, eventFrame->GetEventData()); } 
	void SetTireSpinRL(float value) const { BinaryStreamUtil::SetBits<float, short>(value, 12, eventFrame->GetEventData()); }

	float GetTireSpinRR() const { return BinaryStreamUtil::GetBits<float, short>(14, eventFrame->GetEventData()); } 
	void SetTireSpinRR(float value) const { BinaryStreamUtil::SetBits<float, short>(value, 14, eventFrame->GetEventData()); }

	float GetVelX() const { return BinaryStreamUtil::GetBits<float, short>(16, eventFrame->GetEventData()); } 
	void SetVelX(float value) const { BinaryStreamUtil::SetBits<float, short>(value, 16, eventFrame->GetEventData()); }

	float GetVelY() const { return BinaryStreamUtil::GetBits<float, short>(18, eventFrame->GetEventData()); } 
	void SetVelY(float value) const { BinaryStreamUtil::SetBits<float, short>(value, 18, eventFrame->GetEventData()); }

	float GetVelZ() const { return BinaryStreamUtil::GetBits<float, short>(20, eventFrame->GetEventData()); } 
	void SetVelZ(float value) const { BinaryStreamUtil::SetBits<float, short>(value, 20, eventFrame->GetEventData()); }


	float GetPosX() const { return BinaryStreamUtil::GetBits<float>(26, eventFrame->GetEventData()); }
	void SetPosX(float value) const { BinaryStreamUtil::SetBits<float>(value, 26, eventFrame->GetEventData()); }
	float GetPosY() const { return BinaryStreamUtil::GetBits<float>(30, eventFrame->GetEventData()); }
	void SetPosY(float value) const { BinaryStreamUtil::SetBits<float>(value, 30, eventFrame->GetEventData()); }
	float GetPosZ() const { return BinaryStreamUtil::GetBits<float>(34, eventFrame->GetEventData()); }
	void SetPosZ(float value) const { BinaryStreamUtil::SetBits<float>(value, 34, eventFrame->GetEventData()); }

	float GetAngX() const { return BinaryStreamUtil::GetBits<float>(38, eventFrame->GetEventData()); }
	void SetAngX(float value) const { BinaryStreamUtil::SetBits<float>(value, 38, eventFrame->GetEventData()); }
	float GetAngY() const { return BinaryStreamUtil::GetBits<float>(42, eventFrame->GetEventData()); }
	void SetAngY(float value) const { BinaryStreamUtil::SetBits<float>(value, 42, eventFrame->GetEventData()); }
	float GetAngZ() const { return BinaryStreamUtil::GetBits<float>(46, eventFrame->GetEventData()); }
	void SetAngZ(float value) const { BinaryStreamUtil::SetBits<float>(value, 46, eventFrame->GetEventData()); }
};

#endif // ReplayEventZipLoc_h__
