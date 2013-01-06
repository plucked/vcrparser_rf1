/*
	Copyright (c) 2013 Rainer Heynke <rainer.heynke@plucked.de> (@plucked on twitter)

	This software is licensed with the cc-by license (http://creativecommons.org/licenses/by/3.0/)
*/

#ifndef BinaryStreamUtil_h__
#define BinaryStreamUtil_h__

using namespace std;


class BinaryStreamUtil
{
public:
	template <typename T>
	static vector<T> ReadContainer(istream& stream, int size)
	{
		vector<T> result;
		char* buffer = new char[size * sizeof(T)];
		stream.read(buffer, size * sizeof(T));
		for(u_int i = 0; i < size * sizeof(T); i += sizeof(T))
			result.push_back((T)buffer[i]);
		delete buffer;
		return result;
	}

	template <typename T>
	static void WriteContainer(const vector<T>& container, ostream& stream)
	{
		vector<T>::const_iterator it = container.begin();
		vector<T>::const_iterator itEnd = container.end();
		for(; it != itEnd; ++it)
			WriteBinary<T>(*it, stream);
	}

	template <typename T>
	static T* ReadArray(istream& stream, istream::pos_type size)
	{
		char* buffer = new char[size * sizeof(T)];
		stream.read(buffer, size * sizeof(T));
		T* result = (T*)buffer;
		return result;
	}

	template <typename T>
	static void WriteArray(T* arr, int size, ostream& stream)
	{
		char* buffer = (char*)arr;
		stream.write(buffer, size * sizeof(T));
	}

	template <typename T>
	static T ReadBinary(istream& stream, int size)
	{
		T result = 0;
		stream.read((char*)&result, size);
		return result;
	}

	template <typename T>
	static T ReadBinary(istream& stream)
	{
		return ReadBinary<T>(stream, sizeof(T));
	}

	template <typename T>
	static void WriteBinary(T value, int size, ostream& stream)
	{
		stream.write((char*)&value, size);
	}

	template <typename T>
	static void WriteBinary(T value, ostream& stream)
	{
		WriteBinary(value, sizeof(T), stream);
	}

	static string ReadString(istream& stream, int size)
	{
		char* buffer = new char[size];
		stream.read(buffer, size);
		string result(buffer, size);
		delete buffer;
		return result;
	}

	static void WriteString(const string& str, ostream& stream)
	{
		if (str.length() > 0) stream.write(str.c_str(), str.length());
	}

	static string ReadStringWithSizeInt(istream& stream)
	{
		int size = ReadBinary<int>(stream);
		if (size == 0) return "";
		return ReadString(stream, size);
	}

	static void WriteStringWithSizeInt(const string& str, ostream& stream)
	{
		int length = str.length();
		stream.write((char*)&length, sizeof(int));
		if (str.length() > 0) stream.write(str.c_str(), str.length());
	}

	static string ReadStringWithSizeChar(istream& stream)
	{
		u_char size = ReadBinary<u_char>(stream);
		if (size == 0) return "";
		return ReadString(stream, size);
	}

	static void WriteStringWithSizeChar(const string& str, ostream& stream)
	{
		u_char length = (char)str.length();
		stream.write((char*)&length, sizeof(char));
		if (str.length() > 0) stream.write(str.c_str(), str.length());
	}

	static void SkipBytes(istream& stream, istream::pos_type size)
	{
		stream.seekg(stream.tellg() + size);
	}

	template <typename T>
	static void SetBits(T value, int byteOffset, char* data)
	{
		memcpy(data + byteOffset, (char*)&value, sizeof(T));
	}

	template <typename T, typename TO>
	static void SetBits(T value, int byteOffset, char* data)
	{
		assert(false); // there is a missing template specialization
	}

	template<>
	static void SetBits<float, char>(float value, int byteOffset, char* data)
	{
		char v = (char)round(value * (float)CHAR_MAX);
		SetBits<char>(v, byteOffset, data);
	}

	template<>
	static void SetBits<float, u_char>(float value, int byteOffset, char* data)
	{
		u_char v = (u_char)round(value * (float)_I8_MAX);
		SetBits<u_char>(v, byteOffset, data);
	}

	template<>
	static void SetBits<float, short>(float value, int byteOffset, char* data)
	{
		short v = (short)round(value * (float)SHRT_MAX);
		SetBits<short>(v, byteOffset, data);
	}

	template<>
	static void SetBits<float, u_short>(float value, int byteOffset, char* data)
	{
		u_short v = (u_short)round(value * (float)_I16_MAX);
		SetBits<u_short>(v, byteOffset, data);
	}

	template<>
	static void SetBits<float, int>(float value, int byteOffset, char* data)
	{
		int v = (int)round(value * (float)INT_MAX);
		SetBits<int>(v, byteOffset, data);
	}

	template<>
	static void SetBits<float, u_int>(float value, int byteOffset, char* data)
	{
		u_int v = (u_int)round(value * (float)_I32_MAX);
		SetBits<u_int>(v, byteOffset, data);
	}

	template <typename T>
	static void SetBits(const vector<T>& value, int byteOffset, char* data)
	{
		for(vector<T>::size_type i = 0; i < value.size(); ++i)
			memcpy(data + byteOffset + (sizeof(T) * i), (char*)&value[i], sizeof(T));
	}


	template <typename T>
	static T GetBits(int byteOffset, char* data)
	{
		T result;
		memcpy((char*)&result, data + byteOffset, sizeof(T));
		return result;
	}

	template <typename T, typename FROM>
	static T GetBits(int byteOffset, char* data)
	{
		assert(false); // there is a missing template specialization
		return 0;
	}

	template <>
	static float GetBits<float, u_char>(int byteOffset, char* data)
	{
		u_char v = GetBits<u_char>(byteOffset, data);
		return (float)v / (float)CHAR_MAX;
	}

	template <>
	static float GetBits<float, char>(int byteOffset, char* data)
	{
		char v = GetBits<char>(byteOffset, data);
		return (float)v / (float)_I8_MAX;
	}

	template <>
	static float GetBits<float, u_short>(int byteOffset, char* data)
	{
		u_short v = GetBits<u_short>(byteOffset, data);
		return (float)v / (float)SHRT_MAX;
	}

	template <>
	static float GetBits<float, short>(int byteOffset, char* data)
	{
		short v = GetBits<short>(byteOffset, data);
		return (float)v / (float)_I16_MAX;
	}

	template <>
	static float GetBits<float, u_int>(int byteOffset, char* data)
	{
		u_int v = GetBits<u_int>(byteOffset, data);
		return (float)v / (float)INT_MAX;
	}

	template <>
	static float GetBits<float, int>(int byteOffset, char* data)
	{
		int v = GetBits<int>(byteOffset, data);
		return (float)v / (float)_I32_MAX;
	}

	template <typename T>
	static vector<T> GetBits(int amount, int byteOffset, char* data)
	{
		vector<T> result;
		for(u_int i = 0; i < amount; ++i)
			result.push_back(GetBits<T>(byteOffset + (sizeof(T) * i), data));
		return result;
	}
};
#endif // BinaryStreamUtil_h__
