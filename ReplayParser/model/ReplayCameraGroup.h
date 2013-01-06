/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayCameraGroup_h__
#define ReplayCameraGroup_h__

#include "ReplayCamera.h"

class ReplayCameraGroup
{
public:
	typedef boost::shared_ptr<ReplayCameraGroup> Shared;

	int unknown_integer_1; // was "1" in my testing cases
	int unknown_integer_2; // was 0 in my testing cases

	typedef vector<ReplayCamera::Shared> t_CameraContainer;
	t_CameraContainer cameras;

	static ReplayCameraGroup::Shared ReadFromStream(istream& stream) 
	{
		ReplayCameraGroup::Shared result(new ReplayCameraGroup);
		result->unknown_integer_1 = BinaryStreamUtil::ReadBinary<int>(stream);
		result->unknown_integer_2 = BinaryStreamUtil::ReadBinary<int>(stream);

		u_int camera_count = BinaryStreamUtil::ReadBinary<int>(stream);
		for(u_int i = 0; i < camera_count; ++i)
		{
			result->cameras.push_back(ReplayCamera::ReadFromStream(stream));
		}

		return result;
	}

	void WriteToStream(std::ostream& stream) const
	{
		BinaryStreamUtil::WriteBinary<int>(unknown_integer_1, stream);
		BinaryStreamUtil::WriteBinary<int>(unknown_integer_2, stream);
		BinaryStreamUtil::WriteBinary<int>(cameras.size(), stream);

		t_CameraContainer::const_iterator it = cameras.begin();
		t_CameraContainer::const_iterator itEnd = cameras.end();
		for(; it != itEnd; ++it)
		{
			it->get()->WriteToStream(stream);
		}
	}
};
#endif // ReplayCameraGroup_h__
