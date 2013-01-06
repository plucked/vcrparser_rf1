/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef ReplayCamera_h__
#define ReplayCamera_h__

using namespace std;

class ReplayCamera
{
public:
	typedef boost::shared_ptr<ReplayCamera> Shared;

	int unknown_integer_1;
	string camera_name;
	int driver_id;
	float camera_start_time;
	float camera_end_time;
	float camera_start_time_et;
	float camera_end_time_et;
	static const int size_of_unknown_byte_array_1 = 12;
	char* unknown_byte_array_1; // 12 bytes in my test cases, could be 3 floats or something
	int camera_flags; // this is some kind of bit flag I guess
	int camera_data_len; // this could be the length of the following data block, it fits in my cases, could be something else
	char* unknown_camera_data; // looks like a bunch of floats like orientation, position, zoom, fov ...

	ReplayCamera()
		: unknown_byte_array_1(nullptr), unknown_camera_data(nullptr)
	{

	}

	void swap(ReplayCamera & other)
	{
		std::swap(unknown_integer_1, other.unknown_integer_1);
		std::swap(camera_name, other.camera_name);
		std::swap(driver_id, other.driver_id);
		std::swap(camera_start_time, other.camera_start_time);
		std::swap(camera_end_time, other.camera_end_time);
		std::swap(camera_start_time_et, other.camera_start_time_et);
		std::swap(camera_end_time_et, other.camera_end_time_et);
		std::swap(unknown_byte_array_1, other.unknown_byte_array_1);
		std::swap(camera_flags, other.camera_flags);
		std::swap(camera_data_len, other.camera_data_len);
		std::swap(unknown_camera_data, other.unknown_camera_data);
	}

	ReplayCamera & operator = (ReplayCamera other) 
	{
		swap(other);
		return *this;
	}

	ReplayCamera::ReplayCamera( const ReplayCamera& other ) :
		unknown_integer_1( other.unknown_integer_1 ), 
		camera_name( other.camera_name ), 
		driver_id( other.driver_id ), 
		camera_start_time( other.camera_start_time ), 
		camera_end_time( other.camera_end_time ), 
		camera_start_time_et( other.camera_start_time_et ), 
		camera_end_time_et( other.camera_end_time_et ), 
		unknown_byte_array_1( nullptr ), 
		camera_flags( other.camera_flags ),
		camera_data_len( other.camera_data_len ), 
		unknown_camera_data(nullptr)
	{
		if (other.unknown_byte_array_1 != nullptr)
		{
			unknown_byte_array_1 = new char[size_of_unknown_byte_array_1];
			memcpy(unknown_byte_array_1, other.unknown_byte_array_1, size_of_unknown_byte_array_1);
		}

		if (other.unknown_camera_data != nullptr)
		{
			unknown_camera_data = new char[other.camera_data_len];
			memcpy(unknown_camera_data, other.unknown_camera_data, other.camera_data_len);
		}
	}

	~ReplayCamera()
	{
		if (unknown_byte_array_1 != nullptr) delete[] unknown_byte_array_1;
		if (unknown_camera_data != nullptr) delete[] unknown_camera_data;
	}

	static ReplayCamera::Shared ReadFromStream(istream& stream) 
	{
		ReplayCamera::Shared result(new ReplayCamera);
		
		result->unknown_integer_1 = BinaryStreamUtil::ReadBinary<int>(stream);
		result->camera_name = BinaryStreamUtil::ReadStringWithSizeInt(stream);
		result->driver_id = BinaryStreamUtil::ReadBinary<int>(stream);
		result->camera_start_time = BinaryStreamUtil::ReadBinary<float>(stream);
		result->camera_end_time = BinaryStreamUtil::ReadBinary<float>(stream);
		result->camera_start_time_et = BinaryStreamUtil::ReadBinary<float>(stream);
		result->camera_end_time_et = BinaryStreamUtil::ReadBinary<float>(stream);
		result->unknown_byte_array_1 = BinaryStreamUtil::ReadArray<char>(stream, size_of_unknown_byte_array_1);
		result->camera_flags = BinaryStreamUtil::ReadBinary<int>(stream);
		result->camera_data_len = BinaryStreamUtil::ReadBinary<int>(stream);
		result->unknown_camera_data = BinaryStreamUtil::ReadArray<char>(stream, result->camera_data_len);
		return result;
	}

	void WriteToStream(std::ostream& stream) const
	{
		BinaryStreamUtil::WriteBinary<int>(unknown_integer_1, stream);
		BinaryStreamUtil::WriteStringWithSizeInt(camera_name, stream);
		BinaryStreamUtil::WriteBinary<int>(driver_id, stream);
		BinaryStreamUtil::WriteBinary<float>(camera_start_time, stream);
		BinaryStreamUtil::WriteBinary<float>(camera_end_time, stream);
		BinaryStreamUtil::WriteBinary<float>(camera_start_time_et, stream);
		BinaryStreamUtil::WriteBinary<float>(camera_end_time_et, stream);
		BinaryStreamUtil::WriteArray<char>(unknown_byte_array_1, size_of_unknown_byte_array_1, stream);
		BinaryStreamUtil::WriteBinary<int>(camera_flags, stream);
		BinaryStreamUtil::WriteBinary<int>(camera_data_len, stream);
		BinaryStreamUtil::WriteArray<char>(unknown_camera_data, camera_data_len, stream);
	}
};
#endif // ReplayCamera_h__
