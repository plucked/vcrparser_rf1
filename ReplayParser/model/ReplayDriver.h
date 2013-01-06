/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayDriver_h__
#define ReplayDriver_h__

using namespace std;

class ReplayDriver
{
public:
	typedef boost::shared_ptr<ReplayDriver> Shared;
	typedef vector<ReplayDriver::Shared> t_DriverContainer;

	char slotId;
	string name;
	string co_name;
	string vehicle_file;
	string skin_file;
	std::vector<char> upgrade_pack;
	float entry_time;
	float exit_time;

	static ReplayDriver::Shared ReadFromStream(istream& stream)
	{
		ReplayDriver::Shared result(new ReplayDriver);
		result->slotId = BinaryStreamUtil::ReadBinary<char>(stream);
		result->name = BinaryStreamUtil::ReadStringWithSizeChar(stream);
		result->co_name = BinaryStreamUtil::ReadStringWithSizeChar(stream);
		result->vehicle_file = BinaryStreamUtil::ReadString(stream, 32);
		result->skin_file = BinaryStreamUtil::ReadString(stream, 32);
		result->upgrade_pack = BinaryStreamUtil::ReadContainer<char>(stream, 8);
		result->entry_time = BinaryStreamUtil::ReadBinary<float>(stream);
		result->exit_time = BinaryStreamUtil::ReadBinary<float>(stream);
		return result;
	}

	void WriteToStream(std::ostream& stream) const
	{
		BinaryStreamUtil::WriteBinary<char>(slotId, stream);
		BinaryStreamUtil::WriteStringWithSizeChar(name, stream);
		BinaryStreamUtil::WriteStringWithSizeChar(co_name, stream);
		BinaryStreamUtil::WriteString(vehicle_file, stream);
		BinaryStreamUtil::WriteString(skin_file, stream);
		BinaryStreamUtil::WriteContainer<char>(upgrade_pack, stream);
		BinaryStreamUtil::WriteBinary<float>(entry_time, stream);
		BinaryStreamUtil::WriteBinary<float>(exit_time, stream);
	}
};


#endif // ReplayDriver_h__
